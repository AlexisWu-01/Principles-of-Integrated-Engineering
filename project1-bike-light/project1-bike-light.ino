//Initialize pins on arduino board
int button = 7;
int sensor = A0;
int LED_1=9;
//Use number of LED lights to make it easier to adjust numbers than hardcoding it
int num_LED = 4;

//Initialize variables
int lastPressed = 0;
int lastTimeStamp = 0;
int mode = 0;
int delayTime = 500;
int led_states = LOW;


void setup() {
    //Sets up pin mode and print monitor
    for (int i=LED_1; i <= LED_1 + num_LED; i++){
        pinMode(i,OUTPUT);
    }
    pinMode(button, INPUT);
    pinMode(sensor,INPUT);
    Serial.begin(9600);
    
}

void allOff(){
    //All lights stay off
    for (int i=LED_1; i <= LED_1 + num_LED; i++){
        // For loop is to avoid hardcoding
        digitalWrite(i,LOW);
        led_states = LOW;
    }
}

void allOn(){
    //All lights stay on
    for (int i=LED_1; i <= LED_1 + num_LED; i++){
        digitalWrite(i,HIGH);
        led_states = HIGH;
    }
}

void allFlashing(){
    // All lights turns on and off
    if (millis() - lastTimeStamp >= delayTime){
        /*
        * millis() finds the current timestamp
        * and compares it with the last recorded time stamp
        */
        if (led_states == HIGH){
            //reverse led mode
            led_states = LOW;
        }
        else{
            led_states =HIGH;
        }
        for (int i=LED_1;i<=LED_1+num_LED;i++){
            //actually changes the LED modes
            digitalWrite(i,led_states);
        }
        lastTimeStamp = millis(); //update last pressed time stamp
    }
}

void left_bounce(){
    /*
    * Serves as the left turn signal light.
    * All lights turns on then off one by one.
    */
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
    /*
    * Serves as the right turn signal light.
    * All lights turns on then off one by one.
    */
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
    /*
    * Lights flashing at the pace determined
    * by the distance detected by infrared sensor.
    * The code was adapted from flashing() function.
    */
    int dist = analogRead(sensor);
    int waitTime = (1000 - dist)/2;
    if (millis() - lastTimeStamp >= waitTime){
        /*
        * millis() finds the current timestamp
        * and compares it with the last recorded time stamp
        */
        if (led_states == HIGH){
            //reverse led mode
            led_states = LOW;
        }
        else{
            led_states =HIGH;
        }
        for (int i=LED_1;i<=LED_1+num_LED;i++){
            //actually changes the LED modes
            digitalWrite(i,led_states);
        }
        lastTimeStamp = millis(); //update last pressed time stamp
    }
}


void control(){
    /*
    * Reads the button input with an interval of 300 milliseconds.
    */
    int reading = digitalRead(button);
    if (reading == HIGH && (millis() - lastPressed > 300)) {
        mode += 1;
        lastPressed = millis();
        //prints mode to monitor
        Serial.print("mode switched to: ");
        Serial.print(mode);
        Serial.print('\n');
    }
    
}

void changeMode(){
    /*
    * Calls function based on different modes.
    */
    switch (mode) {
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
          allOff();
          break;
        
    }
    
}

void loop(){
    /*
    * main function, keeps being called.
    */
    control();
    changeMode();
}
