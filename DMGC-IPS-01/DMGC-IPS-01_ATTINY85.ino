// ********************************************************************
// *DISCONNECT THE CPU AND Q5 KIT RIBBON CABLES BEFORE PROGRAMMING!!!!*
// ********************************************************************

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

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
const uint8_t    COLOR_QTY  = 14;
const uint8_t    RAINBOW_START_IDX = 10;
const uint8_t    DEBOUNCE_DELAY = 50;
const uint8_t    LOOP_DELAY = 10;
const uint8_t    BRIGHTNESS_INC = 5;
const uint8_t    MIN_BRIGHTNESS = 5;
const uint8_t    MAX_BRIGHTNESS = 50;

volatile uint8_t brightness_change_flag = 0;

// cycles through different colors:  red  org  ylw  grn  cyan blue purp pink wht  off rainbow rainbow_slow rainbow_med rainbow_fast
const uint8_t red[COLOR_QTY]     = { 255, 255, 255, 0,   0,   0,   255, 242, 255, 0,  0,      0,           0,          0};
const uint8_t green[COLOR_QTY]   = { 0,   100, 200, 255, 255, 0,   0,   90,  255, 0,  0,      0,           0,          0};
const uint8_t blue[COLOR_QTY]    = { 0,   0,   0,   0,   255, 255, 255, 255, 255, 0,  0,      0,           0,          0};
// Rainbow animation speed
const uint8_t rainbow[COLOR_QTY] = { 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,      37,          76,         151};

const uint8_t RAINBOW_SAT    = 255; // Rainbow saturation (S in HSV)
const uint8_t RAINBOW_VAL    = 255; // Rainbow value (V in HSV)
const uint16_t RAINBOW_START = 10240; // Chosen a bit arbitrarily
volatile uint16_t rainbow_current = RAINBOW_START;

void setup() {

  // Disable the ADC to save a slight amount of power
  ADCSRA = 0;
  power_adc_disable();

  // Set SLEEP_MODE_PWR_DOWN, the lowest power sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  pixels.begin();

  EEPROM.get(0, brightness);
  EEPROM.get(1, color_type);

  // Check if EPROM data was corrupted, set brightness to max or min values
  if (brightness>MAX_BRIGHTNESS){
    brightness=MAX_BRIGHTNESS;
    EEPROM.put(0,brightness);
  }
  if (brightness<MIN_BRIGHTNESS){
    brightness=MIN_BRIGHTNESS;
    EEPROM.put(0,brightness);
  }

  // Set color_type back to 0 if it's an invalid value
  if (color_type>COLOR_QTY-1){
    color_type=0;
    EEPROM.put(1,color_type);
  }

  pixels.setBrightness(brightness);

  // Inputs *MUST NOT* use ATTINY's pull-ups. These will rely on the GBC CPU's internal pull-ups to 3.3V. The ATTINY is powered by 5V!!
  // When developing without the CPU board plugged in, change these to INPUT_PULLUP. Change them back to INPUT before reassembly!
  pinMode(pushbtn, INPUT);
  pinMode(leftbtn, INPUT);
  pinMode(rightbtn, INPUT);
  pinMode(selbtn, INPUT);

  // Skip intro if nav switch is pushed in
  if (digitalRead(pushbtn)==HIGH){

      pixels.clear();
      pixels.show();
      delay(1100);

      const int y=6;
      int k=0;

      const uint8_t introarray[24] = {9,9,9,9,9,9,9,2,2,0,0,6,6,3,3,5,5,5,5,5,5,5,5,5};

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
    while(1){
      sleep(false); // Sleep forever!
    };
  }
//  while(!digitalRead(pushbtn)){
//    delay(10);
//  }
}

void loop() {
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
          rainbow_current=RAINBOW_START;
        }else{
          color_type = color_type+1;
        }
      }
      // Save brightness and color setting to EPROM
      EEPROM.update(0,brightness);
      EEPROM.update(1,color_type);
      brightness_change_flag = 0;
      }
    }

    // Update LED outputs
    outputLED(color_type);

    // Sleep if showing a static color or static rainbow
    if (color_type <= RAINBOW_START_IDX) {
      sleep(true);
    } else {
      // Delay just a bit so we're not refreshing the LEDs so fast
      delay(LOOP_DELAY);
    }
  }

void outputLED(uint8_t x){
  // Rainbow logic; similar to NeoPixel library's, except with first two pixels swapped
  if (x >= RAINBOW_START_IDX) {
    for (uint16_t i=0; i<NUMPIXELS; i++) { // For each pixel...
      uint16_t j = i; // Swap left and up
      if (j == u) {
        j = l;
      } else if (j == l) {
        j = u;
      }
      uint16_t hue = rainbow_current + (i * 65536) / NUMPIXELS;
      uint32_t color = pixels.ColorHSV(hue, RAINBOW_SAT, RAINBOW_VAL);
      pixels.setPixelColor(j, pixels.gamma32(color));
    }
    rainbow_current += rainbow[x];
  } else {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel..
      pixels.setPixelColor(i, pixels.Color(red[x],green[x],blue[x]));
    }
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
}

// ISR - called when push is pushed during sleep to wake up
ISR(PCINT0_vect) {
  GIMSK &= ~0b00100000;  // Turn off pin change interrupts
  sleep_disable();
}

// Sleeps to save ~25 mW
void sleep(bool can_wake) {
  sleep_enable();
  if (can_wake) { // Enable interrupts so we can wake up
    noInterrupts();
    GIMSK |= 0b00100000;  // Turn on pin change interrupts
    PCMSK |= 1 << pushbtn; // For pin 3 - pushbtn
    interrupts();
  }
  sleep_cpu();
}
