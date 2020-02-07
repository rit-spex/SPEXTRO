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

    // Increments on true deployment check 
    uint8_t m_vote_pass_counter{0};
    // Set time of deployment
    uint32_t m_time_deployed_ms{0};
    bool m_is_deployed{false};

    uint8_t m_parachute_delay_ms{NOMINAL_PARACHUTE_DELAY};

    // Set time of launch
    uint32_t m_launch_time{0};
    bool m_is_launched{false};

};