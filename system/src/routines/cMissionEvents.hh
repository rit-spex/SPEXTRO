// 
// SPEXTRO Flight Software
// file: cMissionEvents.hh
// routine: cMissionEvents
// desc:
//      Routine which handles all critical mission events such as
//      launch detection, payload deployment, science payload trigger and
//      parachute deployment. 
//

#pragma once

template <typename EnvType>
class cMissionEvents : public psycron::TimedRoutine<EnvType>
{


private:

    void check_respond_launch_detection();

    void check_respond_deployment();

    void run(){
        
    }

};