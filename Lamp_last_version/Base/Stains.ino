#define Sat 255
#define Bri (0)

CRGBPalette16 currentPalette(PartyColors_p);
void N(){
   for (byte y = 0; y < LED_ROWS; y++) {
        for (byte x = 0; x < LED_COLS; x++) {
          uint8_t pixelHue8 = inoise8 (x*scale_stains,y*scale_stains,millis()/16);
 leds[XY(x, y)] = ColorFromPalette(currentPalette, pixelHue8);}
   }blur2d(leds,LED_COLS, LED_ROWS, 32 );}

bool loadingFlag = true;

void draw_Stains() {
   if (loadingFlag)
  {loadingFlag = false;
  }fill_solid( currentPalette, 16, CHSV(hue_stains,Sat,230));
    currentPalette[9] = CHSV(hue_stains,Sat-60,255);
    currentPalette[8] = CHSV(hue_stains,255-Sat,210);
    currentPalette[7] = CHSV(hue_stains,255-Sat,210);
    currentPalette[6] = CHSV(hue_stains,Sat-60,255);
  N();
  delay(16);}
