#include <Arduino.h>
#include <CommDefinitions.h>
#include <CommandParser.h>
#include <CommandHandler.h>
#include <StateMachine.h>
#include <GlobalDefines.h>
#include <CommandTimeoutTracker.h>

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED, SERIAL_8E2);
    Serial.println("SETUP");

    pinMode(LED_BUILTIN, OUTPUT);

    for (unsigned int i = 0; i < sizeof(arInputPins) / sizeof(arInputPins[0]); i++)
        pinMode(arInputPins[i], INPUT);
    
    for (unsigned int i = 0; i < sizeof(arOutputPins) / sizeof(arOutputPins[0]); i++)
    {
        pinMode(arOutputPins[i], OUTPUT);
        digitalWrite(arOutputPins[i], LOW);
    }
}

void loop()
{
    // Auto trigger the exit idle event.
    if (STATE_IDLE == gCurrentState)
        FireEvent(EVENT_EXIT_IDLE);

    TickCommandTracker();
    gCommandParser.FetchCommandResult();
    if (gCommandParser.IsResultAvailable())
    {
        tzCommandResponse cmdResponse;
        gCommandParser.GetLastResponse(&cmdResponse);

        HandleCommand(&cmdResponse);
    }

    delay(20);
}
