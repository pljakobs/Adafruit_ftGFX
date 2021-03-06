#include <Adafruit_ftGFX.h>

#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

//#define EN
#define DE

#include <i18n.h>

// This Teensy3 native optimized version requires specific pins
//
#define sclk 13  // SCLK can also use pin 14
#define mosi 11  // MOSI can also use pin 7
#define cs   10  // CS & DC can use pins 2, 6, 9, 10, 15, 20, 21, 22, 23
#define dc   9   //  but certain pairs must NOT be used: 2+10, 6+9, 20+23, 21+22
#define rst  8   // RST can use any pin
#define sdcs 4   // CS for SD card, can use any pin

#define backlight 23

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#define DISPLAYCLASS Adafruit_ST7735

// Option 1: use any pins but a little slower
//Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

// Option 2: must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, rst);

uint16_t max_width, screen_width;
uint8_t max_height;

void setup(void) {
  pinMode(backlight, OUTPUT);
  analogWriteResolution(8);
  analogWriteFrequency(backlight,100000);
  pinMode(sdcs, INPUT_PULLUP);  // keep SD CS high when not using SD card
  
  setBacklight(0);
  
  Serial.begin(250000);
 
  //tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  //tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
  tft.initR(INITR_GREENTAB); // initialize a ST7735R chip, green tab

  setBacklight(255);
  //analogWrite(backlight,1024);
  Serial.println("init");
  
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
}

void loop()
{
  tft.fillScreen(ST7735_WHITE);
  tft.setFont(OPENSANSREG_12);
  tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
  tft.setCursor(0,10);
  String mytest="Franz fährt im übel verwahrlosten Taxi quer durch Bayern";
  tft.print(UTF8toLatin1(mytest));
  delay(5000);
  tft.setTextColor(ST7735_BLUE, ST7735_BLACK);
  for( char i=0x20;i!=0x00;i++){
    if (i==0x80) i=0xa0;
    tft.setTextColor(ST7735_BLUE, ST7735_BLACK);
    tft.setCursor(0,20);
    tft.setFont(OPENSANSREG_14);
    tft.printf("0x%02x",i);
    tft.fillRect(0,35,160,45,make565color(160,160,160));
    tft.setTextColor(ST7735_RED, make565color(160,160,160));
    tft.setCursor(20,70);
    tft.setFont(OPENSANSREG_36);
    tft.printf("%c%c%c%c%c",i-2,i-1,i,i+1,i+2);
    tft.setCursor(00,120);
    tft.setFont(SEGMENT7_24);
    tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
    tft.printf("dec %02d",i);
    delay(1000);
    tft.fillScreen(ST7735_BLACK);
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}
void setTeensy3Time(time_t t){
  Teensy3Clock.set(t);
}

void setBacklight(uint8_t l ){
  analogWrite(backlight,l);
}

String UTF8toLatin1( String& in){
  String out;
  for(uint16_t i=0;i<in.length();i++){
    if (in[i]<0x7f){
      out+=in[i];
    }else if(in[i] == 0xc2){
      out+=in[++i];
    }else if(in[i] == 0xc3){
      out+=(char)(in[++i]+0x40);
    }
  }
  return out ;
}

uint16_t make565color(uint8_t r, uint8_t g, uint8_t b){
  return (r & 0xf8)<<8|(g & 0xfa)<<3|(b >> 3);
}


