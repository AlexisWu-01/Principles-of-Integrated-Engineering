int LED_1=9;
int LED_2=10;
int LED_3=11;
int LED_4=12;
int LED_5=13;

int button = 7;
int sensor = A0;

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
  pinMode(sensor,INPUT);
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


void distance(){
    int dist = analogRead(sensor);
    Serial.print(dist);
    Serial.print('\n');
    allOn();
    delay((1000-dist)/3);
    allOff();
    delay((1000-dist)/3);

}


void control(){
int reading = digitalRead(button);
  if (reading == HIGH && (millis() - lastPressed) > 200) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    mode += 1;
    lastPressed = millis();
  }
  
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
  case 5:
    distance();
    break;
  default:
    mode = 0;
    break;
  
}

}

void loop(){
//
  control();
  changeMode();
//  Serial.print(mode);
//distance();
}