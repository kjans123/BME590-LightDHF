#define inPin 2
#define outPin 5
#define FLASH_RATE_Hz 2
#define PWM_MAX 255

int currentState;
int lastState;
int pwmVal = 0;
int operating_state=0;
volatile bool button_pushed = false;


void setup() {
  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(inPin), button_pushed_func, RISING);
}

void loop() {
  check_for_button_press();
  cycle_light();
}


void button_pushed_func(){
  button_pushed = true;
}

void flash_the_light(){
  double on_off_time = (pow(FLASH_RATE_Hz,-1)*0.5)*1000;
  analogWrite(outPin,PWM_MAX);
  delay(on_off_time);
  analogWrite(outPin,0);
  delay(on_off_time);
}



void check_for_button_press(){
  if (button_pushed = true){
    lastState = digitalRead(inPin); //0= not pressed, 1 = pressed
    delay(25);
    currentState = digitalRead(inPin);
    if (currentState == 1 && lastState == 0){
      operating_state = operating_state + 1;
      button_pushed = false;
    }
  }
}

void cycle_light(){      
  switch(operating_state){
    case 0: 
      pwmVal = 0;
      break;
    case 1:
      pwmVal = int(PWM_MAX/4);
      break;
    case 2:
      pwmVal = int(PWM_MAX/2);
      break;
    case 3:
      pwmVal = PWM_MAX;
      break;
    case 4:
      flash_the_light();
      break;
  case 5:
      operating_state = 0;
      break;
}
analogWrite(outPin, pwmVal);  
}
