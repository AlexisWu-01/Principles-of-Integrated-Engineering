/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
int LED_1=9;
int LED_2=10;
int LED_3=11;
int LED_4=12;
int LED_5=13;
int button = 7;
int pushed = -1;
int lastButtonState = LOW;
int lastPressed = 0;
int buttonState;
int mode = 0;
int delayTime = 200;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);


}

//// the loop function runs over and over again forever
//void loop() {
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second
//}

void allOff(){
digitalWrite(LED_1, LOW);
digitalWrite(LED_2, LOW);
digitalWrite(LED_3, LOW);
digitalWrite(LED_4, LOW);
}

void allOn(){
digitalWrite(LED_1, HIGH);
digitalWrite(LED_2, HIGH);
digitalWrite(LED_3, HIGH);
digitalWrite(LED_4, HIGH);
}

void allFlashing(){
 allOn();
 delay(delayTime);
 allOff();
 delay(delayTime);
}

void left_bounce(){
  digitalWrite(LED_1,HIGH);
  delay(delayTime);
  digitalWrite(LED_1,LOW);
  digitalWrite(LED_2,HIGH);
  delay(delayTime);
  digitalWrite(LED_2,LOW);
  digitalWrite(LED_3,HIGH);
  delay(delayTime);
  digitalWrite(LED_3,LOW);
  digitalWrite(LED_4,HIGH);
  delay(delayTime);
  digitalWrite(LED_4,LOW);
  
}


void right_bounce(){
  digitalWrite(LED_4,HIGH);
  delay(delayTime);
  digitalWrite(LED_4,LOW);
  digitalWrite(LED_3,HIGH);
  delay(delayTime);
  digitalWrite(LED_3,LOW);
  digitalWrite(LED_2,HIGH);
  delay(delayTime);
  digitalWrite(LED_2,LOW);
  digitalWrite(LED_1,HIGH);
  delay(delayTime);
  digitalWrite(LED_1,LOW);
  
}

void control(){
int reading = digitalRead(button);
  if (reading == HIGH && (millis() - lastPressed) > 200) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    mode += 1;
    lastPressed = millis();
  }
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

void changeMode(){
  switch (mode) {
  case 0:
    allOff();
    break;
  case 1:
    allOn();
    break;
  case 2:
    allFlashing();
    break;
  case 3:
    left_bounce();
    break;
  case 4:
    right_bounce();
    break;
  default:
    mode = 0;
    break;
  
}

}

void loop(){

  control();
  changeMode();
  Serial.print(mode);
}
