//
// SPEXTRO Flight Software
// file: comms_actor.hh
// class: CommsActor
// desc:
//      Used to facilitate telemetry dispatch and command handling using 
//      an XBee SX transceiver module.
//

#include <stdint.h>
#include <XBee.h>

#include "config_defines.hh"

#define FAILOVER_TIMEOUT 500 // in ms

class CommsActor{
public:

    /**
     * State queries method used to check if data may be loaded into
     * the communications actor or not.
     * 
     * @return True if data can be loaded, false otherwise.
     */
    const bool can_load_data() const;

    /**
     * Used to load data into the communication actor which is sent by 
     * the communications director.
     * 
     * @param data Pointer to the data to be loaded.
     * @param data_size Size of the data to be copied.
     * @return True if data can be loaded, false otherwise.
     */
    const bool load_data(const uint8_t* data, const uint8_t data_size);

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

    /**
     * Memcpys out inbound command buffer, flushing the 
     * command buffer.
     * 
     * @param buffer The buffer to place the command data in.
     * @return The size of the command buffer.
     */
    uint8_t flush_copy_command(uint8_t* buffer, uint8_t buffer_capacity);

private:

    /**
     * Send data in load buffer if we are not transmitting and there
     * is data in the load buffer.
     * 
     * @return True if something was actually sent, false otherwise.
     */
    bool try_send();

    /**
     * Used to handle incoming messages from the transceiver module.
     * 
     * @param block_for_transmit_status Block for transmit status messages.
     * @return False on critical error, true otherwise
     */
    bool receive_handler(bool block_for_transmit_status = false);

    /**
     * Checks for incoming messages over the XBee communication link. 
     * It is possible that invalid state is entered due to a missed transmit status. 
     * Extra logic is used to handle cases where this communication link has possibly broken down. 
     * 
     * @param block_for_messages On true, use blocking reads
     * @return True if message is ready, false otherwise.
     */
    bool read_packet(bool block_for_message);
    

    bool m_initalized{false};

    bool m_packet_data_loaded{false};
    bool m_packet_transmitting{false};
    uint16_t m_fail_count{0};

    // Load buffer used for outbound telemetry data
    uint8_t m_load_buffer[UINT8_MAX] = {0};
    uint8_t m_buffer_size{0};

    // Command buffer used for inbound commands
    uint8_t m_command_buffer[UINT8_MAX] = {0};
    uint8_t m_command_buffer_size{0};

    XBee m_xbee{};
    XBeeAddress64 m_addr_ground{XBEE_ADDR_GROUND_HI, XBEE_ADDR_GROUND_LOW};
};