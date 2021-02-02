#include <Wire.h>
const int MPU2 = 0x69, MPU1=0x68;
///const int knockSensor = A0; // the piezo is connected to analog pin 0
//const int threshold = 15;  // threshold value to decide when the detected sound is a k
long accelX=0;
float gForceX=0;
//int sensorReading=0;
char val;
int BuzPin = 9;
int Capsensor=2;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(MPU1);
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 
  
  Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);
  Wire.write(0b00000000); 
  Wire.endTransmission();  
  Wire.beginTransmission(MPU2); 
  Wire.write(0x1B);
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);
  Wire.write(0b00000000);
  Wire.endTransmission(); 

  pinMode(BuzPin, OUTPUT);
  pinMode(Capsensor, INPUT);
  Serial.begin(9600);
  
}

void loop()
{
  GetMpuValue(MPU1);
  Serial.print(" ");
  GetMpuValue(MPU2);
  Serial.print(" ");

  if (digitalRead(Capsensor)== HIGH)
  {
    Serial.print("1 ");
    delay(200);
  }
  else 
    {
      Serial.print("0 ");
     }
    Serial.println();
}

void GetMpuValue(const int MPU)
{
  Wire.beginTransmission(MPU); 
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); 
  
  Wire.beginTransmission(MPU);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  while(Wire.available() < 6);
  gForceX = accelX / 16384.0;
  Serial.print(gForceX);

  if (Serial.available())
  {
    val=Serial.read();
  }
  if (val=='1')
  {  tone(BuzPin, 1000);
    delay(50);
    noTone(BuzPin);
  } else {
    noTone(BuzPin);
    
    
  }
}
