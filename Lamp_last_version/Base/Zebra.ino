struct ModeType
{
  uint8_t Brightness = 255U; // not used here
  uint8_t Speed = speed_zebra;         // 1-255
  uint8_t Scale = scale_zebra;        // 1-100 is scale
};

#define WIDTH 16
#define HEIGHT 16

bool loadingFlag_z = true;
uint8_t selectedSettings = 1;
ModeType modes[1];
uint8_t currentMode = 0;

// The 16 bit version of our coordinates
static uint16_t x;
static uint16_t y;
static uint16_t z;

// This is the array that we keep our computed noise values in
#define MAX_DIMENSION (max(WIDTH, HEIGHT))
#if (WIDTH > HEIGHT)
uint8_t noise[WIDTH][WIDTH];
#else
uint8_t noise[HEIGHT][HEIGHT];
#endif

CRGBPalette16 currentPalette1(PartyColors_p);

uint8_t colorLoop = 1;
uint8_t ihue = 0;

// функция отрисовки точки по координатам X Y
void drawPixelXY(int8_t x, int8_t y, CRGB color)
{
  if (x < 0 || x > (WIDTH - 1) || y < 0 || y > (HEIGHT - 1)) return;
  uint32_t thisPixel = XY((uint8_t)x, (uint8_t)y);// * SEGMENTS;
  //for (uint8_t i = 0; i < SEGMENTS; i++)
  //{
    leds[thisPixel] = color;
  //}
}

// ************* СЛУЖЕБНЫЕ *************
void fillNoiseLED()
{
  uint8_t dataSmoothing = 0;
  if (speed_zebra < 50)
  {
    dataSmoothing = 200 - (speed_zebra * 4);
  }
  for (uint8_t i = 0; i < MAX_DIMENSION; i++)
  {
    int32_t ioffset = scale_zebra * i;
    for (uint8_t j = 0; j < MAX_DIMENSION; j++)
    {
      int32_t joffset = scale_zebra * j;

      uint8_t data = inoise8(x + ioffset, y + joffset, z);

      data = qsub8(data, 16);
      data = qadd8(data, scale8(data, 39));

      if (dataSmoothing)
      {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }

      noise[i][j] = data;
    }
  }
  z += speed_zebra;

  // apply slow drift to X and Y, just for visual variation.
  x += speed_zebra / 8;
  y -= speed_zebra / 16;

  for (uint8_t i = 0; i < WIDTH; i++)
  {
    for (uint8_t j = 0; j < HEIGHT; j++)
    {
      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];
      // if this palette is a 'loop', add a slowly-changing base value
      if ( colorLoop)
      {
        index += ihue;
      }
      // brighten up, as the color palette itself often contains the
      // light/dark dynamic range desired
      if ( bri > 127 )
      {
        bri = 255;
      }
      else
      {
        bri = dim8_raw( bri * 2);
      }
      CRGB color = ColorFromPalette( currentPalette1, index, bri);      
      drawPixelXY(i, j, color);                             //leds[XY(i, j)] = color;
    }
  }
  ihue += 1;
}

void fillnoise8()
{
  for (uint8_t i = 0; i < MAX_DIMENSION; i++)
  {
    int32_t ioffset = scale_zebra * i;
    for (uint8_t j = 0; j < MAX_DIMENSION; j++)
    {
      int32_t joffset = scale_zebra * j;
      noise[i][j] = inoise8(x + ioffset, y + joffset, z);
    }
  }
  z += speed_zebra;
}

//void zebraNoiseRoutine()
void draw_Zebra()
{
  if (loadingFlag_z)
  {
    #if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)
      if (selectedSettings){
        setModeSettings(12U+random8(16U), 1U+random8(9U));
      }
    #endif //#if defined(USE_RANDOM_SETS_IN_APP) || defined(RANDOM_SETTINGS_IN_CYCLE_MODE)

    loadingFlag_z = false;
    // 'black out' all 16 palette entries...
    fill_solid(currentPalette1, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette1[0] = CRGB::White;
    currentPalette1[4] = CRGB::White;
    currentPalette1[8] = CRGB::White;
    currentPalette1[12] = CRGB::White;
    scale_zebra = modes[currentMode].Scale;
    speed_zebra = modes[currentMode].Speed;
    colorLoop = 1;
  }
  fillNoiseLED();
}
