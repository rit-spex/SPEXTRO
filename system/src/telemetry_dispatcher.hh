//
// SPEXTRO Flight Software
// file: telemetry_dispatcher.hh
// class: TelemetryDispatcher
// desc:
//      Schedules telemtry messages using a linear state machine, then 
//      dispatches the binary telemetry message to the requester.
//

#pragma once

#include <stdint.h>

enum message_type{
    altitude,
    orientation,
    environmental,
    position,
    acceleration,
    system_phase
};

struct repeat_message{

    repeat_message(message_type type, uint8_t amount) :
        msg_type{type},
        repeat_amount{amount}
    {};

    /**
     * Used to check if the message should keep being dispatched.
     * 
     * @return True if should repeat, false otherwise
     */
    bool should_repeat(){
        bool result = repeat_count < repeat_amount;
        if(!result){
            repeat_count = 0;
        } else {
            ++repeat_count;
        }

        return result;
    };

    message_type msg_type;
    uint8_t repeat_amount;
    uint8_t repeat_count{0};
};

class TelemetryDispatcher{
public:
    
    /**
     * Dispatches telemetry according to the state machine. Serialized messages are
     * placed in the work buffer to be passed on later.
     * 
     * @param env The environment which contains all the data needed to send relevent telemetry.
     */
    void dispatch_telemetry(struct flight_env* env);

private:

    // Work buffer used to store the serialized packets
    mutable uint8_t m_work_buffer[UINT8_MAX] = {0};

    uint8_t m_state_counter{0};
    // Holds the telemetry state machine 
    static repeat_message telemetry_machine[];
};