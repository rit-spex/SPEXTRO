#pragma once

#define mHEARTBEAT_DELAY 1000
#define mCOMMDIRECTOR_DELAY 10
#define cMISSIONEVENTS_DELAY 20
#define hBNO055_PRIORITY 1
#define hSTRATOLOGGER_DELAY 200

// @TODO Change these
#define XBEE_ADDR_GROUND_HI 0x00000000
#define XBEE_ADDR_GROUND_LOW 0x00000000

#define LOG_FILE_PREFIX "SPEXTRO_Test-"

// Actual flight configuration
#ifdef TEENSY_40_FLIGHT

#define SD_CARD_SPI BUILTIN_SDCARD

// @TODO Change this
#define XBEE_SERIAL Serial1
#define XBEE_BAUD_RATE 9600

// @TODO Change this
#define STRATOLOGGER_SERIAL Serial2
#define STRATOLOGGER_RATE 9600

// #TODO fix these pins
#define PIN_HEARTBEAT_LED LED_BUILTIN
#define PIN_DEPLOY_01 10
#define PIN_DEPLOY_02 11
#define PIN_DEPLOY_03 12
#define PIN_DEPLOY_04 13
#define PIN_PARACHUTE_TRIGGER 15
#define PIN_PARACHUTE_ARM 16

#endif


// Used for testing
#ifdef TEENSY_36_TEST

#define SD_CARD_SPI BUILTIN_SDCARD

// @TODO Change this
#define XBEE_SERIAL Serial1
#define XBEE_BAUD_RATE 9600

// @TODO Change this
#define STRATOLOGGER_SERIAL Serial2
#define STRATOLOGGER_RATE 9600

// #TODO fix these pins
#define PIN_HEARTBEAT_LED LED_BUILTIN
#define PIN_DEPLOY_01 10
#define PIN_DEPLOY_02 11
#define PIN_DEPLOY_03 12
#define PIN_DEPLOY_04 13
#define PIN_PARACHUTE_TRIGGER 15
#define PIN_PARACHUTE_ARM 16

#endif