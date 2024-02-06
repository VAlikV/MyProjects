void WIFIinit() {
  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  WiFi.begin(_ssid, _pass);
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    draw_on();
    FastLED.show();
    delay(500);
    draw_off();
    FastLED.show();
    delay(500);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    // Если не удалось подключиться запускаем в режиме AP
    Serial.println("");
    Serial.println("WiFi up AP");
    draw_reset();
    FastLED.show();
    delay(500);
    draw_off();
    FastLED.show();
    StartAPMode();
  }
  else {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    IPAddress ip = WiFi.localIP();
    first = ip[2];
    second = ip[3];
  }
}

bool StartAPMode()
{
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(_ssidAP, _passAP);
  IPAddress ip = IPAddress(192, 168, 2, 2);
  first = ip[2];
  second = ip[3];
  return true;
}
