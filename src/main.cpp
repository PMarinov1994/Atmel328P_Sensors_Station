#include <Arduino.h>
#include "../.pio/libdeps/pro16MHzatmega328/Low-Power/LowPower.h"

int pin = A0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("SETUP");

    analogReference(INTERNAL);

    pinMode(LED_BUILTIN, OUTPUT);
}

long readVcc()
{
    // Read 1.1V reference against AVcc
    // set the reference to Vcc and the measurement to the internal 1.1V reference
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

    delay(2);            // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA, ADSC))
    {
    }; // measuring

    uint8_t low = ADCL;  // must read ADCL first - it then locks ADCH
    uint8_t high = ADCH; // unlocks both

    long result = (high << 8) | low;

    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
    return result;              // Vcc in millivolts
}

/*
* The reference voltage is set to VCC and we measure at A0. This way
* the resulting voltage will be proportional to the supply voltage and
* we can calculate the value from 3.3V to 5V range of supply voltage.
*/
long readSensor(int pin)
{
    // from 0000 to 0111 (7) are valid values.
    if (pin < 0 || pin > 7)
        return 0;

    // 23.9.1   ADMUX – ADC Multiplexer Selection Register
    ADMUX = _BV(REFS0) | (pin & 0x07); // AVcc with external capacitor at AREF pin

    delay(2);            // Wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Start conversion
    while (bit_is_set(ADCSRA, ADSC))
    {
    }; // measuring

    uint8_t low = ADCL;  // must read ADCL first - it then locks ADCH
    uint8_t high = ADCH; // unlocks both

    long result = (high << 8) | low;

    result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
    return result;
}

int vMinSensorPower = 3300;
int vMaxSensorPower = 5000;

int vSensorDryMin = 1256;
int vSensorDryMax = 1895;

int vSensorWetMin = 2953;
int vSensorWetMax = 4447;

void loop()
{
    delay(500);

    long vccMv = readVcc();
    double vcc = (vccMv / 1000.0) + 0.005;
    Serial.print(vcc);
    Serial.print("V");

    Serial.print(" | Volt: ");
    Serial.print(vccMv);

    int moistureMv = readSensor(A0);
    Serial.print(" | Raw: ");
    Serial.print(moistureMv);

    int sensorDry = map(vccMv, vMinSensorPower,vMaxSensorPower, vSensorDryMin, vSensorDryMax);
    int sensorWet = map(vccMv, vMinSensorPower,vMaxSensorPower, vSensorWetMin, vSensorWetMax);

    int moisture = map(moistureMv, sensorDry, sensorWet, 0, 100);

    Serial.print(" | Moisture: ");
    Serial.print(moisture);
    Serial.println("%");

    Serial.flush();
    // Serial.end();

    // Execution continues from here and not from SETUP.
    LowPower.powerDown(SLEEP_8S, ADC_ON, BOD_ON);
}
