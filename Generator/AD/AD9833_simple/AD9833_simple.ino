/*
   Пример простой генерации сигнала на AD9833
*/

#define PIN_CS 4
#include <AD9833.h>

AD9833 myGen (PIN_CS);

void setup() {
  myGen.begin();                                  // Инициализируем генератор
  myGen.generate(FREQ0, 10000, WAVEFORM_SINE);  // Генерируем меандр частотой 10кгц
}

void loop() {
  
}
