#include <LiquidCrystal.h>

const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;
LiquidCrystal pH_lcd(2, 3, 4, 5, 6, 7);
void setup() {
 Serial.begin(9600);
 pH_lcd.begin(16, 2);
 pH_lcd.setCursor(0, 0);
 pH_lcd.print("pH Reading");  

}

void loop() {
 for(int i=0;i<10;i++) 
 { 
  buf[i]=analogRead(analogInPin);
  delay(10);
 }
 for(int i=0;i<9;i++)
 {
  for(int j=i+1;j<10;j++)
  {
   if(buf[i]>buf[j])
   {
    temp=buf[i];
    buf[i]=buf[j];
    buf[j]=temp;
   }
  }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -5.70 * pHVol + 21.34;
 Serial.print("sensor = ");
 Serial.println(phValue);
 pH_lcd.setCursor(0, 1);
 pH_lcd.print(phValue);
 delay(1000);
}
