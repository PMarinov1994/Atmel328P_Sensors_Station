#ifndef GLOBAL_DEFINES__H
#define GLOBAL_DEFINES__H

#define STATION_MEASURE_INTERVAL_SECONDS 15 * 60

#define LED_STATION_INIT_ERROR 2
#define LED_WIFI_INIT_ERROR 3
#define LED_MQTT_INIT_ERROR 4
#define LED_PUBLISH_ERROR 5
#define LED_STATION_CONFIG_INIT_ERROR 6

#define PIN_STATION_POWER 10
#define PIN_STATION_CH_EN 11

#define MOISTURE_SENSOR_1_PIN A0

const int arInputPins[] =
{
    MOISTURE_SENSOR_1_PIN,
};

const int arOutputPins[] =
{
    LED_STATION_INIT_ERROR,
    LED_WIFI_INIT_ERROR,
    LED_MQTT_INIT_ERROR,
    LED_PUBLISH_ERROR,
    LED_STATION_CONFIG_INIT_ERROR,
    PIN_STATION_POWER,
    PIN_STATION_CH_EN,
};

#define MQTT_A0_TOPIC "Outside_Level_0/A0"
#define MQTT_BATTER_TOPIC "Outside_Level_0/Battery"
#define MQTT_MEASURE_INTERVAL_TOPIC "Outside_Level_0/MeasureInterval"

// Real Global Definitions
#define PRINT_LINES 0

#if (PRINT_LINES == 1)
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINT_LN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x) ((void)0)
#define DEBUG_PRINT_LN(x) ((void)0)
#endif // DEBUG

#endif // !GLOBAL_DEFINES__H