#ifndef TRANSITION_TABLE__H
#define TRANSITION_TABLE__H

#include <StateMachine.h>
#include <EventHandlers.h>

/*
*   \brief The transition table of the state machine.
*
*   [CHANGE STATE EVENT | CURRENT STATE | NEXT STATE | ON EVENT CHANGE ACTION]
*/
extern const Transition_Entry gTransitionEntries[] =
{
    // IDLE -> CHARGE UP SENSORS
    { EVENT_EXIT_IDLE, STATE_IDLE, STATE_CHARGING_CAPASITIVE_PROBES, ChargeUpSensors },

    // IDLE -> MEASUR (READ SENSORS)
    { EVENT_CHARGING_CAPASITIVE_PROBES_DONE, STATE_CHARGING_CAPASITIVE_PROBES, STATE_MEASURE, ReadSensorData },

    // MEASURE -> STATION POWER UP
    { EVENT_MEASURE_DONE, STATE_MEASURE, STATE_WAITING_POWER_UP_STATION, PowerUpStation },
    
    // STATION POWER UP -> INIT CONFIG FILE
    { EVENT_POWER_UP_STATION_SUCCESS, STATE_WAITING_POWER_UP_STATION, STATE_WAITING_INIT_STATION_CONFIG, InitStationConfig },
    { EVENT_POWER_UP_STATION_TIMED_OUT, STATE_WAITING_POWER_UP_STATION, STATE_POWERING_DOWN_STATION, PowerDownStation },
    
    // INIT CONFIG FILE -> CONNECT TO WIFI
    { EVENT_INIT_STATION_CONFIG_SUCCESS, STATE_WAITING_INIT_STATION_CONFIG, STATE_WAITING_CONNECT_STATION_WIFI, ConnectToWifi },
    { EVENT_INIT_STATION_CONFIG_FAIL, STATE_WAITING_INIT_STATION_CONFIG, STATE_POWERING_DOWN_STATION, PowerDownStation },
    { EVENT_INIT_STATION_CONFIG_TIMED_OUT, STATE_WAITING_INIT_STATION_CONFIG, STATE_POWERING_DOWN_STATION, PowerDownStation },

    // CONNECT TO WIFI -> CONNECT TO MQTT
    { EVENT_WIFI_CONNECT_SUCCESS, STATE_WAITING_CONNECT_STATION_WIFI, STATE_WAITING_CONNECT_STATION_MQTT, ConnectToMQTT },
    { EVENT_WIFI_CONNECT_FAIL, STATE_WAITING_CONNECT_STATION_WIFI, STATE_POWERING_DOWN_STATION, PowerDownStation },
    { EVENT_WIFI_CONNECT_TIMED_OUT, STATE_WAITING_CONNECT_STATION_WIFI, STATE_POWERING_DOWN_STATION, PowerDownStation },

    // CONNECT TO MQTT -> PUBLISH A0
    { EVENT_MQTT_CONNECT_SUCCESS, STATE_WAITING_CONNECT_STATION_MQTT, STATE_WAITING_PUBLISH_SENSOR_DATA_A0, PublishA0 },
    { EVENT_MQTT_CONNECT_FAIL, STATE_WAITING_CONNECT_STATION_MQTT, STATE_WAITING_DISCONNECT_WIFI, DisconnectWifi },
    { EVENT_MQTT_CONNECT_TIMED_OUT, STATE_WAITING_CONNECT_STATION_MQTT, STATE_WAITING_DISCONNECT_WIFI, DisconnectWifi },

    // PUBLISH A0 -> PUBLISH A1
    { EVENT_PUBLISH_A0_SUCCESS, STATE_WAITING_PUBLISH_SENSOR_DATA_A0, STATE_WAITING_PUBLISH_SENSOR_DATA_A1, PublishA1 },
    { EVENT_PUBLISH_A0_FAIL, STATE_WAITING_PUBLISH_SENSOR_DATA_A0, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },
    { EVENT_PUBLISH_A0_TIMED_OUT, STATE_WAITING_PUBLISH_SENSOR_DATA_A0, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },

    // PUBLISH A1 -> PUBLISH BATTERY LEVEL
    { EVENT_PUBLISH_A1_SUCCESS, STATE_WAITING_PUBLISH_SENSOR_DATA_A1, STATE_WAITING_PUBLISH_BATTERY_LEVEL, PublishBatteryLevel },
    { EVENT_PUBLISH_A1_FAIL, STATE_WAITING_PUBLISH_SENSOR_DATA_A1, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },
    { EVENT_PUBLISH_A1_TIMED_OUT, STATE_WAITING_PUBLISH_SENSOR_DATA_A1, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },

    // PUBLISH BATTERY LEVEL -> PUBLISH MEASURE INTERVAL
    { EVENT_PUBLISH_BATTERY_SUCCESS, STATE_WAITING_PUBLISH_BATTERY_LEVEL, STATE_WAITING_PUBLISH_MEASURE_INTERVAL, PublishMeasureInterval },
    { EVENT_PUBLISH_BATTERY_FAIL, STATE_WAITING_PUBLISH_BATTERY_LEVEL, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },
    { EVENT_PUBLISH_BATTERY_TIMED_OUT, STATE_WAITING_PUBLISH_BATTERY_LEVEL, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },
    
    // PUBLISH MEASURE INTERVAL -> DISCONNECT MQTT
    { EVENT_PUBLISH_MEASURE_INTERVAL_SUCCESS, STATE_WAITING_PUBLISH_MEASURE_INTERVAL, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },
    { EVENT_PUBLISH_MEASURE_INTERVAL_FAIL, STATE_WAITING_PUBLISH_MEASURE_INTERVAL, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },
    { EVENT_PUBLISH_MEASURE_INTERVAL_TIMED_OUT, STATE_WAITING_PUBLISH_MEASURE_INTERVAL, STATE_WAITING_DISCONNECT_MQTT, DisconnectMQTT },

    // DISCONNECT MQTT -> DISCONNECT WIFI
    { EVENT_MQTT_DISCONNECT_SUCCESS, STATE_WAITING_DISCONNECT_MQTT, STATE_WAITING_DISCONNECT_WIFI, DisconnectWifi },
    { EVENT_MQTT_DISCONNECT_FAIL, STATE_WAITING_DISCONNECT_MQTT, STATE_WAITING_DISCONNECT_WIFI, DisconnectWifi },
    { EVENT_MQTT_DISCONNECT_TIMED_OUT, STATE_WAITING_DISCONNECT_MQTT, STATE_WAITING_DISCONNECT_WIFI, DisconnectWifi },

    // DISCONNECT WIFI -> POWER DOWN STATION
    { EVENT_WIFI_DISCONNECT_SUCCESS, STATE_WAITING_DISCONNECT_WIFI, STATE_POWERING_DOWN_STATION, PowerDownStation },
    { EVENT_WIFI_DISCONNECT_FAIL, STATE_WAITING_DISCONNECT_WIFI, STATE_POWERING_DOWN_STATION, PowerDownStation },
    { EVENT_WIFI_DISCONNECT_TIMED_OUT, STATE_WAITING_DISCONNECT_WIFI, STATE_POWERING_DOWN_STATION, PowerDownStation },

    // POWER DOWN STATION -> ENTER POWER SAVE MODE
    { EVENT_POWER_DOWN_STATION_DONE, STATE_POWERING_DOWN_STATION, STATE_POWER_SAVE_MODE, EnterPowerSaveMode },

    // ENTER POWER SAVE MODE -> IDLE
    { EVENT_POWER_SAVE_MODE_OVER, STATE_POWER_SAVE_MODE, STATE_IDLE, Idle },
};

#endif // !TRANSITION_TABLE__H