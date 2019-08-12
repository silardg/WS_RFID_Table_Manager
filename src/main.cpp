
#include <Arduino.h>
#include "config.h"
#include "sd_driver.h"
#include "rfid_driver.h"
#include "ws_led.h"

void setup() {
  #ifdef DEBUG
    Serial.begin(SERIAL_BAUD);
  #endif

  setup_sd();
  setup_rfid();
  setup_leds();
}

void loop() {
  loop_rfid();
}
