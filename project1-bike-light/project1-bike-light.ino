int LED_1=9;
int num_LED = 4;

int button = 7;
int sensor = A0;

int lastPressed = 0;
int lastTimeStamp = 0;
int buttonState;
int mode = 0;
int delayTime = 500;
int led_states[] = {LOW,LOW,LOW,LOW};

void setup() {
  for (int i=LED_1; i <= LED_1 + num_LED; i++){
    pinMode(i,OUTPUT);
  }
  pinMode(button, INPUT);
  pinMode(sensor,INPUT);
  Serial.begin(9600);

}

void allOff(){
    for (int i=LED_1; i <= LED_1 + num_LED; i++){
      digitalWrite(i,LOW);
      led_states[i] = LOW;
  }
}

void allOn(){
   for (int i=LED_1; i <= LED_1 + num_LED; i++){
      digitalWrite(i,HIGH);
      led_states[i] = HIGH;
  }
}

void allFlashing(){
  if (millis() - lastTimeStamp >= delayTime){
    for (int i=LED_1;i<=LED_1+num_LED;i++){
      lastTimeStamp = millis();
      if (led_states[i] == HIGH){
        led_states[i] = LOW;
      }
      else{
        led_states[i] =HIGH;
      }
      digitalWrite(i,led_states[i]);
    }
  }
}

void left_bounce(){
  //While loop failed because while has the similar effect as delay: arduino would not respond to other codes
  digitalWrite(LED_1,HIGH);
  for (int i=LED_1+1;i<LED_1+num_LED;i++){
      delay(delayTime);
      digitalWrite(i-1,LOW);
      digitalWrite(i,HIGH);
    }
    delay(delayTime);
    digitalWrite(LED_1+num_LED-1,LOW);
  }
  

void right_bounce(){
  digitalWrite(LED_1+num_LED-1,HIGH);
  for (int i=LED_1+num_LED-2;i>=LED_1;i--){
      delay(delayTime);
      digitalWrite(i+1,LOW);
      digitalWrite(i,HIGH);
    }
    delay(delayTime);
    digitalWrite(LED_1,LOW);
  }
  

void distance(){
    int dist = analogRead(sensor);
    int waitTime = (1000 - dist)/2;
    if (millis() - lastTimeStamp >= waitTime){
      for (int i=LED_1;i<=LED_1+num_LED;i++){
        lastTimeStamp = millis();
        if (led_states[i] == HIGH){
          led_states[i] = LOW;
        }
        else{
          led_states[i] =HIGH;
        }
        digitalWrite(i,led_states[i]);
    }
  }
}


void control(){
int reading = digitalRead(button);
  if (reading == HIGH && (millis() - lastPressed > 300)) {
    lastPressed = millis();
    mode += 1;
    Serial.print("mode switched to: ");
    Serial.print(mode);
    Serial.print('\n');
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

  control();
  changeMode();
}
