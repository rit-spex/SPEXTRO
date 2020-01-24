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
        this->_get_envrionment().comms_actor.init();
    }

private:

    void run(){
        this->_get_envrionment().comms_actor.perform();
        telemetry_dispatcher.dispatch_telemetry(this->_get_envrionment());
    }

    TelemetryDispatcher telemetry_dispatcher{};
};