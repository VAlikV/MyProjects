#include <GyverNTC.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>
#include <GyverButton.h>
//#include <GyverOLED.h>

Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
GyverNTC therm(A1, 10000, 3435);
GButton butt1(9);
GButton butt2(8);
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;

float zero[16] = {2.4964, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4435, 2.4964};
float sens[16] = {3.118, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.418, 3.118}; // мВ/Гаусс 
int16_t adc0;
double volts;
float B, Bs, t;
int chanel = 0;
unsigned long last_time;
int num = 0;
int avg = 10;
int ae = 0;


bool ch[16][4] = {{0, 0, 0, 0},
{0, 0, 0, 1},
{0, 0, 1, 0},
{0, 0, 1, 1},
{0, 1, 0, 0},
{0, 1, 0, 1},
{0, 1, 1, 0},
{0, 1, 1, 1},
{1, 0, 0, 0},
{1, 0, 0, 1},
{1, 0, 1, 0},
{1, 0, 1, 1},
{1, 1, 0, 0},
{1, 1, 0, 1},
{1, 1, 1, 0},
{1, 1, 1, 1}};

void setup(void)
{
  Serial.begin(9600);
  
  //oled.init();        // инициализация
  //oled.clear();       // очистка
  
  ads.setGain(GAIN_ONE);  // 2/3x gain +/- 6.144V    0.1875mV (default)

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

  butt2.setTimeout(1000);
  
  pinMode(2,OUTPUT);
  
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  
  digitalWrite(6,LOW);
  
  digitalWrite(5,LOW);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,LOW);

  last_time = millis();
}

void loop(void)
{

  butt1.tick();
  butt2.tick(); 
  
  if (butt1.isClick()) 
  {
    chanel++;
    if (chanel == 16) chanel = 0;
    digitalWrite(5,ch[chanel][0]);
    digitalWrite(4,ch[chanel][1]);
    digitalWrite(3,ch[chanel][2]);
    digitalWrite(2,ch[chanel][3]);
    volts = 0;
    num = 0;
  }    

  if (butt2.isHolded()) 
  {
    Serial.println("Get ready");
    delay(1000);
    num = 0;
    volts = 0;
    for (int i = 0; i < 10; i++){
      adc0 = ads.readADC_SingleEnded(0);
      volts += ads.computeVolts(adc0);
    }
    zero[chanel] = volts/10;
    volts = 0;
    Serial.print("Set zero: ");Serial.println(zero[chanel],4);
  } 
  
  if ((millis()-last_time) > 25){
    last_time = millis();
    
    if  (num != avg){
      adc0 = ads.readADC_SingleEnded(0);
      volts += ads.computeVolts(adc0);
      num++;
    }
    else{
      volts = volts/avg;
      B = (volts-zero[chanel])/(sens[chanel]/1000);
      t = therm.getTempAverage();
      Serial.print(chanel);Serial.print(") ");Serial.print(t);Serial.print(" °C  ");Serial.print(volts,4); Serial.print("V"); Serial.print("  "); Serial.print(B,0); Serial.print(" Gauss      ");Serial.print(zero[chanel],4); Serial.println(" V");
      volts = 0;
      num = 0;
    }
  }
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
