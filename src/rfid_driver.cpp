#include "rfid_driver.h"
#include "sd_driver.h"
#include "ws_led.h"
#include "config.h"

MFRC522 mfrc522(PIN_CS_RFID, PIN_RST_RFID);   // Create MFRC522 instance

MFRC522::MIFARE_Key key;                      // MFRC522 key instance

/**
  * Function:     String getUID(byte *buffer, byte bufferSize)
  * Description:  returns the UID of the card
  * Parameters:   byte *buffer - the card buffer, bufferSize - the buffer size in bytes
***/
String getUID(byte *buffer, byte bufferSize) {
  String main_string = "";
  String one = "";
  for (byte i = 0; i < bufferSize; i++) {
    one = String(buffer[i] < 0x10 ? " 0" : " ");
    one = String(buffer[i], HEX);
    main_string += one;
  }
  main_string.toUpperCase();

  #ifdef DEBUG
    Serial.println(main_string);
  #endif

  return main_string;
} // end of getUID();

// Init array that will store new NUID
byte nuidPICC[4];

/**
  * Function:     void setup_rfid()
  * Description:  setup the RFID module
***/
void setup_rfid() {
  mfrc522.PCD_Init();		               // Init MFRC522
  delay(4);				                     // Optional delay. Some board do need more time after init to be ready, see Readme
  mfrc522.PCD_DumpVersionToSerial();	 // Show details of PCD - MFRC522 Card Reader details

  // write FF to key
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  #ifdef DEBUG
    Serial.println("RFID - Inited");
  #endif

} // end of setup_rfid()

/**
  * Function:     void loop_rfid()
  * Description:  main processing loop
***/
void loop_rfid() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  // get the type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = mfrc522.uid.uidByte[i];
  }

  // get the table num through SD function
  int guest_table_num = get_table_num(getUID(mfrc522.uid.uidByte, mfrc522.uid.size));

  #ifdef DEBUG
    Serial.print("Guests table:");
    Serial.println(guest_table_num);
  #endif

  // wait a bit
  delay(500);

  if(guest_table_num == -1)  {
    led_flash_red();
  } else {
    // display the table
    up_to_table((guest_table_num-1) * num_per_table);
  }

  // Halt PICC
  mfrc522.PICC_HaltA();

  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
} // end of loop_rfid()
