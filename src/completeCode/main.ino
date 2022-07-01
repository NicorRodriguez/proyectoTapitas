#include <string.h>
#include "COLOR.h"
#include <Servo.h>

#include <TimedAction.h>
Servo myservo; 

bool onlyOnce = true;
int buttonState;
int pos = 0;


void motorStepper(){
  Serial.println("Hilo 1");
}

void changeText(){
  RGB_t c = COLOR_getRGB();
  //Serial.begin(19200);
  //Serial.println (COLOR_getColorName()); // Se obtiene el nombre del color que esté viendo el sensor y se imprime en el monitor (Herramientas > Monitor Serial)

  //Serial.end();
  discoGirador(myservo,COLOR_getColorName());
}

TimedAction stepperThread = TimedAction(1000,motorStepper);
TimedAction textThread = TimedAction(500,changeText);

void setup() {
  COLOR_init();
  //
   myservo.attach(0);
   myservo.write(0);
}

void loop() {
  
  stepperThread.check();
  textThread.check();
  Serial.end();
}

void compuerta(){
  Serial.println("com´peryf");
  for (pos = 120; pos >= 50; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
    };  
}

void girarMotor(int hasta){
  for (pos = 0; pos <= hasta; pos += 1) {
    myservo.write(pos);
    delay(10);
    Serial.begin(9600);
    Serial.println(pos);
    Serial.end();
  }
    Serial.begin(9600);
    Serial.println("****************");
    Serial.end();
  for (pos = hasta; pos >= 0; pos -= 1) {
    myservo.write(pos);
    Serial.begin(9600);
    Serial.println(pos);
    Serial.end();
    delay(1);
  }
}
void debug(int pos){
   Serial.begin(9600);
    Serial.println(pos);
    Serial.end();
  }
void EscribirPos(Servo myservo, int hasta){
  myservo.write(0);
  delay(500);
  myservo.write(hasta);
  
}

void discoGirador(Servo myservo, char* color){
  
  Serial.println(color);
  
  if(color == "NEGRO"){
    EscribirPos(myservo, 180);
    
  } if(color == "ROJO"){
    EscribirPos(myservo, 180);
   
  }if(color == "VERDE"){
   myservo.write(35);
  } if(color == "AZUL"){
   myservo.write(45); 
  } else {
    myservo.write(55);
  }

}
