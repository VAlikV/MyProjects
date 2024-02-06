
float s_r = speed_rain/10.0;
byte ind; 
void draw_Rainbow() {
  static float t=0.0;
 
for (int i = 0; i < 16; i++) { 
for (int j = 0; j < 16; j++) {
  switch (flag_rain){
    case 0: ind = sin8(i*8+sin8(i*2+6*t))/2+sin8(j*8+sin8(j*2+t*7)/2); break;
    case 1: ind = sin8(i*16*sin(PI*j/32+t)+j*8*cos(2*PI*i/32+t*2))>>1; break;
    case 2: ind = sin8(i*j)/2-sin8(i*8+t)/2+sin8(i*i+j*j+t)/2; break;
    case 3: ind = sin8((i<<4)+t)/2+sin8((j<<4)+t)/2; break;
  }
  leds [XY(i,j)] = CHSV (ind,255,255);
}
}
t+=s_r;
}
