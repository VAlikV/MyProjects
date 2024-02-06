#include <GyverButton.h>
#include <FastLED.h>
#include <GyverPortal.h>
#include <list.h>
#include <log.h>
#include <portal.h>
#include <themes.h>
#include <utils.h>
#include <ESP8266SSDP.h>
#include <EEPROM.h>

#define LED_PIN  D4
#define BTN_PIN D1
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define LED_ROWS 16
#define LED_COLS 16
#define N_LEDS 256
#define ROWS 16
#define COLS 16 

GyverPortal portal;
IPAddress apIP(192, 168, 2, 2);

GButton butt1(BTN_PIN);

struct LampData {
  char ssid[32] = "---"; // Для хранения SSID *********************************************
  char pass[32] = "---"; // Для хранения пароля сети *********************************************
  char ssidAP[32] = "Ar_lux";   // SSID AP точки доступа
  char passAP[32] = "12213443"; // пароль точки доступа
};

LampData data;

String _ssid = String(data.ssid); 
String _pass = String(data.pass); 
String _ssidAP = String(data.ssidAP);   
String _passAP = String(data.passAP); 

bool flag_on = false;
byte mode0 = 0; //*********************************************


const bool    kMatrixSerpentineLayout = true;

//---------------------------------------------- Функции

uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( kMatrixSerpentineLayout == false) {
    i = (y * LED_COLS) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (LED_COLS - 1) - x;
      i = (y * LED_COLS) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * LED_COLS) + x;
    }
  }
  
  return i;
}

CRGB leds_plus_safety_pixel[ N_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

uint16_t XYsafe( uint8_t x, uint8_t y)
{
  if( x >= LED_COLS) return -1;
  if( y >= LED_ROWS) return -1;
  return XY(x,y);
}

//---------------------------------------------- Переменные

//Параметры режимов

byte BRIGHTNESS = 5; // 10 - 100 *********************************************
byte last_BRIGHTNESS = 10;

// 1 - Моно

int color_mono = 16711680; // 0 - 255 *********************************************
int last_color_mono = 16711680;

// 2 - Перелив

byte hue_play = 0;
byte speed_play = 10;  // 10 - 100 *********************************************
byte last_speed_play = 10;

// 3 -  Огонь

byte flag_fire = 0; // 0 - 3 *********************************************
byte last_flag_fire = 0;
byte scale_fire = 64;
byte speed_fire = 60; // 5 - 80 *********************************************
byte last_speed_fire = 60;

// 4 - Зебра

byte speed_zebra = 20; // 1 - 255 *********************************************
byte last_speed_zebra = 20;
byte scale_zebra = 30; // 1 - 100 *********************************************
byte last_scale_zebra = 30;
//byte SCALE = 21;
//byte SPEED = 8;

// 5 - Радуга

byte flag_rain = 0; // 0 - 3 *********************************************
byte last_flag_rain = 0;
byte speed_rain = 3;

// 6 - Разводы

byte hue_stains = 100; // 0 - 255 *********************************************
byte last_hue_stains = 100;
byte scale_stains = 30;    // 5 - 100 *********************************************
byte last_scale_stains = 30; 

// 7 - Кольца

// 8 - Змейки

byte speed_nexus = 50; // 10 - 100 *********************************************
byte last_speed_nexus = 50;
byte scale_nexus = 200; // 50 - 250 *********************************************
byte last_scale_nexus = 200;

// 9 - Конфети

byte hue_confetti = 255; // 0 - 255 *********************************************
byte last_hue_confetti = 255;

// 10 - Северное сияния

byte speed_aurora = 127; // 1-255 *********************************************
byte last_speed_aurora = 127;
byte scale_aurora = 60;  

// 11 - Звезды

// 12 - Песок

byte hue_send = 30; //0 - 255 *********************************************
byte last_hue_send = 30;

// Прочее

byte led_flag = 1;
unsigned long last_t;

// Отображение

byte first = 2; // ****************************************************
byte second = 2;

// Цифры

int numbers[10][15][2] = {{{0,0}, {1,0}, {2,0}, {0,1}, {0,2}, {0,3}, {0,4}, {2,1}, {2,2}, {2,3}, {2,4}, {1,4}, {0,0}, {0,0}, {0,0}}, //0
{{0,0}, {1,0}, {2,0}, {1,1}, {1,2}, {1,3}, {1,4}, {0,3}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}, {0,0}}, //1
{{0,0}, {1,0}, {2,0}, {0,1}, {1,2}, {2,3}, {2,4}, {2,4}, {1,4}, {0,4}, {2,2}, {0,2}, {0,0}, {0,0}, {0,0}}, //2
{{0,0}, {1,0}, {2,0}, {2,1}, {0,2}, {2,3}, {0,4}, {1,2}, {2,2}, {0,0}, {1,4}, {2,4}, {0,0}, {0,0}, {0,0}}, //3
{{2,0}, {2,1}, {0,2}, {0,3}, {0,4}, {1,2}, {2,2}, {2,3}, {2,4}, {2,0}, {2,0}, {2,0}, {2,0}, {2,0}, {2,0}}, //4
{{0,0}, {1,0}, {2,0}, {2,1}, {1,2}, {0,3}, {0,4}, {1,4}, {2,4}, {0,0}, {2,2}, {0,2}, {0,0}, {0,0}, {0,0}}, //5
{{0,0}, {1,0}, {2,0}, {0,1}, {2,1}, {1,2}, {0,3}, {2,4}, {1,4}, {0,4}, {0,2}, {2,2}, {0,0}, {0,0}, {0,0}}, //6
{{2,0}, {2,1}, {2,2}, {2,3}, {0,4}, {1,4}, {2,4}, {2,0}, {2,0}, {2,0}, {2,0}, {2,0}, {2,0}, {2,0}, {2,0}}, //7
{{0,0}, {1,0}, {2,0}, {0,2}, {1,2}, {2,2}, {0,4}, {1,4}, {2,4}, {0,1}, {2,1}, {2,3}, {0,3}, {0,0}, {0,0}}, //8
{{0,0}, {1,0}, {2,0}, {0,2}, {1,2}, {2,2}, {0,4}, {1,4}, {2,4}, {2,1}, {0,0}, {2,3}, {0,3}, {0,0}, {0,0}}}; //9


