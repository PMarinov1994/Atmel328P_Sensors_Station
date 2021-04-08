#include <Arduino.h>
#include <LowPower.h>
#include <CommDefinitions.h>

int pin = A0;

void setup()
{
    Serial.begin(SERIAL_COMMUNICATION_SPEED);
    Serial.println("SETUP");

    pinMode(LED_BUILTIN, OUTPUT);
}


void loop()
{
    LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_ON);
}
