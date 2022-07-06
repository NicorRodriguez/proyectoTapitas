#include <string.h>
#include "COLOR.h"
#include <Servo.h>
#include <Stepper.h>

Servo compuerta;
Servo myservo;

bool onlyOnce = true;
int buttonState;
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
  myservo.write(0);
  compuerta.write(90);
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
  if(color == "ROJO") return 20;
  if(color == "AZUL") return 55;
  if(color == "VERDE") return 90;
  if(color == "NEGRO") return 125;
  else return 160;
}

void loop() {
  RGB_t c = COLOR_getRGB();
  moveServo(myservo, 90, 0);
  Serial.println(COLOR_getColorName());

  
  angle = angleByColor("NEGRO");
  compuerta.write(angle);
  myStepper.step(stepsPerRevolution);
  delay(10);
  
  //moveServo(compuerta, angle, 2000);
}