DEFINE_GRADIENT_PALETTE(firepal_red) { 
  0,  0,  0,  0, //black
  32,  255,  0,  0, // red
  190,  255,  255,  0, //yellow
  255,  255,  255,  255 // white
};

DEFINE_GRADIENT_PALETTE(firepal_green) {
  0,  0,  0,  0, 
  32,  0,  255,  0, 
  120,  255,  255,  0, 
  255,  255,  255,  255 
};

DEFINE_GRADIENT_PALETTE(firepal_blue) { 
  0,  0,  0,  0, 
  72,  52,  102,  255, 
  25,  51,  200,  255, 
  255,  255,  255,  255 
};

DEFINE_GRADIENT_PALETTE(firepal_purp) { 
  0,  0,  0,  0, 
  50,  180, 0,  200, 
  10,  153,  85,  200, 
  255,  255,  255,  255 
};;

CRGB white1 = CRGB(155, 155, 155);

void loop() //----------------------------------------------------- Loop
{
  
  FastLED.setBrightness( BRIGHTNESS );

  butt1.tick();

  convert2_data();
  
  if (butt1.isSingle()) flag_on = !flag_on;
  
 /* 
  if (butt1.isTriple()) {
     _ssid = ""; 
     _pass = ""; 
     draw_reset();
     convert_data();
     EEPROM.put(1, data);
     FastLED.show();
     delay(500);
     draw_off(); 
     FastLED.show();
     delay(2000);  
  }
  */
  
  portal.tick();

  if (portal.click()) {
    if ((portal.click("on_off")) && (portal.getString("on_off") == "1")) flag_on = true;
    if ((portal.click("on_off")) && (portal.getString("on_off") == "0")) flag_on = false;
    if (portal.click("BR")) BRIGHTNESS = portal.getInt("BR");
  }
  
  if (!flag_on) {
    portal.attachBuild(build_off);
    draw_off(); 
  }
  else {
    if ((portal.click("mode")) && (portal.getString("mode") == "Mono")) mode0 = 0;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Play")) mode0 = 1;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Fire")) mode0 = 2;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Zebra")) mode0 = 3;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Rainbow")) mode0 = 4;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Stains")) mode0 = 5;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Rings")) mode0 = 6;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Nexus")) mode0 = 7;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Confetti")) mode0 = 8;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Aurora")) mode0 = 9;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Stars")) mode0 = 10;
    else if ((portal.click("mode")) && (portal.getString("mode") == "Send")) mode0 = 11;
    portal.attachBuild(build_on);
    switch(mode0){
      case 0: //Mono
        if (portal.click()) {
          if (portal.click("color_mono")) color_mono = portal.getColor("color_mono");
          if (portal.click("reset")){
            color_mono = last_color_mono;
          }
        }
        draw_Mono();      
      break;
      case 1: //-------------------------------------------------------------------------------------------Play
        if (portal.click()) {
          if (portal.click("speed_play")) speed_play = portal.getInt("speed_play");
          if (portal.click("reset")){
            speed_play = last_speed_play;
          }
        }
        draw_Play();
      break;
      case 2: //-------------------------------------------------------------------------------------------Fire
        if (portal.click()) {
          
          if ((portal.click("color_fire")) && (portal.getString("color_fire") == "Red")) flag_fire = 0;
          else if ((portal.click("color_fire")) && (portal.getString("color_fire") == "Green")) flag_fire = 1;
          else if ((portal.click("color_fire")) && (portal.getString("color_fire") == "Blue")) flag_fire = 2;
          else if ((portal.click("color_fire")) && (portal.getString("color_fire") == "Purp")) flag_fire = 3;
          
          if (portal.click("speed_fire")) speed_fire = portal.getInt("speed_fire");
          if (portal.click("reset")){
            flag_fire = last_flag_fire;
            speed_fire = last_speed_fire;
          }
        }
        draw_Fire();   
      break;
      case 3: //-------------------------------------------------------------------------------------------Zebra
        if (portal.click()) {
          if (portal.click("scale_zebra")) scale_zebra = portal.getInt("scale_zebra");
          if (portal.click("speed_zebra")) speed_zebra = portal.getInt("speed_zebra");
          if (portal.click("reset")){
            scale_zebra = last_scale_zebra;
            speed_zebra = last_speed_zebra;
          }
        }
        draw_Zebra();
      break;
      case 4://-------------------------------------------------------------------------------------------Rainbow
        if (portal.click()) {
          if ((portal.click("mode_rainbow")) && (portal.getString("mode_rainbow") == "_1_")) flag_rain = 0;
          else if ((portal.click("mode_rainbow")) && (portal.getString("mode_rainbow") == "_2_")) flag_rain = 1;
          else if ((portal.click("mode_rainbow")) && (portal.getString("mode_rainbow") == "_3_")) flag_rain = 2;
          else if ((portal.click("mode_rainbow")) && (portal.getString("mode_rainbow") == "_4_")) flag_rain = 3;
          if (portal.click("reset")){
            flag_rain = last_flag_rain;
          }
        }
        draw_Rainbow();              
      break;
      case 5://-------------------------------------------------------------------------------------------Stains
        if (portal.click()) {
          if (portal.click("scale_stains")) scale_stains = portal.getInt("scale_stains");
          if (portal.click("color_stains")) hue_stains = portal.getInt("color_stains");
          if (portal.click("reset")){
            hue_stains = last_hue_stains;
            scale_stains = last_scale_stains;
          }
        }
        draw_Stains();  
      break;
      case 6://-------------------------------------------------------------------------------------------Rings
        draw_Rings();      
      break;
      case 7://-------------------------------------------------------------------------------------------Nexus
        if (portal.click()) {
          if (portal.click("scale_nexus")) scale_nexus = portal.getInt("scale_nexus");
          if (portal.click("speed_nexus")) speed_nexus = portal.getInt("speed_nexus");
          if (portal.click("reset")){
            scale_nexus = last_scale_nexus;
            speed_nexus = last_speed_nexus;
          }
        }
        draw_Nexus();
      break;
      case 8://-------------------------------------------------------------------------------------------Confetti
        if (portal.click()) {
          if (portal.click("color_confetti")) hue_confetti = portal.getInt("color_confetti");
          if (portal.click("reset")){
            hue_confetti = last_hue_confetti;
          }
        }
        draw_Confetti();
      break;
      case 9://-------------------------------------------------------------------------------------------Aurora
        if (portal.click()) {
          if (portal.click("speed_aurora")) speed_aurora = portal.getInt("speed_aurora");
          if (portal.click("reset")){
            speed_aurora = last_speed_aurora;
          }
        }
        draw_Aurora();
      break;
      case 10://-------------------------------------------------------------------------------------------Stars
        draw_Stars();
      break;
      case 11://-------------------------------------------------------------------------------------------Send
        if (portal.click()) {
          if (portal.click("color_send")) hue_send = portal.getInt("color_send");
          if (portal.click("reset")){
            hue_send = last_hue_send;
          }
        }
        draw_Send();      
      break;
    }
  } //switch
  FastLED.show();
  if (portal.form()) {
  if (portal.form("/login")){
    _ssid = portal.getString("Log");
    _pass = portal.getString("Pass");
    convert_data();
    EEPROM.put(1, data);
    EEPROM.commit();
  }
}
}


