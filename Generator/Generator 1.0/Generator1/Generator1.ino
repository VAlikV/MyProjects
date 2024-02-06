#include <GyverOLED.h>
#include <AD9833.h>
#include <GyverEncoder.h>

#define FPS 3
#define Ssecond 5
#define Sfirst 3
#define KEY 2
#define PIN_CS 4

Encoder enc (9, 8, 10, TYPE2);
GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
AD9833 myGen (PIN_CS);

byte x_sin[16] = {1,2,3,4,6,7,8,9,11,12,13,14,16,17,18,19};
byte y_sin[16] = {1,0,0,1,5,6,6,5,1,0,0,1,5,6,6,5};

struct Data{
  float freq = 1000.0;
  int waveform = 0;
  byte pos = 0;
  byte mode = 0;
};

Data data;
Data lastdata;

byte curs[2] = {31,47};

bool temp1 = 0;
byte temp2 = 0;

void setup() {        //---------------------------------------------------------------- SETUP
  myGen.begin(); 
  oled.init();        // инициализация
  oled.clear();       // очистка
  printMenu();
  myGen.generate(FREQ0, 1000, WAVEFORM_SQUARE);
}

void loop() {        //---------------------------------------------------------------- LOOP

  encoder();
  if (Sravn()){
    printMenu();
    eqv();
    switch (data.waveform){
      case 0:
        myGen.generate(FREQ0, data.freq, WAVEFORM_SQUARE);
      break;
      case 1:
        myGen.generate(FREQ0, data.freq, WAVEFORM_TRIANGLE);
      break;
      case 2:
        myGen.generate(FREQ0, data.freq, WAVEFORM_SINE);
      break;
    }
  }
}

void printMenu(){        //---------------------------------------------------------------- MENU
  oled.clear();       // очистка
  oled.setScale(2);   // масштаб текста (1..4)
  oled.setCursor(17,0);        // курсор в 0,0
  oled.print("Gen v1.1");

  oled.line(5,21,122,21);
  
  oled.setScale(1);
  oled.setCursorXY(7,curs[data.pos]);
  oled.print(">");
  
  
  // курсор на начало 3 строки
  oled.setCursorXY(20, 31);
  oled.print("FORM: ");
  switch(data.waveform){
    case 0: oled.line(57,37,62,37);
      oled.line(62,37,62,31);
      oled.line(62,31,67,31);
      oled.line(67,37,67,31);
      oled.line(68,37,72,37);
      oled.line(72,37,72,31);
      oled.line(72,31,77,31);
      oled.line(77,37,77,31);
    break;
    case 1: oled.line(56,37,62,31);
      oled.line(62,31,68,37);
      oled.line(68,37,74,31);
      oled.line(74,31,80,37);
    break;
    case 2: for (int index = 0; index < 16; index++) {
        oled.dot(57+x_sin[index],31+y_sin[index]);
      }
      oled.line(57,33,57,34);
      oled.line(62,33,62,35);
      oled.line(67,33,67,35);
      oled.line(72,33,72,35);
    break;
  }
  
  oled.setCursorXY(20, 47);
  oled.print("FREQ: ");
  switch (data.mode){
    case 0: oled.print(data.freq,0); oled.print(" Гц"); break;
    case 1: oled.print(data.freq/1000,2); oled.print(" кГц"); break;
    case 2: oled.print(data.freq/1000000,2); oled.print(" МГц"); break;
  }
  oled.line(5,63,122,63);
  oled.update();
}

void encoder(){        //---------------------------------------------------------------- ENCODER
  enc.tick();
  if (enc.isSingle()){
    if (data.pos == 0) data.pos = 1;
    else data.pos = 0; 
  }
  if (data.pos == 0){
    if (enc.isRight()) data.waveform++;
    if (enc.isLeft()) data.waveform--;
    if (data.waveform < 0) data.waveform = 2;
    if (data.waveform > 2) data.waveform = 0;
    if (enc.isDouble()) data.freq = 1000;
  }
  else{
    if (enc.isDouble()){
      data.mode++;
      if (data.mode == 3) data.mode = 0;
    }
    switch (data.mode){
      case 0: 
        if (enc.isRight()) data.freq++;
        if (enc.isLeft()) data.freq--;
        if (enc.isRightH()) data.freq += 100;
        if (enc.isLeftH()) data.freq -= 100;
        data.freq = constrain(data.freq,0,100000); 
      break;
      case 1:
        if (enc.isRight()) data.freq += 1000;
        if (enc.isLeft()) data.freq -= 1000;
        if (enc.isFastR()) data.freq += 10000;
        if (enc.isFastL()) data.freq -= 10000;
        if (enc.isRightH()) data.freq += 100000;
        if (enc.isLeftH()) data.freq -= 100000;
        data.freq = constrain(data.freq,0,1000000);
      break;
      case 2:
        if (enc.isRight()) data.freq += 500000;
        if (enc.isLeft()) data.freq -= 500000;
        data.freq = constrain(data.freq,0,12000000);
      break;
    }
  }
 data.waveform = constrain(data.waveform,0,2);
}

bool Sravn(){
  if ((data.freq != lastdata.freq) || (data.waveform != lastdata.waveform) || (data.mode != lastdata.mode) || (data.pos != lastdata.pos)) return 1;
  else return 0;
}

void eqv(){
  lastdata.freq = data.freq;
  lastdata.waveform = data.waveform;
  lastdata.pos = data.pos;
  lastdata.mode = data.mode;
}
