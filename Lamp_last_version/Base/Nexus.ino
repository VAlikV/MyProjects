#define WIDTH LED_COLS
#define HEIGHT LED_ROWS

#define NEXUS (WIDTH)
#define BACKGROUND 0

double fmap(const double x, const double in_min, const double in_max, const double out_min, const double out_max){
  return (out_max - out_min) * (x - in_min) / (in_max - in_min) + out_min;
}


void drawPixelXYF_X(float x, uint16_t y, const CRGB &color)
{
  if (x<0 || y<0 || x>((float)WIDTH) || y>((float)HEIGHT)) return;

  // extract the fractional parts and derive their inverses
  uint8_t xx = (x - (int)x) * 255, ix = 255 - xx;
  // calculate the intensities for each affected pixel
  uint8_t wu[2] = {ix, xx};
  // multiply the intensities by the colour, and saturating-add them to the pixels
  for (int8_t i = 1; i >= 0; i--) {
      int16_t xn = x + (i & 1);
      CRGB clr = leds[XY(xn, y)];
      if(xn>0 && xn<(int)WIDTH-1){
        clr.r = qadd8(clr.r, (color.r * wu[i]) >> 8);
        clr.g = qadd8(clr.g, (color.g * wu[i]) >> 8);
        clr.b = qadd8(clr.b, (color.b * wu[i]) >> 8);
      } else if(xn==0 || xn==(int)WIDTH-1) {
        clr.r = qadd8(clr.r, (color.r * 85) >> 8);
        clr.g = qadd8(clr.g, (color.g * 85) >> 8);
        clr.b = qadd8(clr.b, (color.b * 85) >> 8);
      }
    leds[XY(xn, y)]= clr;
  }
}

void drawPixelXYF_Y(uint16_t x, float y, const CRGB &color)
{
  if (x<0 || y<0 || x>((float)WIDTH) || y>((float)HEIGHT)) return;

  // extract the fractional parts and derive their inverses
  uint8_t yy = (y - (int)y) * 255, iy = 255 - yy;
  // calculate the intensities for each affected pixel
  uint8_t wu[2] = {iy, yy};
  // multiply the intensities by the colour, and saturating-add them to the pixels
  for (int8_t i = 1; i >= 0; i--) {
      int16_t yn = y + (i & 1);
      CRGB clr = leds[XY(x, yn)];
      if(yn>0 && yn<(int)HEIGHT-1){
        clr.r = qadd8(clr.r, (color.r * wu[i]) >> 8);
        clr.g = qadd8(clr.g, (color.g * wu[i]) >> 8);
        clr.b = qadd8(clr.b, (color.b * wu[i]) >> 8);
      } else if(yn==0 || yn==(int)HEIGHT-1) {
        clr.r = qadd8(clr.r, (color.r * 85) >> 8);
        clr.g = qadd8(clr.g, (color.g * 85) >> 8);
        clr.b = qadd8(clr.b, (color.b * 85) >> 8);
      }
    leds[XY(x, yn)] = clr;
  }
}

class EffectNexus {
  private:
    float dotPosX[NEXUS];
    float dotPosY[NEXUS];
    int8_t dotDirect[NEXUS];       // направление точки 
    CRGB dotColor[NEXUS];          // цвет точки
    float dotAccel[NEXUS];         // персональное ускорение каждой точки
    bool white = false;
    byte type = 1;
    bool randColor = false;
    float windProgress;
    

    void reload();
    void resetDot(uint8_t idx);

  public:
    bool run();
    void load();
};


//------------ Эффект "Nexus"
// (с) kostyamat 4.12.2020
void EffectNexus::reload() {
  for (byte i = 0; i < NEXUS; i++) {
    dotDirect[i] = random(0, 4);                     // задаем направление
    dotPosX[i] = random(0, WIDTH);                   // Разбрасываем частицы по ширине
    dotPosY[i] = random(0, HEIGHT);                  // и по высоте
    dotColor[i] = ColorFromPalette(RainbowColors_p, random8(0, 9) * 31, 255); // цвет капли
    dotAccel[i] = (float)random(5, 11) / 70;        // делаем частицам немного разное ускорение 
  }
}


