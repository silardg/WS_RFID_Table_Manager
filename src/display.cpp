#include "display.h"

void setup_display() {

}

void display_show(String current_familyname, String current_uid, int current_tableid) {
  Serial.print("Display - will show: ");
  Serial.print(current_familyname);
  Serial.print(" ");
  Serial.print(current_uid);
  Serial.print(" ");
  Serial.print(current_tableid);
  Serial.println(" ");
}
