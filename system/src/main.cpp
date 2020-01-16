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

typedef psycron::PsyTrack<flight_env>::PriorityRoutineArgs SPEXTROPriorityRoutineArgs;
typedef psycron::PsyTrack<flight_env>::TimedRoutineArgs SPEXTROTimedRoutineArgs;

int main(){
    psycron::UIIL config{};
    config.sys_milli_second = millis;

    psycron::PsyCron psycron_ins(config, 1);

    flight_env flight_data{};

    psycron_ins.add_application(
        0,
        flight_data,
        SPEXTROTimedRoutineArgs{new mHeartbeat<flight_env>{}, uint16_t{1}, 1000}
    );
}
