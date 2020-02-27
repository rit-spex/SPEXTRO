// 
// SPEXTRO Flight Software
// file: hBNO055.hh
// routine: hBNO055
// desc:
//      Routine used to collect imu data from the BNO055
//

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include "config_defines.hh"

template <typename EnvType>
class hBNO055 : public psycron::PriorityRoutine<EnvType>
{
public:

    void init(){
        m_init_success = m_bno.begin();
    }

private:

    /**
     * Grabs the orientation data from the BNO055 as a quaternion, 
     * updates the flight parameters then logs the quaternion to the 
     * SD card, serializing using google protobuf.
     */
    void handle_orientation(){

    }

    /**
     * Grabs the accelerometer data from the BNO055 for each axis, x, y, z.
     * Update the flight parameters, then logs the acceleration data to the
     * SD card, serializing using google protobuf.
     */
    void handle_accelerometer(){

    }

    void run(){
        if(!m_init_success) return;

    }

    Adafruit_BNO055 m_bno{-1, 0x28};
    bool m_init_success{false};
};