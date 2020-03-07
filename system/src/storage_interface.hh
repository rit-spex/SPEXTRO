//
// SPEXTRO Flight Software
// file: storage_interface.hh
// class: StorageInterface
// desc:
//      Intermediary layer between data sources and data location. Used to
//      write data to a SD card connected via SPI.
//

#include <stdint.h>
#include <SD.h>

#include "config_defines.hh"

#define INTERFACE_BUFFER_SIZE 16000

class StorageInterface {
public:

    uint16_t load(uint8_t source, uint16_t source_size);

    bool init();

private:

    uint16_t write_buffer();

    bool create_file();

    File m_file;

    uint8_t m_buffer[INTERFACE_BUFFER_SIZE] = {0};
    uint16_t m_buffer_size{0};

    bool m_is_initalized{false};

};