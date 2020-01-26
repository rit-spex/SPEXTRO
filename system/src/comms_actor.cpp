
#include <stdlib.h>
#include <SoftwareSerial.h>

#include "comms_actor.hh"

const bool CommsActor::can_load_data() const{
    return !m_packet_data_loaded;
}

const bool CommsActor::load_data(const uint8_t* data, const uint8_t data_size){
    if(m_packet_data_loaded) return false;

    memcpy(m_load_buffer, data, data_size);
    m_buffer_size = data_size;
    m_packet_data_loaded = true;

    return true;
}

bool CommsActor::receive_handler(bool block_for_tansmit_status){
    
    do {

        if(block_for_tansmit_status){
            if(!m_xbee.readPacket(FAILOVER_TIMEOUT)){
                // Really bad, just bail out
                m_packet_transmitting = false;
                return false;
            }
        } else {
            m_xbee.readPacket();
            // (TRUE) Didn't catch anything this time, it's okay
            if(!m_xbee.getResponse().isAvailable()){
                m_fail_count++;
                // This is also really bad if true, just set state to allow sends
                if(m_fail_count > (uint16_t) FAILOVER_TIMEOUT/mCOMMDIRECTOR_DELAY){
                    m_packet_transmitting = false;
                    m_fail_count = 0;
                }
                continue;
            }

            m_fail_count = 0;
        }

        switch (m_xbee.getResponse().getApiId()) {
            case ZB_TX_STATUS_RESPONSE: {
                ZBTxStatusResponse tx_status = ZBTxStatusResponse{};
                m_xbee.getResponse().getZBTxStatusResponse(tx_status);
                
                if(tx_status.getDeliveryStatus() != SUCCESS){
                    // @TODO handle failure to deliver packet
                }

                m_packet_transmitting = false;
                break;
            } // @TODO Add more cases
            default:
                break;
        }

    } while(block_for_tansmit_status && m_packet_transmitting);

    return true;
}

bool CommsActor::try_send(){
    if(m_packet_data_loaded && !m_packet_transmitting && m_initalized){
        ZBTxRequest tx_request = ZBTxRequest(m_addr_ground, m_load_buffer, m_buffer_size);

        m_xbee.send(tx_request);

        m_packet_data_loaded = false;
        m_packet_transmitting = true;
        return true;
    }

    return false;
}

void CommsActor::perform(){
    if(!m_initalized) return;

    receive_handler();
    try_send();
}

void CommsActor::send_blocking(const uint8_t* data, const uint8_t data_size){
    receive_handler(true); // Make sure we finished previous send.
    if(m_packet_data_loaded){
        // We don't want to overwrite/preempt data already loaded.
        try_send();
        receive_handler(true);
    }
    load_data(data, data_size);
    try_send();
}

void CommsActor::init(){
    if(!m_initalized){
        XBEE_SERIAL.begin(XBEE_BAUD_RATE);
        m_xbee.setSerial(XBEE_SERIAL);
        m_initalized = true;
    }
}