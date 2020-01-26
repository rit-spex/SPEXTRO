
#include <pb_encode.h>
#include <pb_common.h>
#include <telemetry.pb.h>

#include "telemetry_dispatcher.hh"
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


uint8_t TelemetryDispatcher::serialize_altitude(const struct flight_env* env){
    
    spextro_Telemetry message = spextro_Telemetry_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(m_work_buffer, sizeof(m_work_buffer));

    message.header.sent_time_s = env->payload_params.altitude_meters.get_time_updated();
    message.has_header = true;
    message.which_data = spextro_Telemetry_altitude_tag;

    message.data.altitude.altitude_from_sea_level_m = env->payload_params.sea_level_altitude_meters.get_data();
    message.data.altitude.relative_attitude_m = env->payload_params.altitude_meters.get_data();

    bool status = pb_encode(&stream, spextro_Telemetry_fields, &message);

    if(!status) return 0;

    return stream.bytes_written;
};

uint8_t TelemetryDispatcher::serialize_orientation(const struct flight_env* env){};

uint8_t TelemetryDispatcher::serialize_acceleration(const struct flight_env* env){};

uint8_t TelemetryDispatcher::serialize_environmental(const struct flight_env* env){};

uint8_t TelemetryDispatcher::serialize_position(const struct flight_env* env){};

void TelemetryDispatcher::dispatch_telemetry(const struct flight_env* env){

    // Cannot dispatch data
    if(!env->comms_actor.can_load_data()) return;

    uint8_t length_machine{sizeof(telemetry_machine)/sizeof(telemetry_machine[0])};

    if(!telemetry_machine[m_state_counter].should_repeat()){
        m_state_counter += 1;
        if(m_state_counter > length_machine)
                m_state_counter = 0;
    }

    message_type dispatch_type = telemetry_machine[m_state_counter].msg_type;
    uint8_t result_size{0};

    switch (dispatch_type){
        case message_type::altitude:
            result_size = serialize_acceleration(env);
            break;
        case message_type::orientation:
            result_size = serialize_orientation(env);
            break;
        // @TODO add more
        default:
            break;
    };

    if(result_size != 0){
        env->comms_actor.load_data(m_work_buffer, result_size);
    }
}