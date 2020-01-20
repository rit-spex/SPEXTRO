// 
// SPEXTRO Flight Software
// file: mCommsDirector.hh
// routine: mCommsDirector
// desc:
//      Routine used to direct the communications actor.
//

template <typename EnvType>
class mCommsDirector : public psycron::TimedRoutine<EnvType>
{
public:

    void init(){
        this->_get_envrionment().comms_actor.init();
    }

private:

    void run(){
        this->_get_envrionment().comms_actor.perform();
    }
};