static float fmap(const float x, const float in_min, const float in_max, const float out_min, const float out_max)
{
  return (out_max - out_min) * (x - in_min) / (in_max - in_min) + out_min;
}

static const TProgmemRGBPalette16 GreenAuroraColors_p FL_PROGMEM = {0x000000, 0x003300, 0x006600, 0x009900, 0x00cc00, 0x00ff00, 0x33ff00, 0x66ff00, 0x99ff00, 0xccff00, 0xffff00, 0xffcc00, 0xff9900, 0xff6600, 0xff3300, 0xff0000};

unsigned long timer;


float adjastHeight = map(16, 8, 32, 28, 12);
uint16_t adjScale = map(16, 8, 64, 310, 63);

void draw_Aurora()
{ 
    uint16_t _scale = map(scale_aurora, 1, 255, 30, adjScale);
    byte _speed = map(speed_aurora, 1, 255, 128, 16);
    for (byte x = 0; x < 16; x++)
    {
      for (byte y = 0; y < 16; y++)
      {
        timer++;
        leds[XY(x, y)] = ColorFromPalette(GreenAuroraColors_p, qsub8(inoise8(timer % 2 + x * _scale, y * 16 + timer % 16, timer / _speed), fabs((float)16 / 2 - (float)y) * adjastHeight));
      }
    } 
  delay(16);    
}
