#include <CommandHandler.h>
#include <CommDefinitions.h>
#include <StateMachine.h>
#include <GlobalDefines.h>
#include <Arduino.h>

void ClearPowerUpError()
{
    digitalWrite(LED_STATION_INIT_ERROR, LOW);
    DEBUG_PRINT_LN("Clear Power up error.");
};

void ReportPowerUpError()
{
    digitalWrite(LED_STATION_INIT_ERROR, HIGH);
    DEBUG_PRINT_LN("Report Power up error.");
};

void ReportStationConfigInitError()
{
    digitalWrite(LED_STATION_CONFIG_INIT_ERROR, HIGH);
    DEBUG_PRINT_LN("Report Station init config error.");
};

void ClearStationConfigInitError()
{
    digitalWrite(LED_STATION_CONFIG_INIT_ERROR, LOW);
    DEBUG_PRINT_LN("Clear Station init config error.");
};

void ClearWifiError()
{
    digitalWrite(LED_WIFI_INIT_ERROR, LOW);
    DEBUG_PRINT_LN("Clear Wifi error.");
};

void ReportWifiError()
{
    digitalWrite(LED_WIFI_INIT_ERROR, HIGH);
    DEBUG_PRINT_LN("Report Wifi error.");
};

void ClearMqttError()
{
    digitalWrite(LED_MQTT_INIT_ERROR, LOW);
    DEBUG_PRINT_LN("Clear MQTT error.");
};

void ReportMqttError()
{
    digitalWrite(LED_MQTT_INIT_ERROR, HIGH);
    DEBUG_PRINT_LN("Report MQTT error.");
};

void ClearPublishError()
{
    digitalWrite(LED_PUBLISH_ERROR, LOW);
    DEBUG_PRINT_LN("Clear Publish error.");
};

void ReportPublishError()
{
    digitalWrite(LED_PUBLISH_ERROR, HIGH);
    DEBUG_PRINT_LN("Report Publish error.");
};

void HandleCommand(tzCommandResponse *cmd)
{
    switch (cmd->m_id)
    {
    case INIT_DONE_ID:
        if (INIT_DONE_RESULT == cmd->m_result)
        {
            ClearPowerUpError();
            FireEvent(EVENT_POWER_UP_STATION_SUCCESS);
        }
        else
        {
            ReportPowerUpError();
            FireEvent(EVENT_POWER_UP_STATION_FAIL);
        }
        break;

    case COMMAND_HANDLER_STATION_INIT_CONFIG:
        if (SUCCESS == cmd->m_result)
        {
            ClearStationConfigInitError();
            FireEvent(EVENT_INIT_STATION_CONFIG_SUCCESS);
        }
        else
        {
            ReportStationConfigInitError();
            FireEvent(EVENT_INIT_STATION_CONFIG_FAIL);
        }
        break;

    case COMMAND_HANDLER_INIT_WIFI_ID:
        if (SUCCESS == cmd->m_result)
        {
            ClearWifiError();
            FireEvent(EVENT_WIFI_CONNECT_SUCCESS);
        }
        else
        {
            ReportWifiError();
            FireEvent(EVENT_WIFI_CONNECT_FAIL);
        }
        break;

    case COMMAND_HANDLER_INIT_MQTT_ID:
        if (SUCCESS == cmd->m_result)
        {
            ClearMqttError();
            FireEvent(EVENT_MQTT_CONNECT_SUCCESS);
        }
        else
        {
            ReportMqttError();
            FireEvent(EVENT_MQTT_CONNECT_FAIL);
        }
        break;

    case COMMAND_HANDLER_PUBLISH_A0_ID:
        if (SUCCESS == cmd->m_result)
        {
            ClearPublishError();
            FireEvent(EVENT_PUBLISH_A0_SUCCESS);
        }
        else
        {
            ReportPublishError();
            FireEvent(EVENT_PUBLISH_A0_FAIL);
        }
        break;

    case COMMAND_HANDLER_PUBLISH_BATTER_ID:
        if (SUCCESS == cmd->m_result)
        {
            ClearPowerUpError();
            FireEvent(EVENT_PUBLISH_BATTERY_SUCCESS);
        }
        else
        {
            ReportPublishError();
            FireEvent(EVENT_PUBLISH_BATTER_FAIL);
        }
        break;

    case COMMAND_HANDLER_PUBLISH_MEASURE_INTERVAL:
        if (SUCCESS == cmd->m_result)
        {
            ClearPublishError();
            FireEvent(EVENT_PUBLISH_MEASURE_INTERVAL_SUCCESS);
        }
        else
        {
            ReportPublishError();
            FireEvent(EVENT_PUBLISH_MEASURE_INTERVAL_FAIL);
        }
        break;

    case COMMAND_HANDLER_DISCONNECT_MQTT_ID:
        if (SUCCESS == cmd->m_result)
            FireEvent(EVENT_MQTT_DISCONNECT_SUCCESS);
        else
            FireEvent(EVENT_MQTT_CONNECT_SUCCESS);
        break;

    case COMMAND_HADNLER_DISCONNECT_WIFI_ID:
        if (SUCCESS == cmd->m_result)
            FireEvent(EVENT_WIFI_DISCONNECT_SUCCESS);
        else
            FireEvent(EVENT_WIFI_DISCONNECT_FAIL);
        break;

    default:
        DEBUG_PRINT_LN("Unknown command handler");
        break;
    }
}