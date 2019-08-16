
#include <Arduino.h>
#include "config.h"
#include "sd_driver.h"
#include "rfid_driver.h"
#include "ws_led.h"
#include "display.h"

void setup() {
  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD);
  #endif

  setup_sd();
  setup_rfid();
  setup_leds();
  setup_display();
}

void loop() {
  loop_rfid();
}
