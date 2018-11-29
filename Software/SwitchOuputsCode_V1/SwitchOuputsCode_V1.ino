#define inPin 2
#define outPin 6
#define FLASH_RATE_Hz 2
#define PWM_MAX 255

int currentState;
int lastState;
int pwmVal = 0;
int operating_state=0;
bool LED_ON = false;
double turn_light_off_time=0;
double turn_light_on_time = 0;
double flash_count = 0;
double button_pressed_time=0;
volatile bool button_pushed = false;

double on_off_time = (pow(FLASH_RATE_Hz,-1)*0.5)*1000;

void setup() {
  pinMode(outPin, OUTPUT);

  pinMode(inPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(inPin), button_pushed_func, RISING);
  Serial.begin(9600);
}

void loop() {
  check_for_button_press();
  cycle_light();


}


void button_pushed_func(){
  button_pushed = true;
  button_pressed_time = millis();
}

void flash_the_light(){
  if (flash_count == 0){
      if (millis()-button_pressed_time > on_off_time && LED_ON == true){
        analogWrite(outPin,0);
        turn_light_off_time = millis();
        LED_ON = false;
      }
  }

  else if (flash_count >0) {
    if (LED_ON == false && (millis()-turn_light_off_time) > on_off_time){
        analogWrite(outPin,255);
        turn_light_on_time = millis();
        LED_ON = true;
    }
    else if (LED_ON == true && (millis()-turn_light_on_time) > on_off_time){
        analogWrite(outPin, 0);
        turn_light_off_time = millis();
        LED_ON=false;
    }

  }
flash_count = 1 + flash_count;
}



void check_for_button_press(){
  if (button_pushed = true){
    lastState = digitalRead(inPin); //0= not pressed, 1 = pressed
    delay(25);
    currentState = digitalRead(inPin);
    if (currentState == 1 && lastState == 0){
      operating_state = operating_state + 1;

    }
  }
 button_pushed = false;
}

void cycle_light(){
  switch(operating_state){
    case 0:
      pwmVal = 0;
      LED_ON = false;
      analogWrite(outPin, pwmVal);
      break;
    case 1:
      pwmVal = int(PWM_MAX/4);
      LED_ON = true;
      analogWrite(outPin, pwmVal);
      break;
    case 2:
      pwmVal = int(PWM_MAX/2);
      LED_ON = true;
      analogWrite(outPin, pwmVal);
      break;
    case 3:
      pwmVal = PWM_MAX;
      LED_ON = true;
      analogWrite(outPin, pwmVal);
      break;
    case 4:
      flash_the_light();
      break;
    case 5:
      operating_state = 0;
      LED_ON = false;
      flash_count=0;
      pwmVal = 0;
      analogWrite(outPin, pwmVal);
      break;
}

}
