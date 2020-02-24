// 
// SPEXTRO Flight Software
// file: mCommsDirector.hh
// routine: mCommsDirector
// desc:
//      Routine used to direct the communications actor.
//

#pragma once

#include "telemetry_dispatcher.hh"

#define DIRECTOR_COMMAND_BUFFER_SIZE UINT8_MAX

template <typename EnvType>
class mCommsDirector : public psycron::TimedRoutine<EnvType>
{
public:

    void init(){
        this->_get_environment().comms_actor.init();
    }

private:

    void handle_command(){
        uint8_t bytes_written = this->_get_environment().comms_actor
            .flush_copy_command(m_command_buffer, DIRECTOR_COMMAND_BUFFER_SIZE);

        if(bytes_written == 0) return;

        // TODO
        // Deserialize message in command buffer.
        // Handle message.
        // Send back message with command status. 
    }

    void run(){
        this->_get_environment().comms_actor.perform();
        // Call to dispatcher which loads telemetry according to the telemetry state machine.
        telemetry_dispatcher.dispatch_telemetry(&this->_get_environment());

    }

    TelemetryDispatcher m_telemetry_dispatcher{};

    uint8_t m_command_buffer[DIRECTOR_COMMAND_BUFFER_SIZE] = {0};

};