void setup() { //----------------------------------------------------------- Setup
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, N_LEDS).setCorrection(TypicalSMD5050);
  Serial.begin(115200);
  
  
  EEPROM.begin(sizeof(data) + 1);
  
  /*
  for (int i = 0; i < EEPROM.length(); i++) EEPROM.put(i, 0);
  EEPROM.commit();
  */
  
  if (EEPROM.read(0) != 'a'){
    EEPROM.put(1, data);
    EEPROM.put(0,'a');
    EEPROM.commit();
  } else {
    EEPROM.get(1, data);
  }
  convert2_data();
  butt1.setTimeout(5000); 
  FastLED.setBrightness( BRIGHTNESS );
  WIFIinit();
  EEPROM.put(1, data);
  EEPROM.commit();
  portal.start();

  if (first < 10){
    vvod_odn1(first);
  } else if (first >= 100){
    vvod_tr1(first);
  } else {
    vvod_dva1(first);
  }
    if (second < 10){
    vvod_odn2(second);
  } else if (second >= 100){
    vvod_tr2(second);
  } else {
    vvod_dva2(second);
  }
  
  FastLED.show();
  delay(5000);
  draw_off();
  FastLED.show();

  
}


//-----------------------------------------------------------------------------------
static uint32_t t;
void draw_Fire() {
  CRGBPalette16 myPal_red(firepal_red);
  CRGBPalette16 myPal_green(firepal_green);
  CRGBPalette16 myPal_blue(firepal_blue);
  CRGBPalette16 myPal_purp(firepal_purp);
  t += speed_fire;
  for (byte x = 0; x < LED_COLS; x++) {
    for (byte y = 0; y < LED_ROWS; y++) {
     
      int16_t Bri = inoise8(x * scale_fire, (y * scale_fire) - t) - (y * (255 / LED_ROWS));
      byte Col = Bri;
       if (Bri < 0) Bri = 0; if(Bri != 0) Bri = 256 - (Bri * 0.2);
       switch(flag_fire){
        case 0: nblend(leds[XY(x, y)], ColorFromPalette(myPal_red, Col, Bri), speed_fire); break;
        case 1: nblend(leds[XY(x, y)], ColorFromPalette(myPal_green, Col, Bri), speed_fire); break;
        case 2: nblend(leds[XY(x, y)], ColorFromPalette(myPal_blue, Col, Bri), speed_fire); break;
        case 3: nblend(leds[XY(x, y)], ColorFromPalette(myPal_purp, Col, Bri), speed_fire); break;        
       }
     }
  }
}


