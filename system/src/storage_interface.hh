//
// SPEXTRO Flight Software
// file: storage_interface.hh
// class: StorageInterface
// desc:
//      Intermediary layer between data sources and data location. Used to
//      write data to a SD card connected via SPI.
//

#pragma once

#include <stdint.h>
#include <SD.h>

#include "config_defines.hh"

#define INTERFACE_BUFFER_SIZE 16000
#define FILENAME_CAP 30

class StorageInterface {
public:

    uint16_t load(const uint8_t* source_buffer, const uint16_t source_size);

    uint16_t load_with_size_prepend(const uint8_t* source_buffer, const uint16_t source_size);

    void init();

private:

    /**
     * Writes all contents in m_buffer to the log file.
     * 
     * @return Number of bytes written.
     */
    uint16_t write_buffer();

    void generate_log_filename();

    char m_log_filename[FILENAME_CAP] = {0};

    uint8_t m_buffer[INTERFACE_BUFFER_SIZE] = {0};
    uint16_t m_buffer_size{0};

    bool m_is_initalized{false};
    bool m_encountered_error{false};
};