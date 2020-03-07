#include "storage_interface.hh"
#include "config_defines.hh"

void StorageInterface::init(){

    if(!SD.begin(SD_CARD_SPI)){
        m_encountered_error = true;
        return;
    }

    m_is_initalized = true;
    // Attempt to create file for logging.
    generate_filename();

};

void StorageInterface::generate_filename(){
    // @TODO
}