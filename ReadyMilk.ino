#include <math.h>
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


#define LED 2
const int B=3975;                 // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;  // Grove - Temperature Sensor connect to A0
int cur;
int prev;
int colorR;
int colorG;
int colorB;
int T = 36;

void setup()
{
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // initialize the serial communications;
}

void loop()
{
    int a = analogRead(pinTempSensor );
 
    float R = 1023.0/((float)a)-1.0;
    R = 100000.0*R;
    
    if(Serial.available())
    {
      T = Serial.parseInt();
      Serial.print("Imput Temperature: ");
      Serial.println(T);
    }
 
    float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;//convert to temperature via datasheet;

 
    delay(100);
    
    if(temperature > T)
    {
      cur = 3;
    }
    else if( temperature <= T && temperature > T-5)
    {
      cur = 2;
    }
    else if(temperature <= T-5)
    {
      cur = 1;
    }
    
    if(cur == 1 && cur != prev)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("TOO COLD!");
      colorB = 255;
      lcd.setRGB(colorR, colorG, colorB);
    }
    if(cur == 2 && cur != prev)
   {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("READY");
     colorG = 255;
     lcd.setRGB(colorR, colorG, colorB);

   } 
   if( cur == 3 && cur != prev)
   {
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("TOO HOT!");
     colorR = 255;
     lcd.setRGB(colorR, colorG, colorB);
   }
   lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.print( temperature);
      lcd.print("-C");
      delay(1000);
      
    prev = cur;
    colorR = 0;
    colorG = 0;
    colorB = 0;
 
}
