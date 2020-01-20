// 
// SPEXTRO Flight Software
// RIT Space Exploration
// 
// file: main.cpp
// desc:
// 	Main file for the SPEXTRO flight software.
//

#include <PsyCron.hh>
#include <Arduino.h>

#include "routines/routines.hh"
#include "flight_env.hh"
#include "routine_ids.hh"


typedef psycron::PsyTrack<flight_env>::PriorityRoutineArgs SPEXTROPriorityRoutineArgs;
typedef psycron::PsyTrack<flight_env>::TimedRoutineArgs SPEXTROTimedRoutineArgs;

void setup(){
    Serial.begin(9600);
}

void print_msg(char* msg){
    Serial.println(msg);
}

// loop doesn't actually loop
void loop(){
    psycron::UIIL config{};
    config.sys_milli_second = millis;
    config.sys_send_msg = print_msg;

    psycron::PsyCron psycron_ins(config, 1);

    flight_env flight_data{};

    psycron_ins.add_application(
        0,
        flight_data,
        SPEXTROTimedRoutineArgs{new mHeartbeat<flight_env>{}, mHEARTBEAT_ID, mHEARTBEAT_DELAY},
        SPEXTROTimedRoutineArgs{new mCommsDirector<flight_env>{}, mCOMMSDIRECTOR_ID, mCOMMDIRECTOR_DELAY},
        SPEXTROPriorityRoutineArgs{new hBNO055<flight_env>{}, hBNO055_ID, hBNO055_PRIORITY}
    );

    // Blocking call
    psycron_ins.start();
}
