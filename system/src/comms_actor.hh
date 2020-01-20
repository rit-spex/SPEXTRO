//
// SPEXTRO Flight Software
// file: comms_actor.hh
// class: CommsActor
// desc:
//      Used to facilitate telemetry dispatch and command handling using 
//      an XBee SX transciever module.
//

#include <stdint.h>
#include <XBee.h>

#include "config_defines.hh"

class CommsActor{
public:

    /**
     * State queries method used to check if data may be loaded into
     * the communications actor or not.
     * 
     * @return True if data can be loaded, false otherwise.
     */
    bool can_load_data();

    /**
     * Used to load data into the communication actor which is sent by 
     * the comminications director.
     * 
     * @param data Pointer to the data to be loaded.
     * @param data_size Size of the data to be copied.
     * @return True if data can be loaded, false otherwise.
     */
    bool load_data(const uint8_t* data, const uint8_t data_size);

    /**
     * Used to send the data blocking, bypassing the communications director. 
     * 
     * @param data Pointer to the data to be loaded.
     * @param data_size Size of the data to be copied.
     */
    void send_blocking(const uint8_t* data, const uint8_t data_size);

    /**
     * Used to perform state resolution logic, called by the communications 
     * director.
     */
    void perform();

    /**
     * Initialize the transceiver module.
     */
    void init();

private:

    /**
     * Send data in load buffer if we are not transmitting and there
     * is data in the load buffer.
     * 
     * @return True if somthing was actually sent, false otherwise.
     */
    bool try_send();

    /**
     * Used to handle incoming messages from the transciever module.
     * 
     * @param block_for_tansmit_status Block for transmit status messages.
     * @return False on critical error, true otherwise
     */
    bool receive_handler(bool block_for_tansmit_status = false);

    bool m_initalized{false};

    bool m_packet_data_loaded{true};
    bool m_packet_transmitting{false};

    uint8_t m_load_buffer[UINT8_MAX] = {0};
    uint8_t m_buffer_size{0};

    XBee m_xbee{};
    XBeeAddress64 m_addr_ground{XBEE_ADDR_GROUND_HI, XBEE_ADDR_GROUND_LOW};
};