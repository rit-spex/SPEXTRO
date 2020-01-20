
#include <stdlib.h>
#include <SoftwareSerial.h>

#include "comms_actor.hh"

bool CommsActor::can_load_data(){
    return !m_packet_data_loaded;
}

bool CommsActor::load_data(const uint8_t* data, const uint8_t data_size){
    if(m_packet_data_loaded) return false;

    memcpy(m_load_buffer, data, data_size);
    m_packet_data_loaded = true;

    return true;
}

void CommsActor::init(){
    if(!m_initalized){
        XBEE_SERIAL.begin(XBEE_BAUD_RATE);
        m_xbee.setSerial(XBEE_SERIAL);
        m_initalized = true;
    }
}