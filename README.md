# WS-RFID Table Manager

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

## Installing
- Download VSCode or Atom
- Install PlatformIO
- ```git clone https://github.com/silardg/WS_RFID_Table_Manager``` this repo, and open it in your editor
- Build & Flash

## Adding display
- ```display.cpp``` and ```display.h``` with ```setup_display()```
- to get the chosen family name, table id and the uid after line ```78 - sd_driver.cpp``` you can display variables ```char current_familyname[20];char current_uid[20];int current_tableid;```
