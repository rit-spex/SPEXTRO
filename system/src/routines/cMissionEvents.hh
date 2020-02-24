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

#include <stdlib.h>
#include <math.h>

#include "config_defines.hh"
#include "flight_env.hh"

#define SWITCH_QUERY_COUNT 20
#define SWITCH_QUERY_THRESHOLD 15
#define DEPLOYMET_CONFIRM 25
#define DEPLOYMENT_TIMEOUT 40000
#define NOMINAL_PARACHUTE_DELAY 2500
#define ACCEL_THRESHOLD_MPSS 30

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

        // Deployment timeout time trigger
        if(m_is_launched && m_time_deployed_ms + DEPLOYMENT_TIMEOUT <= millis()){
            trigger_deployment();
            return;
        }

        // Check if we have valid acceleration data
        if(!this->_get_environment().raw_sensor_params.bno055_accel.is_valid()) return;

        const sensor_bno055_accel& accel_bno055 = this->_get_environment().raw_sensor_params.bno055_accel.get_data();

        // Calculate the magnitude of the acceleration vector.
        double accel_magnitude = 
            sqrt(
                accel_bno055.accel_x_mpss * accel_bno055.accel_x_mpss +
                accel_bno055.accel_y_mpss * accel_bno055.accel_y_mpss +
                accel_bno055.accel_z_mpss * accel_bno055.accel_z_mpss
            );

        if(accel_magnitude >= ACCEL_THRESHOLD_MPSS){
            m_threshold_over_cnt += 1;
        } else {
            m_threshold_over_cnt = 0;
        }
        
        // Need 3 values over threshold for trigger
        if(m_threshold_over_cnt >= 3 && !m_is_launched){
            trigger_launch();
        }
    }

    void trigger_launch(){
        m_is_launched = true;
        m_launch_time_ms = millis();
        this->_get_environment().payload_params.system_phase
            .update(millis(), flight_phase::LAUNCHED);
        // Activate cSciencePayload
    }

    /**
     * Uses a voting method to determine payload deployment.
     * 3 or 4 switches depressed, vote passed
     * 2 or 1 switches depressed, vote fails
     * This is done to defeat switch failures such as floating voltage, etc..
     * 
     * On deployment confirmation >= DEPLOYMENT_CONFIRM successful votes, internal
     * state is adjusted accordingly.
     * Requiring subsequent successful votes passed defeats the possibility of deployment 
     * confirming while still in the rocket. There is a chance the payload is not fit
     * exactly inside the rocket causing switches to open and close. 
     * 
     * Vote must pass >= DEPLOYMENT_CONFIRM times for payload to be considered deployed
     * from the last vote fail.
     */
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

    /**
     * Perform the necessary logic to move to the deployed state and 
     * send back telemetry back to the ground station notifying state changes.
     */
    void trigger_deployment(){
        m_is_deployed = true;
        m_time_deployed_ms = millis();
        this->_get_environment().payload_params.system_phase
            .update(millis(), flight_phase::PAYLOAD_DEPLOYED);
        // Activate cRecovery 
        // Activate cSciencePayload
    }

    /**
     * Deploy the parachute m_parachute_delay_ms from m_time_deployed_ms. This entails driving
     * a gpio pin high which triggers duel redundant ematches to start the mechanical sequence.
     */
    void check_respond_parachute_deployment(){
        if(!m_is_deployed || m_is_parachute_deployed) return;

        if(m_time_deployed_ms + m_parachute_delay_ms <= millis()){
            trigger_parachute();
        }
    }

    /**
     * Trigger the mechanical sequence for the parachute, setting internal state 
     * and sending telemetry notifying state.
     */
    void trigger_parachute(){
        // Trigger the parachute
        digitalWrite(PIN_PARACHUTE_TRIGGER, HIGH);
        m_is_parachute_deployed = true;
        this->_get_environment().payload_params.system_phase
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
    uint8_t m_threshold_over_cnt{0};

};