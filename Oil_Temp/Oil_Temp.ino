#include <U8g2lib.h>
#include <U8x8lib.h>
#include <Arduino.h>
#include <math.h> 
#include <SPI.h>
#include <Wire.h>

int oilTemp;
float voltageMeasured = 0;
float voltage5v = 5;
float resistorKnown = 100; // this is the resistor you choose 
float resistorUnknown = 0; // oil presure sensor, should be ~0-180 ohms ish
float buffer=0;
int analogVoltage = 115;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0);


void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
  
}

void loop(void) {
float analogAvg = 0;
  for( int i = 0; i < 100; i++){
    analogVoltage = analogRead(A1);
    analogAvg = analogAvg + analogVoltage;
    delay(1);
  }
  Serial.println(analogAvg);
   analogVoltage = analogAvg / 100 ;
   voltageMeasured  =  analogVoltage * 5.0 / 1023.0;
   buffer = voltageMeasured / (voltage5v - voltageMeasured);
   resistorUnknown = resistorKnown * buffer;
   oilTemp = 254 + (-32 * log(resistorUnknown));
   u8g2.clearBuffer();        
   u8g2.setFont(u8g2_font_profont29_tf); 
   u8g2.drawStr(0,20, "OIL TEMP"); 
   u8g2.setFont(u8g2_font_7Segments_26x42_mn); 
   u8g2.setCursor(10,64);
   if ( oilTemp < 0){
     u8g2.print("-" + oilTemp);
   }else{
    u8g2.print(oilTemp);
   }
   u8g2.sendBuffer();  
   delay(900); 
}
