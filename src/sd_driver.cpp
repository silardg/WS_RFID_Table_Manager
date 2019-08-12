#include "sd_driver.h"
#include "config.h"

File root;
File myFile;

char current_familyname[20];        // store current familyname
char current_uid[20];               // store current uid
int current_tableid;                // store current tableid

/**
  * Function:     static char* find_data(String input)
  * Description:  parsing the csv file
  * Parameters:   String input - the current row
***/
static char* find_data(String input) {

  int input_length = input.length();        // get the input length
  char c_input[input_length + 1];           // create string
  strcpy(c_input, input.c_str());           // copy to the new string

  char * string_part;                       // this is used by strtok_r() as an index

  string_part = strtok (c_input,",");       // parsing the first part
  strcpy(current_familyname, string_part);  // copy to current

  string_part = strtok (NULL, ",");         // parsing the second part
  strcpy(current_uid, string_part);         // copy to current

  string_part = strtok (NULL, ",");         // parsing the third part
  current_tableid = atoi(string_part);      // copy to current

  return current_uid;                       // return UID

} // end of find_data(...)

/**
  * Function:     void setup_sd()
  * Description:  setup the sd card
***/
void setup_sd() {
  if (!SD.begin(PIN_SD_CS)) {
    #ifdef DEBUG
      Serial.println("SD - initialization failed!");
    #endif
    while(1);
  } else {
    #ifdef DEBUG
      Serial.println("SD - Inited");
    #endif
  }

  delay(50);

} // end of setup_sd()

/**
  * Function:     int get_table_num(String card_uid)
  * Description:  get the table number
  * Parameters:   String card_uid - the card uid we want to compare
***/
int get_table_num(String card_uid) {

  myFile = SD.open(SD_CSV_FILE);        // open file

  String input_processing = "";         // the processing input

  if(myFile) {

    #ifdef DEBUG
      Serial.println("SD - Opened file");
    #endif

    while (myFile.available()) {
      input_processing = myFile.readStringUntil('\n');      // read new line
      String name_user(find_data(input_processing));        // get the uid
      if(name_user == card_uid) {                           // compare
        return current_tableid;                             // return if the same
      }

    }

    // not found
    return -1;

  } else {
    #ifdef DEBUG
      Serial.println("SD - Can't find file");
    #endif
    while(1);
  }

  myFile.close();
}
