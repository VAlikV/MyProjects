byte out[8] = {2, 3, 4, 5, 6, 7, 8, 9}; 
byte in[8] = {14, 15, 16, 17, 18, 19, 20, 21};
float voltag;
unsigned long t = 0;
int i = 0;

void setup() {        //---------------------------------------------------------------- SETUP

  for (i = 0; i < 8; ++i){
    pinMode(out[i], OUTPUT);
  }

  for (i = 0; i < 8; ++i){
    pinMode(in[i], INPUT);
  }
  
  Serial.begin(9600);
  t = millis(); 
}

void loop() {        //---------------------------------------------------------------- LOOP
  if (millis() - t > 30){

    Serial.print("&");
    for (i = 0; i < 8; ++i){
      voltag = analogRead(in[i]);
      if (voltag>=2.7) {
        digitalWrite(out[i], HIGH);
      } else {
        digitalWrite(out[i], LOW);
      }
      Serial.print(voltag); Serial.print("/");
    } 
    Serial.println("");
    t = millis();
  }
}
