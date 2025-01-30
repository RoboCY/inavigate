/*
iNavigate
A project based around the Kypruino UNO+, a PIR motion sensor and an IR obstacle sensor
*/

//Pinout:
#define PIR_SENSOR_PIN 10
#define OBSTACLE_SENSOR_PIN 5
#define BUZZER_PIN 9
#define BUTTON_PIN 7

//Variables:
int mode = 1; //1: Obstacle sensor | -1: PIR sensor
bool button_pressed = false;


void setup() {
  //Set the function of each of the pins we specified earlier using the pinMode() function.
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(OBSTACLE_SENSOR_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW){ //Read the state of the 'A' button. If digitalRead returns LOW the button is pressed.
    while(digitalRead(BUTTON_PIN) == LOW){} //Wait for the button to be released, this is used to trigger the "button_pressed = true" only once.
    button_pressed = true;
  }

  if(button_pressed){
    mode = mode * -1; //By multiplying mode (with a starting value of 1) with -1, we can alternate between 2 values, '1' and '-1'.
    button_pressed = false; //Reset the button status to false.
    tone(BUZZER_PIN,3000,80); //Play sound as feedback to the user.
    delay(80);
    tone(BUZZER_PIN,8000,100);
  }

  if(mode == 1){ //Mode 1: Only the obstacle sensor is active
    if(digitalRead(OBSTACLE_SENSOR_PIN) == LOW){ //When an obstacle is detected the sensor pulls the OUT Pin to GND (LOW). If we detect a LOW pin state, the buzzer beeps while the obstacle is in range.
      tone(BUZZER_PIN,8000,50);
    }
  }
  else if(mode == -1){ //Mode -1: Only the PIR motion sensor is active
    if(digitalRead(PIR_SENSOR_PIN) == HIGH){ //When movement is detected the sensor outputs volage (HIGH). If we detect a HIGH pin state, the buzzer plays a melody each time movement is detected.
      tone(BUZZER_PIN,2000,400);
      delay(400);
      tone(BUZZER_PIN,5000,400);
      delay(400);
      tone(BUZZER_PIN,9000,500);
      delay(1000);
    }
  }
  delay(100);
}
