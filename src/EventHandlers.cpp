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

unsigned short usA0_Value = 0;
double dBatteryLevel = 0;

void ReadSeonsorData()
{
    CCapSoilSensor cSensor;
    usA0_Value = cSensor.ReadSensorHumidity(MOISTURE_SENSOR_1_PIN);

    CStationInfo cStation;
    dBatteryLevel = (cStation.ReadSupplyVoltage() / 1000.0) + 0.005;

    DEBUG_PRINT("ReadSeonsorData() -> A0: ");
    DEBUG_PRINT(usA0_Value);

    DEBUG_PRINT(" | Battery: ");
    DEBUG_PRINT_LN(dBatteryLevel);

    FireEvent(EVENT_MEASURE_DONE);
};

void PowerUpStation()
{
    DEBUG_PRINT("PowerUpStation()");
    digitalWrite(PIN_STATION_POWER, HIGH);
};

void InitStationConfig()
{
    DEBUG_PRINT("InitStationConfig()");
    gCommandParser.SendCommand(COMMAND_HANDLER_STATION_INIT_CONFIG, CMD_LOAD_FILE_CONFIG);
};

void ConnectToWifi()
{
    DEBUG_PRINT("ConnectToWifi()");
    gCommandParser.SendCommand(COMMAND_HANDLER_INIT_WIFI_ID, CMD_MQTT_INIT);
};

void ConnectToMQTT()
{
    DEBUG_PRINT("ConnectToMQTT()");
    gCommandParser.SendCommand(COMMAND_HANDLER_INIT_MQTT_ID, CMD_MQTT_INIT);
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

void PublishBatteryLevel()
{
    DEBUG_PRINT("PublishBatteryLevel()");

    String strBatteryLevel(dBatteryLevel);
    const char* args[] =
    {
        CMD_MQTT_PUBLISH_TOPIC_ARG,
        MQTT_A0_TOPIC,
        CMD_MQTT_PUBLISH_MESSAGE_ARG,
        strBatteryLevel.c_str()
    };

    int size = sizeof(args) / sizeof(args[0]);
    gCommandParser.SendCommand(COMMAND_HANDLER_PUBLISH_BATTER_ID, CMD_MQTT_PUBLISH, (char**)&args, size);
};

void PublishMeasureInterval()
{
    DEBUG_PRINT("PublishMeasureInterval()");

    String strBatteryLevel(dBatteryLevel);
    const char* args[] =
    {
        CMD_MQTT_PUBLISH_TOPIC_ARG,
        MQTT_A0_TOPIC,
        CMD_MQTT_PUBLISH_MESSAGE_ARG,
        strBatteryLevel.c_str()
    };

    int size = sizeof(args) / sizeof(args[0]);
    gCommandParser.SendCommand(COMMAND_HANDLER_PUBLISH_BATTER_ID, CMD_MQTT_PUBLISH, (char**)&args, size);
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
    digitalWrite(PIN_STATION_POWER, LOW);

    FireEvent(EVENT_POWER_DOWN_STATION_DONE);
};

void EnterPowerSaveMode()
{
    DEBUG_PRINT("PowerDownStation()");

    int sleep = STATION_MEASURE_INTERVAL_SECONDS / 8;
    for (unsigned int i = 0; i < sleep; i++)
        LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_ON);

    sleep = STATION_MEASURE_INTERVAL_SECONDS % 8;
    for (unsigned int i = 0; i < sleep; i++)
        LowPower.powerDown(SLEEP_1S, ADC_ON, BOD_ON);

    FireEvent(EVENT_POWER_SAVE_MODE_OVER);
};

void Idle()
{
    DEBUG_PRINT("Idle()");
    FireEvent(EVENT_EXIT_IDLE);
};