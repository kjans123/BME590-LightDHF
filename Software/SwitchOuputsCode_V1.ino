const int inPin = 2;
int currentState;
int lastState;
int outPin = 5;
int pwmVal;
int counter;

void setup() {
  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT);
  Serial.begin(9600); 
}

void loop() {
 
lastState = digitalRead(inPin); //1= not pressed, 0 = pressed
delay(50);
currentState = digitalRead(inPin);

if (currentState == 0 && lastState == 1)
{
  counter = counter + 1;
}
//need Interrupts 
switch(counter){
  case 0: 
    pwmVal = 0;
    break;
  case 1:
    pwmVal = 50;
    break;
  case 2:
    pwmVal = 100;
    break;
  case 3:
    pwmVal = 150;
    break;
  case 4:
    pwmVal = 255;
    break;
  case 5:
    analogWrite(outPin,255); //bugging here...need interrupts
    delay(250);
    analogWrite(outPin,0);
    delay(250);
    break;
 case 6:
  counter = 0;
  break;
}
analogWrite(outPin, pwmVal);
}
