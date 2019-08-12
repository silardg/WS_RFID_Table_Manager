#define DEBUG                               // comment this out if you don't want debug on Serial
#define SERIAL_BAUD 9600                    // baud for serial

/* LED DEFINES */
const int NUM_LEDS = 18;                    // number of leds
const int DATA_PIN = 7;                     // pin for leds

/* SD DEFINES */
const int PIN_SD_CS = 9;                    // CS pin for SD
const String SD_CSV_FILE = "GUESTS.CSV";    // file name (in sd card guests.csv)

/* RFID DEFINES */
const int PIN_CS_RFID = 53;                 // RFID CS pin
const int PIN_RST_RFID = 8;                 // RFID RST pin

/* PROJECT DEFINES */
const int num_per_table = 5;                // number of leds per table
