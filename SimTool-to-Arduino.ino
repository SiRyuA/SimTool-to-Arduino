#include <Servo.h>

Servo mAxis1;
Servo mAxis2;
Servo mAxis3;

char Read_Data;

int Degree,
    Gforce = 0,
    Gforce1 = 0,
    Gforce10 = 0,
    Gforce100 = 0;

void setup() {
  // put your setup code here, to run once:
  mAxis1.attach(2);
  mAxis2.attach(3);
  mAxis3.attach(4);
  
  mAxis1.write(0);
  mAxis2.write(0);
  mAxis3.write(0);
  
  Serial.begin(9600);
  
  ServoTest();
}

void loop() {
  // put your main code here, to run repeatedly:
  Read_Data_To_Axis();
}

void ServoTest(void) {
  for(char i=0;i<1;i++) {
    mAxis1.write(0);
    mAxis2.write(0);
    mAxis3.write(0);
    delay(1000);
    mAxis1.write(90);
    mAxis2.write(90);
    mAxis3.write(90);
    delay(1000);
    mAxis1.write(180);
    mAxis2.write(180);
    mAxis3.write(180);
    delay(1000);
  }
  mAxis1.write(90);
  mAxis2.write(90);
  mAxis3.write(90);
  delay(1000);
}

void Read_Data_To_Axis(void) {
  while(Serial.available() > 0) {
    Read_Data = Serial.read();
    
    if(Read_Data == 'L') Read_Pos(Read_Data);
    if(Read_Data == 'R') Read_Pos(Read_Data);
    if(Read_Data == 'C') Read_Pos(Read_Data);
  }
}

void Read_Pos(char which_servo) {
  delay(2);
  int Gforce100 = Serial.read()- '0';
  delay(2);
  int Gforce10  = Serial.read()- '0';
  delay(2);
  int Gforce1   = Serial.read()- '0';
  
  if(Gforce1 < 0) Gforce = Gforce10 + 10*Gforce100;
  if(Gforce1 < 0 && Gforce10 < 0) Gforce = Gforce100;
  if(Gforce100 < 0) Gforce = 127;
  if(Gforce1 >= 0 && Gforce10 >= 0 && Gforce100 >= 0) Gforce = 100 * Gforce100 + 10 * Gforce10 + Gforce1;
  
  Degree = map(Gforce, 0, 255, 0, 180);
  
  if(which_servo == 'R') mAxis1.write(Degree);
  if(which_servo == 'C') mAxis2.write(Degree);
  if(which_servo == 'L') mAxis3.write(Degree);
}
