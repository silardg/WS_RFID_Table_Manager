#include "ws_led.h"
#include "config.h"

CRGB leds[NUM_LEDS];      // the leds object

/**
  * Function:     void led_flash_red()
  * Description:  flash the led as not passed
***/
void led_flash_red() {

    for(int i=0; i<NUM_LEDS; i++) {
      leds[i].r = 0;
      leds[i].g = 255;
      leds[i].b = 0;
    }
    FastLED.show();

    delay(300);
    for(int i=0; i<NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(300);

} // end of led_flash_red()

/**
  * Function:     static void test_leds(void)
  * Description:  test out the leds
***/
static void test_leds(void) {
  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
     leds[whiteLed].r = random(50, 180);
     leds[whiteLed].g = random(50, 180);
     leds[whiteLed].b = random(50, 180);

     FastLED.show();
     delay(100);

     leds[whiteLed] = CRGB::Black;
  }

  for(int i=0; i<10; i++) {
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
       leds[whiteLed].r = random(50, 180);
       leds[whiteLed].g = random(50, 180);
       leds[whiteLed].b = random(50, 180);

       FastLED.show();

       delay(10);
    }
  }

  for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
    leds[whiteLed] = CRGB::Black;


    FastLED.show();

  }
} // end of test_leds()

/**
  * Function:     static void blink_led(int _led)
  * Description:  blink leds
  * Parameters:   int _led - the number led to blink + num_per_table
***/
static void blink_led(int _led) {
  for(int i=0; i<5; i++) {
    for(int i=0; i<num_per_table; i++) {
      leds[_led+i].r = random(50, 180);
      leds[_led+i].g = random(50, 180);
      leds[_led+i].b = random(50, 180);
    }
    FastLED.show();


    delay(300);
    for(int i=0; i<num_per_table; i++) {
      leds[_led+i] = CRGB::Black;
    }
    FastLED.show();
    delay(300);
  }
} // end of void blink_led(...)

/**
  * Function:     void up_to_table(int num)
  * Description:  fill leds up to certain led
  * Parameters:   int num - the led to fill up to
***/
void up_to_table(int num) {

  #ifdef DEBUG
    Serial.println("LED - Blinking...");
  #endif

    for(int _led = 0; _led < num+num_per_table; _led = _led + 1) {
       leds[_led].r = random(50, 180);
       leds[_led].g = random(50, 180);
       leds[_led].b = random(50, 180);

       FastLED.show();

       delay(70);
    }

    for(int _led = 0; _led < NUM_LEDS; _led = _led + 1) {
      leds[_led] = CRGB::Black;
      FastLED.show();
    }
    delay(500);
    blink_led(num);

} // void up_to_table(...)

/**
  * Function:     void setup_leds()
  * Description:  setup the leds
***/
void setup_leds() {

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  #ifdef DEBUG
    Serial.println("LEDS - Inited... testing...");
  #endif

  test_leds();

} // end of setup_leds()
