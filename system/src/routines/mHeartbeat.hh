// 
// SPEXTRO Flight Software
// file: mHeartbeat.hh
// routine: mHeartbeat
// desc:
//      Routine used to toggle the heartbeat.
//

#include "config_defines.hh"

template <typename EnvType>
class mHeartbeat : public psycron::TimedRoutine<EnvType>
{
public:

    void init(){
        pinMode(PIN_HEARTBEAT_LED, OUTPUT);
        digitalWrite(PIN_HEARTBEAT_LED, LOW);
    }

private:

    void run(){

        if(m_is_on){
            digitalWrite(PIN_HEARTBEAT_LED, LOW);
            m_is_on = false;
        } else {
            digitalWrite(PIN_HEARTBEAT_LED, HIGH);
            m_is_on = true;
        }
    }

    bool m_is_on{false};
};
