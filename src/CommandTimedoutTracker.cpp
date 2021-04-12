#include <CommandTimeoutTracker.h>
#include <Arduino.h>
#include <GlobalDefines.h>
#include <StateMachine.h>
#include <CommandHandler.h>
#include <LEDController.h>

struct stTracker
{
    unsigned long usEndTime;
    unsigned short iCmdId;
};

typedef struct stTracker Tracker;

struct stCmdEventTimeoutEntry
{
    unsigned short iCmdId;
    Event eTimeOutEvent;
    char sError;
};

typedef struct stCmdEventTimeoutEntry CmdEventTimeoutEntry;

static CmdEventTimeoutEntry gMapCmdToEventTimeout[] =
{
    { WIFI_STATION_POWER_UP_RESPONSE_TRACKER, EVENT_POWER_UP_STATION_TIMED_OUT, ERROR_STATION_BOOT_ERROR },
    { COMMAND_HANDLER_STATION_INIT_CONFIG, EVENT_INIT_STATION_CONFIG_TIMED_OUT, ERROR_STATION_FILE_CONFIG_INIT },
    { COMMAND_HANDLER_INIT_WIFI_ID, EVENT_WIFI_CONNECT_TIMED_OUT, ERROR_STATION_WIFI_CONNECT },
    { COMMAND_HANDLER_INIT_MQTT_ID, EVENT_MQTT_CONNECT_TIMED_OUT, ERROR_STATION_MQTT_CONNECT },
    { COMMAND_HANDLER_PUBLISH_A0_ID, EVENT_PUBLISH_A0_TIMED_OUT, ERROR_STATION_MQTT_PUBLISH },
    { COMMAND_HANDLER_PUBLISH_BATTER_ID, EVENT_PUBLISH_BATTERY_TIMED_OUT, ERROR_STATION_MQTT_PUBLISH },
    { COMMAND_HANDLER_PUBLISH_MEASURE_INTERVAL, EVENT_PUBLISH_MEASURE_INTERVAL_TIMED_OUT,ERROR_STATION_MQTT_PUBLISH },
    { COMMAND_HANDLER_DISCONNECT_MQTT_ID, EVENT_MQTT_DISCONNECT_TIMED_OUT, ERROR_STATION_MQTT_DISCONNECT },
    { COMMAND_HADNLER_DISCONNECT_WIFI_ID, EVENT_WIFI_DISCONNECT_TIMED_OUT, ERROR_STATION_WIFI_DISCONNECT },
};

static Tracker gCmdTracked = { 0 };
static bool gbIsTracking = false;

void TickCommandTracker()
{
    if (!gbIsTracking)
        return;

    if (gCmdTracked.usEndTime > millis())
        return;

    for (unsigned short i = 0; i < sizeof(gMapCmdToEventTimeout) / sizeof(gMapCmdToEventTimeout[0]); i++)
    {
        if (gCmdTracked.iCmdId != gMapCmdToEventTimeout[i].iCmdId)
            continue;

        gbIsTracking = false;

        // For timeout error we will use the normal error with the second to last
        // most significant bit turned on (i.e. bit at 3th possition).
        // If an error is -3, we normally would show [1 0 0 1 1], but since we timedout
        // we will show [1 1 0 1 1]. Errors are up to 7, so for now we can show all of them.
        SetError(gMapCmdToEventTimeout[i].sError + (char)0xF8); // 0xF8 = -8
        FireEvent(gMapCmdToEventTimeout->eTimeOutEvent);
        break;
    }
    
}

void TrackCommand(unsigned short id)
{
    gCmdTracked.iCmdId = id;
    gCmdTracked.usEndTime = millis() + (COMMAND_TIME_OUT_SECODNS * 1000);

    gbIsTracking = true;
}

void UntrackCommand(unsigned short id)
{
    if (gCmdTracked.iCmdId != id)
        return;

    gbIsTracking = false;
}