/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 64x48 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SCL GPIO5
// SDA GPIO4
#define OLED_RESET -1  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);


void InitDisplay() {
/*
  Wire.begin(OLED_SDA,OLED_SCL);
  Wire.setClock(400000L);
  display.begin(SSD1306_SWITCHCAPVCC, I2C_ADDRESS);

  display.display();
  delay(500);
*/  
  display.begin();
//  display.firstPage();
//  display.setPowerSave(0);
//  display.setContrast(30); //Contrast setup will help to preserve OLED lifetime. In case OLED need to be brighter increase number up to 255
// display.dim();
}
///////////////
IRAM_ATTR void ShowTitle()
{
  display.clearDisplay();
//  display.setTextColor(SSD1306_WHITE); // Draw white text
//  display.setTextSize(1);    // Normal 1:1 pixel scale
  //display.setTextColor(WHITE, BLACK);       // Draw white text
//  display.setFont(u8x8_font_chroma48medium8_r);
//  display.setFont(u8x8_font_5x8_r);
//  display.setFont(u8x8_font_inb33_3x6_n);
  
  display.setCursor(0, 0);
  display.drawStr(0,0,"TPMS Monitor");
  display.drawStr(0,14," JSM Solutions");
  display.drawStr(0,28,VERSION);
  delay(1000);
  //display.clearDisplay();
  //display.drawString(0,0,"1.00");
  //display.drawString(4,0,"2.00");
  
  //display.setFont(u8x8_font_8x13B_1x2_r);
  //display.setFont(u8x8_font_7x14_1x2_r);
//  display.setFont(u8x8_font_inr33_3x6_r);
  //display.drawString(0,18,"3.00");
  //display.drawString(4,18,"4.00");

    
//  display.println(")");  
  delay(500);
  display.display();
}
/////////////
IRAM_ATTR char DisplayTimeoutBar(unsigned long TimeSinceLastUpdate)
{
  int HowCloseToTimeout;
  HowCloseToTimeout = (int)(TimeSinceLastUpdate/(TPMS_TIMEOUT/5));

  switch(HowCloseToTimeout)
  {
    case 0: 
       //return(FONTBAR_7);
       return('5');
       break;
    case 1: 
       //return(FONTBAR_5);
       return('4');
       break;
    case 2: 
       //return(FONTBAR_3);
       return('3');
       break;
    case 3: 
       //return(FONTBAR_2);
       return('2');
       break;
    case 4: 
       //return(FONTBAR_1);
       return('1');
       break;
    default: 
       //return(FONTBAR_0);
       return('0');
       break;
                  
  }
}

#define LOGO_HEIGHT   8
#define LOGO_WIDTH    8
static const unsigned char PROGMEM logo_winter[] =
{ 0x09, 0x20, 0x05, 0x40, 0x23, 0x88, 0x11, 0x10, 0x8b, 0xa2, 0x45, 0x44, 0x2b, 0xa8, 0xfe,  0xfe,
  0x2b, 0xa8, 0x45, 0x44, 0x8b, 0xa2, 0x11, 0x10, 0x23, 0x88, 0x05, 0x40, 0x09, 0x20, 0x00, 0x00
 };

static const unsigned char PROGMEM logo_summer[] =
{ 0x01, 0x00, 0x01, 0x00, 0x20, 0x08, 0x13, 0xd0, 0x0f, 0xe0, 0x0f, 0xf0, 0x1f, 0xf0, 0xdf, 0xf6, 
  0x1f, 0xf0, 0x0f, 0xf0, 0x0f, 0xe0, 0x17, 0xd0, 0x20, 0x08, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00
};
///////////////
IRAM_ATTR void ShowClock(char timeHourMinute[6]) {
  display.clearDisplay();
//    display.setFont(u8x8_font_courB18_2x3_f);
//  display.setFont(u8x8_font_px437wyse700a_2x2_r);
  display.drawStr(0,0,timeHourMinute);
//  display.drawString(2,15,":");
//  display.drawCircle(10,18+30,9);
  display.display();
}
//////////
IRAM_ATTR void UpdateDisplay() {
  int i, x = 0, y = 0;
  char s[12];
  display.clearDisplay();

  for (i = 0; i < 4; i++) {
    switch (i) {
      case 0:
        x = 0; y = 0; break;
      case 1:
        x = 4; y = 0; break;
      case 2:
        x = 0; y = 3; break;
      case 3:
        x = 4; y = 3; break;
    }

    display.setCursor(x, y);

    switch(TPMS[i].Typename){
      case 'w':
      case 'W':
//        display.drawBitmap(x,y+4,logo_winter,LOGO_WIDTH,LOGO_HEIGHT, 1);
          display.print("S");
        break;
      case 's':
      case 'S':
//        display.drawBitmap(x,y+4,logo_summer,LOGO_WIDTH,LOGO_HEIGHT, 1);
          display.print("S");
    }

//    sprintf(s,"%c ",TPMS[i].Typename);
//    display.print(s);

//    display.drawLine(0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SSD1306_WHITE);   
//    display.drawVLine(SCREEN_WIDTH/2, 32, 12);
    display.setCursor(x+0, y);
//    display.setTextSize(2);
//    display.setFont(u8x8_font_7x14_1x2_r);
    sprintf(s,"%3.2f ",TPMS[i].TPMS_Pressure);
//    s = strtok(s,":");
    display.print(s);
    Serial.print(s);
    
//    display.setCursor(x+0, y);
//    display.setFont(u8x8_font_8x13_1x2_r);
//    sprintf(s,"%0.0f ",TPMS[i].TPMS_Pressure);  
//    display.print(s);
//    Serial.print(s);
    
    display.setCursor(x+1, y+2);
//    display.setFont(u8x8_font_5x8_f);
    sprintf(s,"%2.0f\xF8""C", TPMS[i].TPMS_Temperature);
    display.print(s);
//...    display.print(DisplayTimeoutBar(millis() - TPMS[i].lastupdated));
//    display.setCursor(x, y+24);
//    sprintf(s,"  %08X", TPMS[i].TPMS_ID);
//    display.print(s);
    //display vertical bar showing how long since last update 7 bars = recent 1 bar = nearing timeout (at timeout it will be removed from display altogether)
  }
  Serial.println();
//  display.dim(true);
  display.display();
}
