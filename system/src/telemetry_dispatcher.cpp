
#include "telemetry_dispatcher.hh"

const repeat_message TelemetryDispatcher::telemetry_machine[9] = {
        repeat_message{message_type::altitude, 1},
        repeat_message{message_type::orientation, 3},
        repeat_message{message_type::accel, 5},
        repeat_message{message_type::environmental, 1},
        repeat_message{message_type::orientation, 3},
        repeat_message{message_type::accel, 5},
        repeat_message{message_type::position, 1},
        repeat_message{message_type::orientation, 3},
        repeat_message{message_type::accel, 5},
};