#include <pb_encode.h>
#include <pb_common.h>
#include <telemetry.pb.h>

#include "nanopb_message_utils.hh"

uint8_t serialize_altitude(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<float>* altitude_meters,
    const data_point<float>* sea_level_altitude_meters
){
    
    spextro_Telemetry message = spextro_Telemetry_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);

    message.header.sent_time_s = altitude_meters->get_time_updated();
    message.has_header = true;
    message.which_data = spextro_Telemetry_altitude_tag;

    message.data.altitude.altitude_from_sea_level_m = sea_level_altitude_meters->get_data();
    message.data.altitude.relative_attitude_m = altitude_meters->get_data();

    bool status = pb_encode(&stream, spextro_Telemetry_fields, &message);

    if(!status) return 0;

    return stream.bytes_written;
};

uint8_t serialize_orientation(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<struct orientation_quat>* orientation
){

    spextro_Telemetry message = spextro_Telemetry_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);

    message.header.sent_time_s = orientation->get_time_updated();
    message.has_header = true;
    message.which_data = spextro_Telemetry_orientation_tag;

    message.data.orientation.quaternion.a_comp = orientation->get_data().a;
    message.data.orientation.quaternion.b_comp = orientation->get_data().b;
    message.data.orientation.quaternion.c_comp = orientation->get_data().c;
    message.data.orientation.quaternion.d_comp = orientation->get_data().d;

    bool status = pb_encode(&stream, spextro_Telemetry_fields, &message);

    if(!status) return 0;

    return stream.bytes_written;
};

uint8_t serialize_acceleration(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<struct sensor_bno055_accel>* accel
){

};

uint8_t serialize_environmental(uint8_t* buffer, const uint8_t buffer_size, const struct raw_sensor_data* data){};

uint8_t serialize_position(
    uint8_t* buffer, 
    const uint8_t buffer_size, 
    const data_point<struct gps_position>* gps_position
){
// @TODO
};

uint16_t serialize_bno055(
    uint8_t* buffer, 
    const uint8_t buffer_size,
    const bno055& data
){
    spextro_SensorLog message = spextro_SensorLog_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);

    message.poll_time.sent_time_s = data.poll_time;

    message.has_poll_time = true;
    message.which_data = spextro_SensorLog_bno055_tag;

    message.data.bno055.accel_x = data.accel_x;
    message.data.bno055.accel_y = data.accel_y;
    message.data.bno055.accel_z = data.accel_z;

    message.data.bno055.quaternion_orentation.a_comp = data.a_comp;
    message.data.bno055.quaternion_orentation.b_comp = data.b_comp;
    message.data.bno055.quaternion_orentation.c_comp = data.c_comp;
    message.data.bno055.quaternion_orentation.d_comp = data.d_comp;

    bool status = pb_encode(&stream, spextro_SensorLog_fields, &message);

    if(!status) return 0;

    return stream.bytes_written;
};

uint16_t serialize_stratologger(
    uint8_t* buffer, 
    const uint8_t buffer_size,
    const stratologgerCF& data
){

    spextro_SensorLog message = spextro_SensorLog_init_zero;

    pb_ostream_t stream = pb_ostream_from_buffer(buffer, buffer_size);

    message.poll_time.sent_time_s = data.poll_time;
    message.has_poll_time = true;
    message.which_data = spextro_SensorLog_stratologgerCF_tag;
    message.data.stratologgerCF.altitude_m = data.altitude_m;

    bool status = pb_encode(&stream, spextro_SensorLog_fields, &message);

    if(!status) return 0;

    return stream.bytes_written;
};