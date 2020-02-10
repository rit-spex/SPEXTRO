// 
// SPEXTRO Flight Software
// file: mCommsDirector.hh
// routine: mCommsDirector
// desc:
//      Routine used to direct the communications actor.
//

#pragma once

#include "telemetry_dispatcher.hh"

template <typename EnvType>
class mCommsDirector : public psycron::TimedRoutine<EnvType>
{
public:

    void init(){
        this->_get_environment().comms_actor.init();
    }

private:

    void run(){
        this->_get_environment().comms_actor.perform();
        // Call to dispatcher which loads telemetry according to the telemetry state machine.
        telemetry_dispatcher.dispatch_telemetry(&this->_get_environment());
    }

    TelemetryDispatcher telemetry_dispatcher{};
};