//--------------------------------------------------------------------------------------------------------------------------------

void convert_data(){
  _ssid.toCharArray(data.ssid,32);
  _pass.toCharArray(data.pass,32);
  _ssidAP.toCharArray(data.ssidAP,32);
  _passAP.toCharArray(data.passAP,32);
}

void convert2_data(){
  _ssid = String(data.ssid); 
  _pass = String(data.pass); 
  _ssidAP = String(data.ssidAP);   
  _passAP = String(data.passAP); 
}

//---------------------------------------------------------------------------------------------------------------------------------

void vvod_odn1(byte x){
  for (int index = 0; index < 15; index+=1) {
    leds[XY(6+numbers[x][index][0],9+numbers[x][index][1])] = white1;
  }
}

void vvod_odn2(byte x){
  for (int index = 0; index < 15; index+=1) {
    leds[XY(6+numbers[x][index][0],2+numbers[x][index][1])] = white1;
  }
}

void vvod_dva1(byte y){
  for (int index = 0; index < 15; index+=1) {
    leds[XY(8+numbers[y%10][index][0],9+numbers[y%10][index][1])] = white1;
    leds[XY(4+numbers[y/10][index][0],9+numbers[y/10][index][1])] = white1;
  }
}

void vvod_dva2(byte y){
  for (int index = 0; index < 15; index+=1) {
    leds[XY(8+numbers[y%10][index][0],2+numbers[y%10][index][1])] = white1;
    leds[XY(4+numbers[y/10][index][0],2+numbers[y/10][index][1])] = white1;
  }
}

void vvod_tr1(byte z){
  for (int index = 0; index < 15; index+=1) {
    leds[XY(10+numbers[z%10][index][0],9+numbers[z%10][index][1])] = white1;
    leds[XY(6+numbers[(z/10)%10][index][0],9+numbers[(z/10)%10][index][1])] = white1;
    leds[XY(2+numbers[z/100][index][0],9+numbers[z/100][index][1])] = white1;
  }
}


void vvod_tr2(byte z){
  for (int index = 0; index < 15; index+=1) {
    leds[XY(10+numbers[z%10][index][0],9+numbers[z%10][index][1])] = white1;
    leds[XY(6+numbers[(z/10)%10][index][0],9+numbers[(z/10)%10][index][1])] = white1;
    leds[XY(2+numbers[z/100][index][0],9+numbers[z/100][index][1])] = white1;
  }
}
