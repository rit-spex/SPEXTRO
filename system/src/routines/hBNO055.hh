// 
// SPEXTRO Flight Software
// file: hBNO055.hh
// routine: hBNO055
// desc:
//      Routine used to collect imu data from the BNO055
//

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include <telemetry.pb.h>

#include "config_defines.hh"
#include "nanopb_message_utils.hh"

template <typename EnvType>
class hBNO055 : public psycron::PriorityRoutine<EnvType>
{
public:

    void init(){
        m_init_success = m_bno.begin(Adafruit_BNO055::OPERATION_MODE_NDOF);
    }

private:

    void log_bno055_data(bno055& bno055_data){

        uint8_t write_buffer[spextro_SensorLog_size] = {0};

        uint16_t write_size = serialize_bno055(write_buffer, spextro_SensorLog_size, bno055_data);

        // Write the data to the SD buffer
        this->_get_environment().storage_interface.load_with_size_prepend(write_buffer, write_size);
    }

    /**
     * Grabs the orientation data from the BNO055 as a quaternion, 
     * updates the flight parameters then logs the quaternion to the 
     * SD card, serializing using google protobuf.
     */
    void handle_orientation(bno055& bno055_data){
        imu::Quaternion quat = m_bno.getQuat();

        bno055_data.a_comp = quat.x();
        bno055_data.b_comp = quat.y();
        bno055_data.c_comp = quat.z();
        bno055_data.d_comp = quat.w();

        // Pack struct for system update
        orientation_quat system_update{};
        system_update.a = quat.x();
        system_update.b = quat.y();
        system_update.c = quat.z();
        system_update.d = quat.w();

        this->_get_environment().payload_params.abs_orentation.update(millis(), system_update);
    }

    /**
     * Grabs the accelerometer data from the BNO055 for each axis, x, y, z.
     * Update the flight parameters, then logs the acceleration data to the
     * SD card, serializing using google protobuf.
     * 
     * @param bno055_data Data struct which is populated with acceleration data.
     */
    void handle_accelerometer(bno055& bno055_data){
        sensors_event_t accel_event_data;
        bool error_s = m_bno.getEvent(&accel_event_data, Adafruit_BNO055::VECTOR_LINEARACCEL); 

        if(error_s){
            // @TODO REPORT ERROR
        }

        // Update data to be written
        bno055_data.accel_x = accel_event_data.acceleration.x;
        bno055_data.accel_y = accel_event_data.acceleration.y;
        bno055_data.accel_z = accel_event_data.acceleration.z;

        // Pack struct for system update
        sensor_bno055_accel system_update;
        system_update.accel_x_mpss = accel_event_data.acceleration.x;
        system_update.accel_y_mpss = accel_event_data.acceleration.y;
        system_update.accel_z_mpss = accel_event_data.acceleration.z;

        this->_get_environment().raw_sensor_params.bno055_accel.update(millis(), system_update);
    }

    void run(){

        if(!m_init_success) return;

        bno055 write_data{};
        handle_accelerometer(write_data);
        handle_orientation(write_data);

        write_data.poll_time = millis();
        // Write collected data to sd card
        log_bno055_data(write_data);
    }

    Adafruit_BNO055 m_bno{-1, 0x28};
    bool m_init_success{false};
};