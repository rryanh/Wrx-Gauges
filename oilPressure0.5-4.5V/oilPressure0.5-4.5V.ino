#include <U8g2lib.h>
#include <U8x8lib.h>
#include <Arduino.h>
#include <math.h> 
#include <SPI.h>
#include <Wire.h>

int oilPressure;
int analogVoltage;
float voltage;
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
   voltage =  analogVoltage * 5.0 / 1023.0;
   oilPressure = 37.5 * voltage - 18.8;
   u8g2.clearBuffer();        
   u8g2.setFont(u8g2_font_profont29_tf); 
   u8g2.drawStr(10,20, "OIL PSI"); 
   u8g2.setFont(u8g2_font_7Segments_26x42_mn); 
   u8g2.setCursor(10,64);
   if ( oilPressure < 0){
     u8g2.print(0);
   }else{
    u8g2.print(oilPressure - 14.7);
   }
   u8g2.sendBuffer();  
   delay(150); 
}
