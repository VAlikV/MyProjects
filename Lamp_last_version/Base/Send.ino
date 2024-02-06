void randomdot() {
  byte a = LED_COLS / 2;
  if (!random8(4)) leds[XY(a, LED_ROWS - 1)].setHue(random8(hue_send, hue_send + 45)); // 0 or 1     
}

void updatesand() {
  int index, indexXadd1Y, indexXsub1Y, indexXYadd1;
  for (int y = 0; y < LED_ROWS - 1; y++) {
    for (int x = 1; x < LED_COLS - 1; x++) {
      index = XY(x, y); indexXadd1Y = XY(x + 1, y); indexXsub1Y = XY(x - 1, y); indexXYadd1 = XY(x, y + 1);
      if (!leds[index] && !leds[indexXYadd1]) continue;
      if (!leds[index] && leds[indexXYadd1]) {leds[index] = leds[indexXYadd1]; leds[indexXYadd1] = 0;} 
        else if (leds[index] && leds[indexXYadd1] && !leds[indexXsub1Y] && !leds[indexXadd1Y]) 
         if (random8(2)) {leds[indexXsub1Y] = leds[indexXYadd1]; leds[indexXYadd1] = 0;} else {leds[indexXadd1Y] = leds[indexXYadd1]; leds[indexXYadd1] = 0;} 
          else if (leds[index] && leds[indexXYadd1] && !leds[indexXsub1Y] && leds[indexXadd1Y]) {leds[indexXsub1Y] = leds[indexXYadd1]; leds[indexXYadd1] = 0;} 
           else if (leds[index] && leds[indexXYadd1] && leds[indexXsub1Y] && !leds[indexXadd1Y]) {leds[indexXadd1Y] = leds[indexXYadd1]; leds[indexXYadd1] = 0;}
    }
  }
}

void randomdel() {
  for (int i = 0; i < N_LEDS; i++) {
    if (!random8(3)) leds[i] = 0;
  }
}

void falldown() {
  for (int y = 0; y < LED_ROWS - 1; y++) {
    for (int x = 0; x < LED_COLS; x++) {
      if (!leds[XY(x, y)] && leds[XY(x, y + 1)]) {leds[XY(x, y)] = leds[XY(x, y + 1)]; leds[XY(x, y + 1)] = 0;}
    }
  }
}

void countSand() {
  uint16_t totalSand = 0;
  for (uint16_t i = 0; i < N_LEDS; i++) {
    if (leds[i]) {
      totalSand++;
      if (totalSand >= N_LEDS / 3 + random8(30)) {randomdel(); falldown(); falldown(); falldown(); break;}  //N_LEDS/3 this how many sands on screen? maybe time to delete some? 
    }
  }
}

void draw_Send() {
  EVERY_N_MILLISECONDS(200) {updatesand(); randomdot();}  // 80 is speed of effect
  countSand();
}
