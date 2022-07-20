#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define OUT           PCINT4 // PB4
#define pushbtn       PCINT3 // PB3
#define leftbtn       PCINT2 // PB2
#define rightbtn      PCINT1 // PB1
#define selbtn        PCINT0 // PB0

// Define order of LEDs in string, starting with 0
#define l             1
#define u             0
#define d             2
#define r             3
#define se            4
#define st            5
#define b             6
#define a             7

#define NUMPIXELS 8 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, OUT, NEO_GRB + NEO_KHZ800);

volatile uint8_t brightness;
volatile uint8_t color_type;
const uint8_t    COLOR_QTY  = 9;
const uint8_t    DEBOUNCE_DELAY = 50;
const uint8_t    BRIGHTNESS_INC = 5;
const uint8_t    MIN_BRIGHTNESS = 5;
const uint8_t    MAX_BRIGHTNESS = 50;

volatile uint8_t brightness_change_flag = 0;

// cycles through different colors:    red  org  ylw  grn  cyan blue purp wht  off
volatile uint8_t red[COLOR_QTY]   =  { 255, 255, 255, 0,   0,   0,   255, 255, 0};
volatile uint8_t green[COLOR_QTY] =  { 0,   100, 200, 255, 255, 0,   0,   255, 0};
volatile uint8_t blue[COLOR_QTY]  =  { 0,   0,   0,   0,   255, 255, 255, 255, 0};

void setup() {

  pixels.begin();

  EEPROM.get(0, brightness);
  EEPROM.get(1, color_type);

  // Check if EPROM data was corrupted, set brightness to max or min values
  if (brightness>MAX_BRIGHTNESS){
    brightness=MAX_BRIGHTNESS;
  }
  if (brightness<MIN_BRIGHTNESS){
    brightness=MIN_BRIGHTNESS;
  }
  
  pixels.setBrightness(brightness);

  // Inputs *MUST NOT* use ATTINY's pull-ups. These will rely on the GBC CPU's internal pull-ups to 3.3V. The ATTINY is powered by 5V!!
  pinMode(pushbtn, INPUT);
  pinMode(leftbtn, INPUT);
  pinMode(rightbtn, INPUT);
  pinMode(selbtn, INPUT);

  // Skip intro if nav switch is pushed in
  if (digitalRead(pushbtn)==HIGH){

      pixels.clear();
      pixels.show();
      delay(1100);

      int y=6;
      int k=0;

      uint8_t introarray[24] = {8,8,8,8,8,8,8,2,2,0,0,6,6,3,3,5,5,5,5,5,5,5,5,5};

      // Loop through values in introarray. Delays were timed experimentally.
      for(int j=0; j<16; j++){
        for(int i=0; i<NUMPIXELS; i++){
          if(i==l){
            k=introarray[j+6];
          }
          if(i==u){
            k=introarray[j+5];
          }
          if(i==d){
            k=introarray[j+5];
          }
          if(i==r){
            k=introarray[j+4];
          }
          if(i==se){
            k=introarray[j+3];
          }
          if(i==st){
            k=introarray[j+2];
          }
          if(i==b){
            k=introarray[j+1];
          }
          if(i==a){
            k=introarray[j];
          }
        pixels.setPixelColor(i, pixels.Color(red[k],green[k],blue[k]));
        pixels.show();
        delay(y);
        }
      }
      delay(2000);
  }else{
    while(1){};
  }
//  while(!digitalRead(pushbtn)){
//    delay(10);
//  }
}

void loop() {
  // Update LED outputs
  outputLED(color_type);

  // If nav switch is pressed
  if(digitalRead(pushbtn)==LOW){
    // Pause the program to debounce the switch, check to make sure it's still pressed
    delay(DEBOUNCE_DELAY);
    if(digitalRead(pushbtn)==LOW){

      // I'm sorry, I forgot to comment this, and now I'm reading it months later
      while(!digitalRead(pushbtn) && !digitalRead(pushbtn)){
        if(digitalRead(rightbtn)==LOW){
        delay(DEBOUNCE_DELAY);
          if(digitalRead(rightbtn)==LOW){
            while(!digitalRead(rightbtn)){
              delay(DEBOUNCE_DELAY);
            }
            if(brightness+BRIGHTNESS_INC>MAX_BRIGHTNESS){
              brightness=MAX_BRIGHTNESS;
            }else{
              brightness=brightness+BRIGHTNESS_INC;
            }
            brightness_change_flag = 1;
            pixels.setBrightness(brightness);
            outputLED(color_type);
          }
        }
        
        if(digitalRead(leftbtn)==LOW){
          delay(DEBOUNCE_DELAY);
          if(digitalRead(leftbtn)==LOW){
            while(!digitalRead(leftbtn) && !digitalRead(pushbtn)){
              delay(DEBOUNCE_DELAY);
            }
            if(brightness-BRIGHTNESS_INC<MIN_BRIGHTNESS){
              brightness=MIN_BRIGHTNESS;
            }else{
              brightness=brightness-BRIGHTNESS_INC;
            }
            brightness_change_flag = 1;
            pixels.setBrightness(brightness);
            outputLED(color_type);
          }
        }
        delay(DEBOUNCE_DELAY);
      }
      
      if(brightness_change_flag==0){
        if(color_type==COLOR_QTY-1){
          color_type=0;
        }else{
          color_type = color_type+1;
        }
      }
      // Save brightness and color setting to EPROM
      EEPROM.put(0,brightness);
      EEPROM.put(1,color_type);
      brightness_change_flag = 0;
      }
    }
  }

void outputLED(uint8_t x){
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(red[x],green[x],blue[x]));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }  
}
