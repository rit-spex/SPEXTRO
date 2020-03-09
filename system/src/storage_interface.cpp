
#include <string.h>
#include <stdlib.h>

#include "storage_interface.hh"
#include "config_defines.hh"

void StorageInterface::init(){

    if(!SD.begin(SD_CARD_SPI)){
        m_encountered_error = true;
        return;
    }

    m_is_initalized = true;
    // Attempt to create file for logging.
    generate_log_filename();

};

void StorageInterface::generate_log_filename(){
    
    if(!m_is_initalized) return;

    char temp_filename[FILENAME_CAP] = {0};
    uint16_t seq_number{0};

    do{
        // Copy in prefix
        strlcpy(temp_filename, LOG_FILE_PREFIX, FILENAME_CAP);

        char seq_buffer[10] = {'\0'};
        // This could overflow
        itoa(seq_number, seq_buffer, 10);

        strlcat(temp_filename, seq_buffer, FILENAME_CAP);

        seq_number += 1;

    } while(SD.exists(temp_filename));

    m_log_filename[0] = '\0';
    // Set to final filename
    strlcpy(m_log_filename, temp_filename, FILENAME_CAP);

}

uint16_t StorageInterface::load(const uint8_t* source_buffer, const uint16_t source_size){
    // Be sure SD has been initialized and write size is not larger than the buffer.
    if(!m_is_initalized || source_size >= INTERFACE_BUFFER_SIZE) return 0;

    if(m_buffer_size >= INTERFACE_BUFFER_SIZE - source_size) {
        // Post condition is m_buffer_size = 0
        write_buffer();
    }

    // Load data into buffer
    memcpy(m_buffer, source_buffer, source_size);
    m_buffer_size += source_size;

    return source_size;
}

uint16_t StorageInterface::load_with_size_prepend(const uint8_t* source_buffer, const uint16_t source_size){
    // Be sure SD has been initialized and write size is not larger than the buffer.
    if(!m_is_initalized || source_size + sizeof(uint16_t) >= INTERFACE_BUFFER_SIZE) return 0;

    union size_char{
        uint16_t size;
        uint8_t size_char_arry[sizeof(uint16_t)];
    } size_convert;

    size_convert.size = source_size;
    uint16_t bytes_written{0};

    // Write size to buffer
    bytes_written += load(size_convert.size_char_arry, sizeof(uint16_t));
    // Write actual data to buffer
    bytes_written += load(source_buffer, source_size);
    
    return bytes_written;
}

uint16_t StorageInterface::write_buffer(){

    if(!m_is_initalized || m_buffer_size == 0) return 0;

    File log_file = SD.open(m_log_filename, O_CREAT | O_APPEND);

    if(!log_file){
        // @TODO send error 
        m_buffer_size = 0;
        return 0;
    }

    size_t bytes_written = log_file.write(m_buffer, m_buffer_size);
    m_buffer_size = 0;

    log_file.close();

    return bytes_written;
}