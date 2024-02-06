void draw_Mono() {
  for (int index = 0; index < N_LEDS; index++) {
    leds[index] = CRGB(color_mono);
  }
}

void draw_off() {
  for (int index = 0; index < N_LEDS; index++) {
    leds[index] = CRGB(0, 0, 0);
  }
}

void draw_on() {
  for (int index = 0; index < N_LEDS; index+=3) {
    if (index%2 == 0) leds[index] = CRGB(155, 155, 155);
  }
}

void draw_reset() {
  for (int index = 0; index < N_LEDS; index+=3) {
    if (index%2 == 0) leds[index] = CRGB(155, 0, 0);
  }
}
