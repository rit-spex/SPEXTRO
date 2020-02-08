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

#include "config_defines.hh"
#include "flight_env.hh"

#define SWITCH_QUERY_COUNT 20
#define SWITCH_QUERY_THRESHOLD 15
#define DEPLOYMET_CONFIRM 50
#define DEPLOYMENT_TIMEOUT 40000
#define NOMINAL_PARACHUTE_DELAY 2000

template <typename EnvType>
class cMissionEvents : public psycron::TimedRoutine<EnvType>
{
public:

    void init(){

        // Set mode for deployment switches
        pinMode(PIN_DEPLOY_01, INPUT);
        pinMode(PIN_DEPLOY_02, INPUT);
        pinMode(PIN_DEPLOY_03, INPUT);
        pinMode(PIN_DEPLOY_04, INPUT);

        pinMode(PIN_PARACHUTE_ARM, OUTPUT);
        pinMode(PIN_PARACHUTE_TRIGGER, OUTPUT);

        digitalWrite(PIN_PARACHUTE_ARM, LOW);
        digitalWrite(PIN_PARACHUTE_TRIGGER, LOW);

    }

private:

    void check_respond_launch_detection(){
        // Now deployed
        if(m_is_deployed) return;

        // Activate cSciencePayload
    }

    void check_respond_deployment(){
        // Now deployed
        if(m_is_deployed) return;

        uint8_t switch_votes[4] = {0};

        // Pull the state of deployment switches 
        for(int switch_query = 0; switch_query < SWITCH_QUERY_COUNT; switch_query++){
            switch_votes[0] += digitalRead(PIN_DEPLOY_01) == LOW ? 1 : 0;
            switch_votes[1] += digitalRead(PIN_DEPLOY_02) == LOW ? 1 : 0;
            switch_votes[2] += digitalRead(PIN_DEPLOY_03) == LOW ? 1 : 0;
            switch_votes[3] += digitalRead(PIN_DEPLOY_04) == LOW ? 1 : 0;
        }

        uint8_t vote_accumilate{0};
        vote_accumilate += switch_votes[0] >= SWITCH_QUERY_THRESHOLD ? 1 : 0;
        vote_accumilate += switch_votes[1] >= SWITCH_QUERY_THRESHOLD ? 1 : 0;
        vote_accumilate += switch_votes[2] >= SWITCH_QUERY_THRESHOLD ? 1 : 0;
        vote_accumilate += switch_votes[3] >= SWITCH_QUERY_THRESHOLD ? 1 : 0;

        // 4 or 3 switches open - vote passes
        if(vote_accumilate > 2){
            m_vote_pass_counter += 1;
        } else {
            m_vote_pass_counter = 0;
        }

        if(m_vote_pass_counter >= DEPLOYMET_CONFIRM){
            trigger_deployment();
        }

    }

    void trigger_deployment(){
        m_is_deployed = true;
        m_time_deployed_ms = millis();
        this->_get_envrionment().payload_params.system_phase
            .update(millis(), flight_phase::PAYLOAD_DEPLOYED);
        // Activate cRecovery 
        // Activate cSciencePayload
    }

    void check_respond_parachute_deployment(){
        if(!m_is_deployed || m_is_parachute_deployed) return;

        if(m_time_deployed_ms + m_parachute_delay_ms <= millis()){
            trigger_parachute();
        }
    }

    void trigger_parachute(){
        // Trigger the parachute
        digitalWrite(PIN_PARACHUTE_TRIGGER, HIGH);
        m_is_parachute_deployed = true;
        this->_get_envrionment().payload_params.system_phase
            .update(millis(), flight_phase::PARACHUTE_DEPLOYED);
    }

    void run(){
        check_respond_launch_detection();
        check_respond_deployment();
        check_respond_parachute_deployment();
    }

    // Increments on true deployment check 
    uint8_t m_vote_pass_counter{0};
    // Set time of deployment
    uint32_t m_time_deployed_ms{0};
    bool m_is_deployed{false};

    uint16_t m_parachute_delay_ms{NOMINAL_PARACHUTE_DELAY};
    bool m_is_parachute_deployed{false};

    // Set time of launch
    uint32_t m_launch_time_ms{0};
    bool m_is_launched{false};

};