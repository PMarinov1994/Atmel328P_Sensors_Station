#ifndef COMMAND_HANDLER__H
#define COMMAND_HANDLER__H

#include <CommandParser.h>

#define COMMAND_HANDLER_POWER_UP_ID                    0
#define COMMAND_HANDLER_STATION_INIT_CONFIG            1
#define COMMAND_HANDLER_INIT_WIFI_ID                   2
#define COMMAND_HANDLER_INIT_MQTT_ID                   3
#define COMMAND_HANDLER_PUBLISH_A0_ID                  4
#define COMMAND_HANDLER_PUBLISH_BATTER_ID              5
#define COMMAND_HANDLER_PUBLISH_MEASURE_INTERVAL       6
#define COMMAND_HANDLER_DISCONNECT_MQTT_ID             7
#define COMMAND_HADNLER_DISCONNECT_WIFI_ID             8
#define COMMAND_HANDLER_PUBLISH_A1_ID                  9

void HandleCommand(tzCommandResponse * cmd);

#endif // !COMMAND_HANDLER__H