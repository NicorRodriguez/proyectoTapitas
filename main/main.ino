#include <string.h>
#include "COLOR.h"
#include <Servo.h>
#include <Stepper.h>

Servo compuerta;
Servo myservo;

bool onlyOnce = true;
int buttonState;
int posmyservo = 0;
int pos = 0;
int angle = 0;

double stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  Serial.begin(9600);
  COLOR_init();
  myservo.attach(13);
  myStepper.setSpeed(15);
  compuerta.attach(12);
  //myservo.write(180);
  //compuerta.write(90);
}

void moveServo(Servo &motor, int value, int delayServo){
  for (pos = 0; pos <= value; pos += 1) {
    motor.write(pos);
    delay(5);
  }
  delay(delayServo);
  for (pos = value; pos >= 0; pos -= 1) {
    motor.write(pos);
    delay(5);
  }
}

int angleByColor(char* color){
  //return 120;
  if(color == "ROJO") return 170;
  if(color == "AZUL") return 120;
  if(color == "VERDE") return 80;
  if(color == "NEGRO") return 40;
  else return 0;
}

void loop() {
  
  RGB_t c = COLOR_getRGB();
  //moveServo(myservo, 90, 0);
  Serial.println(COLOR_getColorName());
  myservo.write(170);

  
  angle = angleByColor(COLOR_getColorName());
  Serial.println(angle);
  for (posmyservo = 180; posmyservo >= angle; posmyservo -= 1) {
    myservo.write(posmyservo);
    delay(10);
  }
  delay(500);
  compuerta.write(180);
  delay(500);
  compuerta.write(0);
  delay(500);
  
  moveServo(compuerta, angle, 2000);

  for (posmyservo = angle; posmyservo <= 180; posmyservo += 1) {
    myservo.write(posmyservo);
    delay(10);
  }
  delay(500);
}
