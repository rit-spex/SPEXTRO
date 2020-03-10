#pragma once

#define mHEARTBEAT_DELAY 1000
#define mCOMMDIRECTOR_DELAY 10
#define cMISSIONEVENTS_DELAY 20
#define hBNO055_PRIORITY 1
#define hSTRATOLOGGER_DELAY 200

// @TODO Change these
#define XBEE_ADDR_GROUND_HI 0x00000000
#define XBEE_ADDR_GROUND_LOW 0x00000000

#define LOG_FILE_PREFIX "TESTL_"

// Actual flight configuration
#ifdef TEENSY_40_FLIGHT

#define SD_CARD_SPI 10 // CS pin 10

#define PIN_WATCHDOG_RESET 16
#define PIN_SCIENCE_LED 17
#define PIN_SOLENOID 20


#define UART_MAXM8 Serial1
#define MAXM8_BAUD_RATE 9600

// @TODO Change this
#define XBEE_SERIAL Serial2
#define XBEE_BAUD_RATE 9600

// @TODO Change this
#define STRATOLOGGER_SERIAL Serial3
#define STRATOLOGGER_RATE 9600

// #TODO fix these pins
#define PIN_HEARTBEAT_LED LED_BUILTIN
#define PIN_DEPLOY_01 2
#define PIN_DEPLOY_02 3
#define PIN_DEPLOY_03 4
#define PIN_DEPLOY_04 5
#define PIN_ARM_EMATCH_1 23
#define PIN_FIRE_EMATCH_1 9
#define PIN_ARM_EMATCH_0 6
#define PIN_FIRE_EMATCH_0 21

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
#define PIN_ARM_EMATCH_1 23
#define PIN_FIRE_EMATCH_1 9
#define PIN_ARM_EMATCH_0 6
#define PIN_FIRE_EMATCH_0 21

#endif