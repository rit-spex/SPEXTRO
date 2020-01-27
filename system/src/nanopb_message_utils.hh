//
// SPEXTRO Flight Software
// file: nanopb_message_utils.hh
// desc:
//      Utility functions for serializing common data.
//

#pragma once

#include <stdint.h>

#include "flight_env.hh"

/**
 * Serializes altitude data using Google protocol buffers.
 * 
 * @param buffer The buffer to place the result in.
 * @param buffer_size The capacity of the buffer.
 * @param altitude_meters Current altitude in meters stored with time captured.
 * @param sea_level_altitude_meters Baseline altitude in meters with time captured.
 * @return size of the serialized message.
 */
uint8_t serialize_altitude(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<float>* altitude_meters,
    const data_point<float>* sea_level_altitude_meters
);

/**
 * Serializes orientation data using Google protocol buffers.
 * 
 * @param buffer The buffer to place the result in.
 * @param buffer_size The capacity of the buffer.
 * @param orentation The container used to store the orientation data.
 * @return size of the serialized message.
 */
uint8_t serialize_orientation(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<struct orientation>* orientation
);

/**
 * Serializes acceleration data using Google protocol buffers.
 * 
 * @param buffer The buffer to place the result in.
 * @param buffer_size The capacity of the buffer.
 * @param accel The container used to store the acceleration data.
 * @return size of the serialized message.
 */
uint8_t serialize_acceleration(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<struct sensor_bno055_accel>* accel
);

/**
 * Serializes environmental data using Google protocol buffers.
 * 
 * @param buffer The buffer to place the result in.
 * @param buffer_size The capacity of the buffer.
 * @param data The container used to store the environmental data.
 * @return size of the serialized message.
 */
uint8_t serialize_environmental(uint8_t* buffer, const uint8_t buffer_size, const struct raw_sensor_data* data);

/**
 * Serializes gps position data using Google protocol buffers.
 * 
 * @param buffer The buffer to place the result in.
 * @param buffer_size The capacity of the buffer.
 * @param gps_position The container used to store the position data.
 * @return size of the serialized message.
 */
uint8_t serialize_position(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<struct gps_position>* gps_position
);