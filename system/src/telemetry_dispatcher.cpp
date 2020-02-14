
#include "telemetry_dispatcher.hh"
#include "nanopb_message_utils.hh"
#include "flight_env.hh"

repeat_message TelemetryDispatcher::telemetry_machine[9] = {
    repeat_message{message_type::altitude, 1},
    repeat_message{message_type::orientation, 3},
    repeat_message{message_type::acceleration, 5},
    repeat_message{message_type::environmental, 1},
    repeat_message{message_type::orientation, 3},
    repeat_message{message_type::acceleration, 5},
    repeat_message{message_type::position, 1},
    repeat_message{message_type::orientation, 3},
    repeat_message{message_type::acceleration, 5},
};

void TelemetryDispatcher::dispatch_telemetry(struct flight_env* env){

    // Cannot dispatch data
    if(!env->comms_actor.can_load_data()) return;

    uint8_t length_machine{sizeof(telemetry_machine)/sizeof(telemetry_machine[0])};

    // Move to next state if current state has completed 
    if(!telemetry_machine[m_state_counter].should_repeat()){
        m_state_counter += 1;
        if(m_state_counter >= length_machine){
            m_state_counter = 0;
        }
    }

    message_type dispatch_type = telemetry_machine[m_state_counter].msg_type;
    uint8_t result_size{0};

    switch (dispatch_type){
        case message_type::altitude:
            result_size = serialize_altitude(
                m_work_buffer, 
                sizeof(m_work_buffer), 
                &env->payload_params.altitude_meters,
                &env->payload_params.sea_level_altitude_meters
            );
            break;
        case message_type::orientation:
            result_size = serialize_orientation(
                m_work_buffer, 
                sizeof(m_work_buffer), 
                &env->payload_params.abs_orentation
            );
            break;
        // @TODO add more
        default:
            break;
    };

    if(result_size != 0){
        env->comms_actor.load_data(m_work_buffer, result_size);
    }
}