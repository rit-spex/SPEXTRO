// 
// SPEXTRO Flight Software
// file: hBNO055.hh
// routine: hBNO055
// desc:
//      Routine used to collect imu data from the BNO055
//

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

#include "pins.hh"

template <typename EnvType>
class hBNO055 : public psycron::PriorityRoutine<EnvType>
{
public:

    hBNO055()
        : m_bno{Adafruit_BNO055(-1, 0x28)}
    {}

    void init(){
        m_init_success = m_bno.begin();
        if(!m_init_success){
            // TODO add code to send error
        }
    }

private:

    /**
     * Grabs the orentation data from the BNO055 as a quaternion, 
     * updates the flight parameters then logs the quaternion to the 
     * SD card, serailizing using google protobuf.
     */
    void handle_orentation(){

    }

    /**
     * Grabs the accelrometer data from the BNO055 for each axis, x, y, z.
     * Update the flight parameters, then logs the acceration data to the
     * SD card, seralilizing using google protobuf.
     */
    void handle_accelerometer(){

    }

    void run(){
        if(!m_init_success) return;

    }

    Adafruit_BNO055 m_bno;
    bool m_init_success{false};
};