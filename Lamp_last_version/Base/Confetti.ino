typedef void (*SimplePatternList[])();


uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

  
void draw_Confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, N_LEDS, 1);
  int pos = random16(N_LEDS);
  leds[pos] += CHSV( hue_confetti + random8(64), 200, 255);
}