void EffectNexus::load() {
  randomSeed(millis());
  reload();
}

bool EffectNexus::run() {
  float speedfactor = fmap(speed_nexus, 1, 255, 0.1, .33);

  fadeToBlackBy(leds, N_LEDS, map(speed_nexus, 1, 255, 11, 33));

  for (byte i = 0; i < map(scale_nexus, 1, 255, 4, NEXUS); i++) {
    switch (dotDirect[i])
    {
    case 0:   // вверх
      dotPosY[i] += (speedfactor + dotAccel[i]);
      break;
    case 1:   //  вниз 
      dotPosY[i] -= (speedfactor + dotAccel[i]);
      break;
    case 2:   // вправо
      dotPosX[i] += (speedfactor + dotAccel[i]);
      break;
    case 3:   // влево
      dotPosX[i] -= (speedfactor + dotAccel[i]);
      break;
    default:
      break;
    } 

    // Обеспечиваем бесшовность по Y. И переносим каплю в начало трека
    if (dotPosY[i] < 0) {
      dotPosY[i] = (float)HEIGHT - 1.;    
      resetDot(i);
    }

    if (dotPosY[i] > (HEIGHT - 1)) {
      dotPosY[i] = 0;
      resetDot(i);
    }

    // Обеспечиваем бесшовность по X.
    if (dotPosX[i] < 0) {
      dotPosX[i] = (WIDTH - 1);
      resetDot(i);
    }
    if (dotPosX[i] > (WIDTH - 1)) {
      dotPosX[i] = 0;
      resetDot(i);
    }

  switch (dotDirect[i])
  {
  case 0:   // вверх
  case 1:   //  вниз 
    drawPixelXYF_Y(dotPosX[i], dotPosY[i], dotColor[i]);
    break;
  case 2:   // вправо
  case 3:   // влево
    drawPixelXYF_X(dotPosX[i], dotPosY[i], dotColor[i]);
    break;
  default:
    break;
  } 


  }

  //fpsmeter();
  return true;
}

void EffectNexus::resetDot(uint8_t idx) {
  randomSeed(micros());
  dotDirect[idx] = random8(0, 4);                     // задаем направление
  dotColor[idx] = ColorFromPalette(RainbowColors_p, random(0, 9) * 31, 255);              // цвет 
  dotAccel[idx] = (float)random(5, 10) / 70;     // делаем частицам немного разное ускорение 
  switch (dotDirect[idx])
  {
  case 0:   // вверх
    dotPosX[idx] = random8(0, WIDTH); // Разбрасываем капли по ширине
    dotPosY[idx] = 0;  // и по высоте
    break;
  case 1:   //  вниз 
    dotPosX[idx] = random8(0, WIDTH); // Разбрасываем капли по ширине
    dotPosY[idx] = HEIGHT-1;  // и по высоте
    break;
  case 2:   // вправо
    dotPosX[idx] = 0; // Разбрасываем капли по ширине
    dotPosY[idx] = random8(0, HEIGHT);  // и по высоте
    break;
  case 3:   // влево
    dotPosX[idx] = WIDTH-1; // Разбрасываем капли по ширине
    dotPosY[idx] = random8(0, HEIGHT);  // и по высоте
    break;
  default:
    break;
  } 
}


EffectNexus eff;

void draw_Nexus() {
  static bool loadingFlag = true;
  if (loadingFlag) eff.load(), loadingFlag = false;
  if (BACKGROUND)
    for (uint16_t i =0; i< N_LEDS; i++) leds[i] += CRGB(0, 2, 6);
  eff.run();
  delay(15); // ~= 60FPS
}
