#define COUNT 4
float posX[COUNT];
float posY[COUNT];
uint8_t aimX[COUNT];
uint8_t aimY[COUNT];
float radius[COUNT];
byte huue[COUNT];;
CRGB color[COUNT];
byte starPoints[COUNT];
bool ruun[COUNT];
bool load = true;

const byte maax = max(16, 16);
const float speedFactor = N_LEDS/256; 


const float speeid = (float) N_LEDS / 256; // Speed normalization for different matrix sizes
const float addRadius = (float) N_LEDS / 4000; // Normalization of increase in radius
// of a circle for different matrix sizes 

void drawPixelXYF(float x, float y, CRGB color) {
  if (x < 0 || y < 0 || x > ((float) LED_COLS - 1) || y > ((float) LED_ROWS - 1)) return;
  uint8_t xx = (x - (int) x) * 255, yy = (y - (int) y) * 255, ix = 255 - xx, iy = 255 - yy;
  // calculate the intensities for each affected pixel
  #define WU_WEIGHT(a, b)((uint8_t)(((a) * (b) + (a) + (b)) >> 8))
  uint8_t wu[4] = {
    WU_WEIGHT(ix, iy),
    WU_WEIGHT(xx, iy),
    WU_WEIGHT(ix, yy),
    WU_WEIGHT(xx, yy)
  };
  // multiply the intensities by the colour, and saturating-add them to the pixels
  for (uint8_t i = 0; i < 4; i++) {
    int16_t xn = x + (i & 1), yn = y + ((i >> 1) & 1);
    CRGB clr = leds[XY(xn, yn)];
    clr.r = qadd8(clr.r, (color.r * wu[i]) >> 8);
    clr.g = qadd8(clr.g, (color.g * wu[i]) >> 8);
    clr.b = qadd8(clr.b, (color.b * wu[i]) >> 8);
    leds[XY(xn, yn)] = clr;
  }
}

void drawCircleF(float x0, float y0, float radius,
  const CRGB & color, float step = 0.25) {
  float a = radius, b = 0.;
  float radiusError = step - a;
  
  if (radius <= step * 2) {
    drawPixelXYF(x0, y0, color);
    return;
  }
  
  while (a >= b) {
    drawPixelXYF(a + x0, b + y0, color);
    drawPixelXYF(b + x0, a + y0, color);
    drawPixelXYF(-a + x0, b + y0, color);
    drawPixelXYF(-b + x0, a + y0, color);
    drawPixelXYF(-a + x0, -b + y0, color);
    drawPixelXYF(-b + x0, -a + y0, color);
    drawPixelXYF(a + x0, -b + y0, color);
    drawPixelXYF(b + x0, -a + y0, color);
    
    b += step;
    if (radiusError < 0.)
      radiusError += 2. * b + step;
    else {
      a -= step;
      radiusError += 2 * (b - a + step);
    }
  }
}

void drawLineF(float x1, float y1, float x2, float y2,
  const CRGB & color) {
  float deltaX = fabs(x2 - x1);
  float deltaY = fabs(y2 - y1);
  float error = deltaX - deltaY;
  
  float signX = x1 < x2 ? 0.5 : -0.5;
  float signY = y1 < y2 ? 0.5 : -0.5;
  
  while (x1 != x2 || y1 != y2) {
    if ((signX > 0. && x1 > x2 + signX) || (signX < 0. && x1 < x2 + signX))
      break;
    if ((signY > 0. && y1 > y2 + signY) || (signY < 0. && y1 < y2 + signY))
      break;
    drawPixelXYF(x1, y1, color);
    float error2 = error;
    if (error2 > -deltaY) {
      error -= deltaY;
      x1 += signX;
    }
    if (error2 < deltaX) {
      error += deltaX;
      y1 += signY;
    }
  }
}



void drawStarF(float x, float y, float biggy, float little, int16_t points, float dangle, CRGB color) {
  float radius2 = 255.0 / points;
  for (int i = 0; i < points; i++) {
    drawLineF(x + ((little * (sin8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), y + ((little * (cos8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), x + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), y + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), color);
    drawLineF(x + ((little * (sin8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), y + ((little * (cos8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), x + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), y + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), color);
  }
}


void aimChange(byte idx) {
  randomSeed(millis());
  aimX[idx] = random(16 / 2 - 16/8, 16 / 2 + 16/8+1);
  aimY[idx] = random(16 / 2 - 16/8, 16 / 2 + 16/8+1);
  radius[idx] = 1;
  huue[idx] = random8();
  color[idx] = ColorFromPalette(RainbowColors_p, huue[idx], 180); //CHSV(hue, 255, 255);
  starPoints[idx] = random(3, 8);
  ruun[idx] = false;
}

byte count = 0;

void draw_Stars() {
  fadeToBlackBy(leds, N_LEDS, 50);
  
  if (load) {
    for (byte i = 0; i < COUNT; i++) {
      aimChange(i);
    }
    ruun[0] = true;
    load = false;
  }
  for (byte i = 0; i < COUNT; i++) {
    if (radius[i] > maax / COUNT) {
      ruun[i + 1 < COUNT ? i + 1 : 0] = true;
    }
    
    static float angle[COUNT];
    
    if (ruun[i]) {
      radius[i] += addRadius * speedFactor;
      angle[i] += radius[i];
      switch (huue[i] % 3) {
        case 0:
          drawCircleF(aimX[i], aimY[i], radius[i], color[i]); // рисуем круг
          break;
        case 1:
          drawStarF(aimX[i], aimY[i], 1.3 * radius[i], radius[i], 4, angle[i], color[i]); // рисуем квадрат
          break;
        case 2:
          drawStarF(aimX[i], aimY[i], 2 * radius[i], radius[i], starPoints[i], angle[i], color[i]); // рисуем звезду
          break;
      }
    }
    if (radius[i] > maax) aimChange(i);
  }
}
