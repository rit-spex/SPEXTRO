// 
// SPEXTRO Flight Software
// file: hStratologger.hh
// routine: hStratologger
// desc:
//      Routine which interfaces with the StratologgerCF atmospheric 
//      altimeter. 
//

#pragma once

#include <telemetry.pb.h>

#include "config_defines.hh"
#include "nanopb_message_utils.hh"

#define READ_BUFFER_SIZE 20
// Must be greater than 2
#define ERROR_FAIL_THRESHOLD 5

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
     * Logs the altitude data to the SD card in binary format following the Google protobuf 
     * SensorLog specification.
     */
    void log_altitude_data(const stratologgerCF stratologger_data){

        uint8_t write_buffer[spextro_SensorLog_size] = {0};

        uint16_t write_size = serialize_stratologger(write_buffer, spextro_SensorLog_size, stratologger_data);

        // Write the data to the SD buffer
        this->_get_environment().storage_interface.load_with_size_prepend(write_buffer, write_size);
    }

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

        stratologgerCF stratologger_data{};
        stratologger_data.poll_time = millis();
        stratologger_data.altitude_m = altitude;

        log_altitude_data(stratologger_data);

        m_buffer_size = 0;
    }

    void run(){

        while(STRATOLOGGER_SERIAL.available()){

            // This should never happen, code serves as protection 
            // against index out of range issues
            if(m_buffer_size >= READ_BUFFER_SIZE) {
                m_buffer_size = 0;
            }

            unsigned char in = STRATOLOGGER_SERIAL.read();
            m_fail_counter = 0;

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

        m_fail_counter += 1;

        if(m_fail_counter >= ERROR_FAIL_THRESHOLD){
            // @TODO shoot back a error message to the ground station.
            m_fail_counter = 0;
        }
    };

    char m_read_buffer[READ_BUFFER_SIZE] = {0};
    uint8_t m_buffer_size{0};
    // First reading from stratologger is absolute altitude
    bool m_got_msl_altitude{false};

    // Incremented on no data received 
    uint8_t m_fail_counter{0};
};