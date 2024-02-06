#include <GyverNTC.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>
//#include <GyverOLED.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
GyverNTC therm(1, 10000, 3435);
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;

float zero = 2.4435;
float sens = 3.418; // мВ/Гаусс 
int16_t adc0;
float volts0, Us;
float B, Bs, t;

void setup(void)
{
  Serial.begin(9600);
  
  //oled.init();        // инициализация
  //oled.clear();       // очистка
  
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V    0.1875mV (default)

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
}

void loop(void)
{
  volts0 = 0;
  Bs = 0;
  t = 0;
  for (int i = 0; i < 30; i++) {
    adc0 = ads.readADC_SingleEnded(0);
    volts0 += ads.computeVolts(adc0);
    //Us += volts0;
  }
  t = therm.getTempAverage();
  volts0 = volts0/30;
  B = (volts0-zero)/(sens/1000);
  
  Serial.print(t);Serial.print(" °C  ");Serial.print(volts0,4); Serial.print("V"); Serial.print("  "); Serial.print(B,0); Serial.println(" Gauss");
  //printOled();
  delay(1);
}

/*
void printOled(){        //---------------------------------------------------------------- Print
  oled.clear();       // очистка  
  oled.setScale(1);
  oled.setCursorXY(10,5);
  oled.print("B = "); oled.print(B,1); oled.print(" Гаусс");  
  oled.setCursorXY(10,20);
  oled.print("U = "); oled.print(volts0,4); oled.print(" В"); 
  oled.update();
}
*/
