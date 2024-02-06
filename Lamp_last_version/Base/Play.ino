void draw_Play() {
  // The EVERY_N_MILLISECONDS block runs its code every N milliseconds
  EVERY_N_MILLISECONDS(speed_play) {
    hue_play++;
  }

  for (int index = 0; index < N_LEDS; index++) {
    leds[index] = CHSV(hue_play, 255, 255);
  }
}
