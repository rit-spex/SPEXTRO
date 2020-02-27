// 
// SPEXTRO Flight Software
// file: hStratologger.hh
// routine: hStratologger
// desc:
//      Routine which interfaces with the StratologgerCF atmospheric 
//      altimeter. 
//

#pragma once

#include "config_defines.hh"

template<typename EnvType>
class hStratologger : public psycron::TimedRoutine<EnvType>{
public:

    void init(){
        STRATOLOGGER_SERIAL.begin(STRATOLOGGER_RATE);

        while(!STRATOLOGGER_SERIAL){
            delay(1);
        }
    };

private:

    /**
     * Updates the system altitude data using altitude data within the read buffer. 
     * The altitude data from the StratologgerCF module is in unit feet and must be converted to meters.
     */
    void update_system_altitude_from_buffer(){
        float altitude = strtof(m_read_buffer, NULL);

        // Convert feet to meters.
        altitude *= 0.3048;

        if(m_got_msl_altitude){
            this->_get_environment().payload_params.altitude_meters.update(millis(), altitude);
        } else {
            this->_get_environment().payload_params.sea_level_altitude_meters.update(millis(), altitude);
            m_got_msl_altitude = true;
        }

        m_buffer_size = 0;
    }

    void run(){

        while(STRATOLOGGER_SERIAL.available()){
            unsigned char in = STRATOLOGGER_SERIAL.read();

            if(in == '\n'){
                // Trigger update
                m_read_buffer[m_buffer_size] = '\0';
                m_buffer_size += 1;
                update_system_altitude_from_buffer();

            } else if (in != '\r'){ // Ignore \r
                m_read_buffer[m_buffer_size] = in;
                m_buffer_size += 1;
            }
        }

    };

    char m_read_buffer[20] = {0};
    uint8_t m_buffer_size{0};
    // First reading from stratologger is absolute altitude
    bool m_got_msl_altitude{false};
};