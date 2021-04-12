#include <GlobalDefines.h>
#include <LEDController.h>
#include <Arduino.h>

static int gLastError = 0;

static int arLEDs[] =
{
    LED_4,
    LED_3,
    LED_2,
    LED_1,
};

void ClearInfo()
{
    if (gLastError != 0)
        return;

    for (size_t i = 0; i < sizeof(arLEDs) / sizeof(arLEDs[0]); i++)
        digitalWrite(arLEDs[i], LOW);
}

void ShowInfo(int n)
{
    if (gLastError != 0 || n < 0 || n > 15)
        return;

    for (size_t i = 0; i < sizeof(arLEDs) / sizeof(arLEDs[0]); i++)
        digitalWrite(arLEDs[i], (n >> i) & 1);

    digitalWrite(LED_0, LOW);
}

void SetError(int n)
{
    if (gLastError != 0 || n < -15 || n >= 0)
        return;

    DEBUG_PRINT("Setting error: ");
    DEBUG_PRINT_LN(n);

    gLastError = n;
    char number = n * -1;
    for (size_t i = 0; i < sizeof(arLEDs) / sizeof(arLEDs[0]); i++)
        digitalWrite(arLEDs[i], (number >> i) & 1);

    digitalWrite(LED_0, HIGH);
}

void ClearError(int n)
{
    if (gLastError != n)
        return;

    gLastError = 0;
}

void ResetErrors()
{
    gLastError = 0;

    digitalWrite(LED_0, LOW);
    for (size_t i = 0; i < sizeof(arLEDs) / sizeof(arLEDs[0]); i++)
        digitalWrite(arLEDs[i], LOW);
}