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

    for (unsigned int i = 0; i < sizeof(arInputPins) / sizeof(arInputPins[0]); i++)
        pinMode(arInputPins[i], INPUT);
    
    for (unsigned int i = 0; i < sizeof(arOutputPins) / sizeof(arOutputPins[0]); i++)
        pinMode(arOutputPins[i], OUTPUT);
}

#include <CapSoilSensor.h>
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
