#include <Wire.h>
#include <Adafruit_MCP4725.h>

int ch2; //right stick
int ch3; //Left stick

boolean killSwitch;

int leftMotor;
int rightMotor;
int leftStick;
int rightStick;

#define RELAY_ON 0
#define RELAY_OFF 1
#define RELAY_1 8
#define RELAY_2 9
#define RELAY_3 12

void setup() {
 
pinMode(6, INPUT); //Right Stick
pinMode(7, INPUT); //Left Stick

killSwitch = false;

digitalWrite(RELAY_1, RELAY_OFF); //Right motor controller//failsafe
digitalWrite(RELAY_2, RELAY_OFF); //Left Motor controller
digitalWrite(RELAY_3, RELAY_OFF); //failsafe


pinMode(RELAY_1, OUTPUT); //right motor controller//failsafe
pinMode(RELAY_2, OUTPUT); //left motor controller
pinMode(RELAY_3, OUTPUT); //failsafe

Serial.begin(9600);

}

void loop() {
  while(killSwitch == false){

 ch2 = pulseIn(6, HIGH, 250000); //Right Stick
 ch3 = pulseIn(7, HIGH, 250000); //Left Stick
 
 leftStick = ch3-1520;
 //leftMax =330;
 //leftMin =-315;
 rightStick = ch2 -1570; 
 //rightMax = 300
 //rightMin = -315
 
 //killswitch leftStick < -500
 
 Serial.print(map(leftStick, -300, 300, -170, 200)+20);
 Serial.print(" ");
 Serial.print(map(rightStick, -315, 300, -255, 255));
 Serial.println();
 
 if(rightStick > 30){
  digitalWrite(RELAY_1, RELAY_OFF);
  analogWrite(10, map(rightStick, -300, 300, -200, 200)+40);
 }else if(rightStick < -30){
  digitalWrite(RELAY_1, RELAY_ON);
  analogWrite(10, (abs(map(rightStick, -300, 300, -200, 200)-35)));
 }else{
  analogWrite(10, abs(rightStick));
 }
 
 if(leftStick < -500){
  digitalWrite(RELAY_3, RELAY_ON);
  killSwitch = true;
  
  }else if( leftStick > -400)
  {
    digitalWrite(RELAY_3, RELAY_OFF);
    
    
  }

 if(leftStick > 30){
  digitalWrite(RELAY_2, RELAY_OFF);
  analogWrite(11, map(leftStick, -300, 300, -200, 200));
  
 }else if(leftStick < -30 && leftStick > -400){
  digitalWrite(RELAY_2, RELAY_ON);
  analogWrite(11, (abs(map(leftStick, -300, 300, -200, 200)-25)));
  
 }else{
  analogWrite(11, abs(leftStick));
 }
  }
  if(killSwitch == true){
  analogWrite(10, 0);
  analogWrite(11, 0);
  }
}
