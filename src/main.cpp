#include <Arduino.h>
#include <CommDefinitions.h>
#include <CommandParser.h>
#include <CommandHandler.h>
#include <StateMachine.h>

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    Serial.println("SETUP");

    pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
    // Auto trigger the exit idle event.
    if (STATE_IDLE == gCurrentState)
        FireEvent(EVENT_EXIT_IDLE);

    gCommandParser.FetchCommandResult();
    if (gCommandParser.IsResultAvailable())
    {
        tzCommandResponse cmdResponse;
        gCommandParser.GetLastResponse(&cmdResponse);

        HandleCommand(&cmdResponse);
    }

    delay(20);
}
