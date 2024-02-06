#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <Adafruit_ADS1X15.h>
#include <Wire.h>

#include <GyverNTC.h>

#define FILESYSTEM SPIFFS

#if FILESYSTEM == FFat
#include <FFat.h>
#endif
#if FILESYSTEM == SPIFFS
#include <SPIFFS.h>
#endif

#define ENABLE 13
#define A0 12
#define A1 14
#define A2 27
#define A3 26

#define NTC 6

/*
Adafruit_ADS1115 ads0(0x48);
Adafruit_ADS1115 ads1(0x49);
Adafruit_ADS1115 ads2(0x4B);
Adafruit_ADS1115 ads3(0x4A);
*/

//GyverNTC therm(NTC, 10000, 3435);

IPAddress apIP(192, 168, 4, 1);

// Web интерфейс для устройства
WebServer HTTP(80);
// Для файловой системы
File fsUploadFile;

struct Setings {
  float zero[128];  // Уровень нуля
  float sens[128];  // Чувствительность датчиков холла (мВ/Гаусс) 
};

Setings setings;
Setings last_setings;

float voltage[128];
float field[128];

byte selected_chanel = 0;

bool chanels[16][4] = {{0, 0, 0, 0},
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

unsigned long timer;
int n_adc0, n_adc1, n_adc2, n_adc3;
float ntc_temp = 25.0;

// Определяем переменные wifi
String _ssidAP = "Magnitometr";   // SSID AP точки доступа
String _passwordAP = "mmmmmmmm"; // пароль точки доступа

void setup() {
  
  Serial.begin(115200);
  
  // ----------------------------------------------------------------------------- Инициализация массивов

  for(int i=0; i<128; i++){
    last_setings.zero[i] = 2.4435;
    last_setings.sens[i] = 3.418;
    setings.zero[i] = 2.4435;
    setings.sens[i] = 3.418;
    voltage[i] = 1.23456;
    field[i] = 9.87654;
  }
  
  // ----------------------------------------------------------------------------- Инициализация GPIO и ADC
    
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ENABLE,OUTPUT);
  
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);

  digitalWrite(ENABLE,LOW);
  
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(A3,LOW);
  
  /*
  ads0.setGain(GAIN_ONE);  // 2/3x gain +/- 6.144V    0.1875mV (default)
  ads1.setGain(GAIN_ONE);
  ads2.setGain(GAIN_ONE);
  ads3.setGain(GAIN_ONE);
  
  if (!ads0.begin()||!ads1.begin()||!ads2.begin()||!ads3.begin()) {
    Serial.println("Failed to initialize ADS.");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  */

  // ----------------------------------------------------------------------------- Инициализация сервера
  
  delay(3000);
  Serial.println("");
  //Запускаем файловую систему 
  Serial.println("Start FS");
  FS_init();
  Serial.println("Start WIFI");
  //Запускаем WIFI
  StartAPMode();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start WebServer");
  HTTP_init();

  timer = millis();
}



void loop() {
  HTTP.handleClient();
 /*
  if ((millis()-timer) >= 15){
    if (selected_chanel == 16){
      selected_chanel = 0;
    }
    
    digitalWrite(A0,chanels[selected_chanel][0]);
    digitalWrite(A1,chanels[selected_chanel][1]);
    digitalWrite(A2,chanels[selected_chanel][2]);
    digitalWrite(A3,chanels[selected_chanel][3]);
    delay(1);

    voltage[0+selected_chanel] = ads0.computeVolts(ads0.readADC_Differential_0_1());
    field[0+selected_chanel] = 1000*(voltage[0+selected_chanel]-setings.zero[0+selected_chanel])/setings.sens[0+selected_chanel];
    
    voltage[16+selected_chanel] = ads0.computeVolts(ads0.readADC_Differential_2_3());
    field[16+selected_chanel] = 1000*(voltage[16+selected_chanel]-setings.zero[16+selected_chanel])/setings.sens[16+selected_chanel];

    voltage[32+selected_chanel] = ads1.computeVolts(ads1.readADC_Differential_0_1());
    field[32+selected_chanel] = 1000*(voltage[32+selected_chanel]-setings.zero[32+selected_chanel])/setings.sens[32+selected_chanel];
    
    voltage[48+selected_chanel] = ads1.computeVolts(ads1.readADC_Differential_2_3());
    field[48+selected_chanel] = 1000*(voltage[48+selected_chanel]-setings.zero[48+selected_chanel])/setings.sens[48+selected_chanel];

    voltage[64+selected_chanel] = ads2.computeVolts(ads2.readADC_Differential_0_1());
    field[64+selected_chanel] = 1000*(voltage[64+selected_chanel]-setings.zero[64+selected_chanel])/setings.sens[64+selected_chanel];
    
    voltage[80+selected_chanel] = ads2.computeVolts(ads2.readADC_Differential_2_3());
    field[80+selected_chanel] = 1000*(voltage[80+selected_chanel]-setings.zero[80+selected_chanel])/setings.sens[80+selected_chanel];

    voltage[96+selected_chanel] = ads3.computeVolts(ads3.readADC_Differential_0_1());
    field[96+selected_chanel] = 1000*(voltage[96+selected_chanel]-setings.zero[96+selected_chanel])/setings.sens[96+selected_chanel];
    
    voltage[112+selected_chanel] = ads3.computeVolts(ads3.readADC_Differential_2_3());
    field[112+selected_chanel] = 1000*(voltage[112+selected_chanel]-setings.zero[112+selected_chanel])/setings.sens[112+selected_chanel];

    selected_chanel++;    
    timer = millis();
  }
*/
}
