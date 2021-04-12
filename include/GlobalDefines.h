#ifndef GLOBAL_DEFINES__H
#define GLOBAL_DEFINES__H

#include <Arduino.h>

#define WIFI_STATION_POWER_UP_RESPONSE_TRACKER 0

#define COMMAND_TIME_OUT_SECODNS 8
#define STATION_MEASURE_INTERVAL_SECONDS 15 * 60

#define ERROR_STATION_BOOT_ERROR -1
#define ERROR_STATION_FILE_CONFIG_INIT -2
#define ERROR_STATION_WIFI_CONNECT -3
#define ERROR_STATION_MQTT_CONNECT -4
#define ERROR_STATION_MQTT_PUBLISH -5
#define ERROR_STATION_MQTT_DISCONNECT -6
#define ERROR_STATION_WIFI_DISCONNECT -7

#define LED_0 2
#define LED_1 3
#define LED_2 4
#define LED_3 5
#define LED_4 6

#define PIN_STATION_CH_EN 11

#define MOISTURE_SENSOR_1_PIN A0

const int arInputPins[] =
{
    MOISTURE_SENSOR_1_PIN
};

const int arOutputPins[] =
{
    LED_0,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    PIN_STATION_CH_EN,
};

#define MQTT_A0_TOPIC "Outside_Level_0/A0"
#define MQTT_BATTER_TOPIC "Outside_Level_0/Battery"
#define MQTT_MEASURE_INTERVAL_TOPIC "Outside_Level_0/MeasureInterval"

// Real Global Definitions
#define PRINT_LINES 1

#if (PRINT_LINES == 1)
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINT_LN(x) Serial.println(x)
#else
#define DEBUG_PRINT(x) ((void)0)
#define DEBUG_PRINT_LN(x) ((void)0)
#endif // DEBUG

#endif // !GLOBAL_DEFINES__H