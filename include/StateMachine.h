#ifndef STATE_MACHINE__H
#define STATE_MACHINE__H

class CStateMachine
{
public:
    CStateMachine();
    ~CStateMachine();

private:
    enum State
    {
        // FIRST
        ENTRY,

        // GET DATA
        MEASURE_VALUE_A0,

        // INIT
        POWER_UP_STATION,
        WAIT_POWER_UP_STATION,
        CONNECT_STATION_WIFI,
        WAIT_CONNECT_STATION_WIFI,
        CONNECT_STATION_MQTT,
        WAIT_CONNECT_STATION_MQTT,
        
        // SEND DATA
        PUBLISH_SENSOR_DATA_A0,
        WAIT_PUBLISH_SENSOR_DATA_A0,
        PUBLISH_BATTERY_LEVEL,
        WAIT_PUBLISH_BATTERY_LEVEL,

        // CLEAN UP
        DISCONNECT_MQTT,
        WAIT_DISCONNECT_MQTT,
        DISCONNECT_WIFI,
        WAIT_DISCONNECT_WIFI,
        POWER_DOWN_STATION,

        // POWER SAVE
        POWER_SAVE_MODE,
    };

    enum Event
    {

    };

    struct Transition_Entry
    {
        State m_from;
        State m_to;
        void* m_action;
    };
};

#endif // !STATE_MACHINE__H