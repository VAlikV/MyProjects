
void build_off() { //----------------------------------------------------------Off
  String s;
  BUILD_BEGIN(s);
  add.THEME(GP_LIGHT);
  
  // Шапка
  add.BLOCK_BEGIN();  
  add.BREAK();   
  add.TITLE("Rainbow_Lamp v3.0");
  add.BREAK();
  add.BLOCK_END();
  add.HR();

  // Вкл\выкл, яркость

  add.BLOCK_BEGIN(); add.BREAK();   
  add.LABEL("On/off: ");
  add.SWITCH("on_off", 0); add.BREAK(); 
  add.BLOCK_END();
  add.HR();

  // Wifi

  add.BLOCK_BEGIN(); add.BREAK();
  add.FORM_BEGIN("/login");
  add.TITLE("WI-FI:");
  add.TEXT("Log", "Login", _ssid); add.BREAK();
  add.PASS("Pass", "Password", _pass); add.BREAK();
  add.SUBMIT("Submit"); add.BREAK();
  add.FORM_END();
  add.BLOCK_END();
  add.HR();

  BUILD_END();
}


void build_on() { //----------------------------------------------------------------------------------------------------------------------On
  String s;
  BUILD_BEGIN(s);
  add.THEME(GP_LIGHT);
  
  // Шапка
  add.BLOCK_BEGIN();  
  add.BREAK();   
  add.TITLE("Rainbow_Lamp v3.0");
  add.BREAK();
  add.BLOCK_END();
  add.HR();

  // Вкл\выкл, яркость

  add.BLOCK_BEGIN(); add.BREAK();   
  add.LABEL("On/off: ");
  add.SWITCH("on_off", 1); add.BREAK(); add.BREAK();
  add.LABEL("Brightness: "); add.BREAK();
  add.SLIDER("BR", BRIGHTNESS, 5, 100, 1); add.BREAK(); 
  add.BLOCK_END();
  add.HR();

  // Режим

  add.BLOCK_BEGIN(); add.BREAK();   
  add.LABEL("Mode: ");
  add.SELECT("mode", "Mono,Play,Fire,Zebra,Rainbow,Stains,Rings,Nexus,Confetti,Aurora,Stars,Send", mode0); add.BREAK();
  add.BLOCK_END();
  add.HR();

  
  switch(mode0){
      case 0:  //-------------------------------------------------------------------------------------------Mono
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Color: ");
          add.COLOR("color_mono", color_mono); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR();
      break;
      case 1: //-------------------------------------------------------------------------------------------Play 
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Speed: "); add.BREAK();
          add.SLIDER("speed_play", speed_play, 10, 100, 1); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR();
      break;
      case 2: //-------------------------------------------------------------------------------------------Fire
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Color: "); add.BREAK();
          add.SELECT("color_fire", "Red,Green,Blue,Purp", flag_fire); add.BREAK(); add.BREAK();
          add.LABEL("Speed: "); add.BREAK();
          add.SLIDER("speed_fire", speed_fire, 5, 80, 1); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR();      
      break;
      case 3: //-------------------------------------------------------------------------------------------Zebra
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Scale: "); add.BREAK();
          add.SLIDER("scale_zebra", scale_zebra, 1, 100, 1); add.BREAK();
          add.LABEL("Speed: "); add.BREAK();
          add.SLIDER("speed_zebra", speed_zebra, 1, 25, 1); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR(); 
      break;
      case 4: //-------------------------------------------------------------------------------------------Rainbow
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Mode: "); add.BREAK();
          add.SELECT("mode_rainbow", "_1_,_2_,_3_,_4_", flag_rain); add.BREAK(); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR();
      break;
      case 5: //-------------------------------------------------------------------------------------------Stains
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Scale: "); add.BREAK();
          add.SLIDER("scale_stains", scale_stains, 5, 100, 1); add.BREAK();
          add.LABEL("Color: "); add.BREAK();
          add.SLIDER("color_stains", hue_stains, 0, 255, 1); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR();
      break;
      case 6:  //-------------------------------------------------------------------------------------------Rings
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("No settings"); add.BREAK();
          add.BLOCK_END();
          add.HR();
      break;
      case 7: //-------------------------------------------------------------------------------------------nexus
          add.BLOCK_BEGIN(); add.BREAK();   
          add.TITLE("Settings:"); add.BREAK();
          add.LABEL("Scale: "); add.BREAK();
          add.SLIDER("scale_nexus", scale_nexus, 50, 250, 1); add.BREAK();
          add.LABEL("Speed: "); add.BREAK();
          add.SLIDER("speed_nexus", speed_nexus, 10, 100, 1); add.BREAK();
          add.BUTTON_MINI("reset", "Reset"); add.BREAK();
          add.BLOCK_END();
          add.HR();
      break;
      case 8: //-------------------------------------------------------------------------------------------Cjnfetti
        add.BLOCK_BEGIN(); add.BREAK();   
        add.TITLE("Settings:"); add.BREAK();
        add.LABEL("Color: "); add.BREAK();
        add.SLIDER("color_confetti", hue_confetti, 0, 255, 1); add.BREAK();
        add.BUTTON_MINI("reset", "Reset"); add.BREAK();
        add.BLOCK_END();
        add.HR();
      break;
      case 9: //-------------------------------------------------------------------------------------------Aurora
        add.BLOCK_BEGIN(); add.BREAK();   
        add.TITLE("Settings:"); add.BREAK();
        add.LABEL("Speed: "); add.BREAK();
        add.SLIDER("speed_aurora", speed_aurora, 1, 255, 1); add.BREAK();
        add.BUTTON_MINI("reset", "Reset"); add.BREAK();
        add.BLOCK_END();
        add.HR();      
      break;
      case 10: //-------------------------------------------------------------------------------------------Stars
        add.BLOCK_BEGIN(); add.BREAK();   
        add.TITLE("Settings:"); add.BREAK();
        add.LABEL("No settings"); add.BREAK();
        add.BLOCK_END();
        add.HR();
      break;
      case 11: //-------------------------------------------------------------------------------------------Send
        add.BLOCK_BEGIN(); add.BREAK();   
        add.TITLE("Settings:"); add.BREAK();
        add.LABEL("Color: "); add.BREAK();
        add.SLIDER("color_send", hue_send, 0, 255, 1); add.BREAK();
        add.BUTTON_MINI("reset", "Reset"); add.BREAK();
        add.BLOCK_END();
        add.HR(); 
      break;
    }

  // Wifi

  add.BLOCK_BEGIN(); add.BREAK();
  add.FORM_BEGIN("/login");
  add.TITLE("WI-FI:");
  add.TEXT("Log", "Login", _ssid); add.BREAK();
  add.PASS("Pass", "Password", _pass); add.BREAK();
  add.SUBMIT("Submit"); add.BREAK();
  add.FORM_END();
  add.BLOCK_END();
  add.HR();

  BUILD_END();
}
