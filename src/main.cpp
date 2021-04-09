#include <Arduino.h>
#include <CommDefinitions.h>
#include <CommandParser.h>
#include <CommandHandler.h>
#include <StateMachine.h>
#include <GlobalDefines.h>

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    Serial.println("SETUP");

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
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

        DEBUG_PRINT("Got a result: ID: ");
        DEBUG_PRINT(cmdResponse.m_id);
        DEBUG_PRINT(" | result: ");
        DEBUG_PRINT_LN(cmdResponse.m_result);

        HandleCommand(&cmdResponse);
    }

    delay(20);
}
