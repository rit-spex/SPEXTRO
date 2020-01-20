
#include <SoftwareSerial.h>

#include "comms_actor.hh"

void CommsActor::init(){
    if(!m_initalized){
        XBEE_SERIAL.begin(XBEE_BAUD_RATE);
        m_xbee.setSerial(XBEE_SERIAL);
        m_initalized = true;
    }
}