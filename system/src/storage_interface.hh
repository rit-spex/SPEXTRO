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

class StorageInterface {
public:

    uint16_t load(uint8_t* source_buffer, uint16_t source_size);

    void init();

private:

    uint16_t write_buffer();

    bool create_file();

    // Persistent file
    File m_file{};

    uint8_t m_buffer[INTERFACE_BUFFER_SIZE] = {0};
    uint16_t m_buffer_size{0};

    bool m_is_initalized{false};
    bool m_encountered_error{false};
};