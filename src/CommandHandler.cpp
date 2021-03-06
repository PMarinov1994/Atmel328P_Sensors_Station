#include <CommandHandler.h>
#include <CommDefinitions.h>
#include <StateMachine.h>
#include <GlobalDefines.h>
#include <Arduino.h>
#include <LEDController.h>
#include <CommandTimeoutTracker.h>

void HandleCommand(tzCommandResponse *cmd)
{
    switch (cmd->m_id)
    {
    case INIT_DONE_ID:

        UntrackCommand(INIT_DONE_ID);
        if (INIT_DONE_RESULT == cmd->m_result)
            FireEvent(EVENT_POWER_UP_STATION_SUCCESS);

        break;
    case COMMAND_HANDLER_STATION_INIT_CONFIG:

        UntrackCommand(COMMAND_HANDLER_STATION_INIT_CONFIG);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_FILE_CONFIG_INIT);
            FireEvent(EVENT_INIT_STATION_CONFIG_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_FILE_CONFIG_INIT);
            FireEvent(EVENT_INIT_STATION_CONFIG_FAIL);
        }
        break;

    case COMMAND_HANDLER_INIT_WIFI_ID:

        UntrackCommand(COMMAND_HANDLER_INIT_WIFI_ID);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_WIFI_CONNECT);
            FireEvent(EVENT_WIFI_CONNECT_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_WIFI_CONNECT);
            FireEvent(EVENT_WIFI_CONNECT_FAIL);
        }

        break;

    case COMMAND_HANDLER_INIT_MQTT_ID:

        UntrackCommand(COMMAND_HANDLER_INIT_MQTT_ID);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_MQTT_CONNECT);
            FireEvent(EVENT_MQTT_CONNECT_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_MQTT_CONNECT);
            FireEvent(EVENT_MQTT_CONNECT_FAIL);
        }

        break;

    case COMMAND_HANDLER_PUBLISH_A0_ID:

        UntrackCommand(COMMAND_HANDLER_PUBLISH_A0_ID);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_A0_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_A0_FAIL);
        }

        break;

    case COMMAND_HANDLER_PUBLISH_A1_ID:

        UntrackCommand(COMMAND_HANDLER_PUBLISH_A1_ID);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_A1_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_A1_FAIL);
        }

        break;

    case COMMAND_HANDLER_PUBLISH_BATTER_ID:

        UntrackCommand(COMMAND_HANDLER_PUBLISH_BATTER_ID);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_BATTERY_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_BATTERY_FAIL);
        }

        break;

    case COMMAND_HANDLER_PUBLISH_MEASURE_INTERVAL:

        UntrackCommand(COMMAND_HANDLER_PUBLISH_MEASURE_INTERVAL);
        if (SUCCESS == cmd->m_result)
        {
            ClearError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_MEASURE_INTERVAL_SUCCESS);
        }
        else
        {
            SetError(ERROR_STATION_MQTT_PUBLISH);
            FireEvent(EVENT_PUBLISH_MEASURE_INTERVAL_FAIL);
        }

        break;

    case COMMAND_HANDLER_DISCONNECT_MQTT_ID:

        UntrackCommand(COMMAND_HANDLER_DISCONNECT_MQTT_ID);
        if (SUCCESS == cmd->m_result)
            FireEvent(EVENT_MQTT_DISCONNECT_SUCCESS);
        else
            FireEvent(EVENT_MQTT_CONNECT_SUCCESS);

        break;

    case COMMAND_HADNLER_DISCONNECT_WIFI_ID:

        UntrackCommand(COMMAND_HADNLER_DISCONNECT_WIFI_ID);
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