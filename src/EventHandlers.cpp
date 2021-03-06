#include <EventHandlers.h>
#include <CapSoilSensor.h>
#include <StateMachine.h>
#include <StationInfo.h>
#include <Arduino.h>
#include <GlobalDefines.h>
#include <CommandParser.h>
#include <CommDefinitions.h>
#include <CommandHandler.h>
#include <LowPower.h>
#include <LEDController.h>
#include <CommandTimeoutTracker.h>

unsigned short usA0_Value = 0;
unsigned short usA1_Value = 0;
double dBatteryLevel = 0;

void PowerDown(int seconds)
{
    Serial.flush();

    int sleep = seconds / 8;
    for (int i = 0; i < sleep; i++)
        LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_ON);

    sleep = seconds % 8;
    for (int i = 0; i < sleep; i++)
        LowPower.powerDown(SLEEP_1S, ADC_ON, BOD_ON);
}

void ChargeUpSensors()
{
    DEBUG_PRINT_LN("ChargeUpSensors()");

    digitalWrite(SENSORS_POWER_PIN, HIGH);
    PowerDown(CAPACITIVE_SENSORTS_CHARGE_TIME_SECONDS);

    FireEvent(EVENT_CHARGING_CAPASITIVE_PROBES_DONE);
}

void ReadSensorData()
{
    digitalWrite(LED_BUILTIN, HIGH);

    CCapSoilSensor cSensor;
    usA0_Value = cSensor.ReadSensorHumidity(MOISTURE_SENSOR_1_PIN);
    delay(20);
    usA1_Value = cSensor.ReadSensorHumidity(MOISTURE_SENSOR_2_PIN);

    CStationInfo cStation;
    dBatteryLevel = (cStation.ReadSupplyVoltage() / 1000.0) + 0.005;

    DEBUG_PRINT("ReadSensorData() -> A0: ");
    DEBUG_PRINT(usA0_Value);

    DEBUG_PRINT("ReadSensorData() -> A1: ");
    DEBUG_PRINT(usA1_Value);

    DEBUG_PRINT(" | Battery: ");
    DEBUG_PRINT_LN(dBatteryLevel);

    digitalWrite(SENSORS_POWER_PIN, LOW);
    FireEvent(EVENT_MEASURE_DONE);
};

void PowerUpStation()
{
    DEBUG_PRINT("PowerUpStation()");
    TrackCommand(INIT_DONE_ID);
    digitalWrite(PIN_STATION_CH_EN, HIGH);
};

void InitStationConfig()
{
    DEBUG_PRINT("InitStationConfig()");
    gCommandParser.SendCommand(COMMAND_HANDLER_STATION_INIT_CONFIG, CMD_LOAD_FILE_CONFIG);
};

void ConnectToWifi()
{
    DEBUG_PRINT("ConnectToWifi()");
    gCommandParser.SendCommand(COMMAND_HANDLER_INIT_WIFI_ID, CMD_WIFI_CONNECT_FROM_FILE);
};

void ConnectToMQTT()
{
    DEBUG_PRINT("ConnectToMQTT()");
    gCommandParser.SendCommand(COMMAND_HANDLER_INIT_MQTT_ID, CMD_MQTT_INIT_FROM_FILE);
};

void PublishA0()
{
    DEBUG_PRINT("PublishA0()");

    String strA0(usA0_Value);
    const char* args[] =
    {
        CMD_MQTT_PUBLISH_TOPIC_ARG,
        MQTT_A0_TOPIC,
        CMD_MQTT_PUBLISH_MESSAGE_ARG,
        strA0.c_str()
    };

    int size = sizeof(args) / sizeof(args[0]);
    gCommandParser.SendCommand(COMMAND_HANDLER_PUBLISH_A0_ID, CMD_MQTT_PUBLISH, (char**)&args, size);
};

void PublishA1()
{
    DEBUG_PRINT("PublishA1()");

    String strA1(usA1_Value);
    const char* args[] =
    {
        CMD_MQTT_PUBLISH_TOPIC_ARG,
        MQTT_A1_TOPIC,
        CMD_MQTT_PUBLISH_MESSAGE_ARG,
        strA1.c_str()
    };

    int size = sizeof(args) / sizeof(args[0]);
    gCommandParser.SendCommand(COMMAND_HANDLER_PUBLISH_A1_ID, CMD_MQTT_PUBLISH, (char**)&args, size);
};

void PublishBatteryLevel()
{
    DEBUG_PRINT("PublishBatteryLevel()");

    String strBatteryLevel(dBatteryLevel);
    const char* args[] =
    {
        CMD_MQTT_PUBLISH_TOPIC_ARG,
        MQTT_BATTER_TOPIC,
        CMD_MQTT_PUBLISH_MESSAGE_ARG,
        strBatteryLevel.c_str()
    };

    int size = sizeof(args) / sizeof(args[0]);
    gCommandParser.SendCommand(COMMAND_HANDLER_PUBLISH_BATTER_ID, CMD_MQTT_PUBLISH, (char**)&args, size);
};

void PublishMeasureInterval()
{
    DEBUG_PRINT("PublishMeasureInterval()");

    String strMeasureInterval(STATION_MEASURE_INTERVAL_SECONDS);
    const char* args[] =
    {
        CMD_MQTT_PUBLISH_TOPIC_ARG,
        MQTT_MEASURE_INTERVAL_TOPIC,
        CMD_MQTT_PUBLISH_MESSAGE_ARG,
        strMeasureInterval.c_str()
    };

    int size = sizeof(args) / sizeof(args[0]);
    gCommandParser.SendCommand(COMMAND_HANDLER_PUBLISH_MEASURE_INTERVAL, CMD_MQTT_PUBLISH, (char**)&args, size);
};

void DisconnectMQTT()
{
    DEBUG_PRINT("DisconnectMQTT()");
    gCommandParser.SendCommand(COMMAND_HANDLER_DISCONNECT_MQTT_ID, CMD_MQTT_DISCONECT);
};

void DisconnectWifi()
{
    DEBUG_PRINT("DisconnectWifi()");
    gCommandParser.SendCommand(COMMAND_HADNLER_DISCONNECT_WIFI_ID, CMD_WIFI_DISCONECT);
};

void PowerDownStation()
{
    DEBUG_PRINT("PowerDownStation()");
    digitalWrite(PIN_STATION_CH_EN, LOW);

    FireEvent(EVENT_POWER_DOWN_STATION_DONE);
};

void EnterPowerSaveMode()
{
    DEBUG_PRINT("PowerDownStation()");
    
    digitalWrite(LED_BUILTIN, LOW);
    ClearInfo();

    PowerDown(STATION_MEASURE_INTERVAL_SECONDS);
    FireEvent(EVENT_POWER_SAVE_MODE_OVER);
};

void Idle()
{
    DEBUG_PRINT("Idle()");
    ResetErrors();
    FireEvent(EVENT_EXIT_IDLE);
};