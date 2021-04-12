#include "CapSoilSensor.h"
#include "Arduino.h"
#include "StationInfo.h"
#include <GlobalDefines.h>

#define CAP_SOIL_SENSOR_MIN_VOLTAGE 3300
#define CAP_SOIL_SENSOR_MAX_VOLTAGE 5000

#define CAP_SOIL_SENSOR_DRY_READ_MIN 1256
#define CAP_SOIL_SENSOR_DRY_READ_MAX 1895

#define CAP_SOIL_SENSOR_WET_READ_MIN 2953
#define CAP_SOIL_SENSOR_WET_READ_MAX 4447

CCapSoilSensor::CCapSoilSensor()
{
};

CCapSoilSensor::~CCapSoilSensor()
{
};

unsigned short CCapSoilSensor::ReadSensorHumidity(int pin)
{
    DEBUG_PRINT_LN("ReadSensorHumidity");

    CStationInfo stationInfo;
    long vccMv = stationInfo.ReadSupplyVoltage();
    int moistureMv = this->ReadSensor(pin);

    // To find the sensort value in AIR we need to translate the value in AIR
    // measured at 3.3V (lowest sensor operation value) and at 5V (highest sensor operation value)
    // to the current voltage.
    int sensorDryValue = map(
        vccMv,
        CAP_SOIL_SENSOR_MIN_VOLTAGE,
        CAP_SOIL_SENSOR_MAX_VOLTAGE,
        CAP_SOIL_SENSOR_DRY_READ_MIN,
        CAP_SOIL_SENSOR_DRY_READ_MAX);

    // To find the sensort value in WATTER we need to translate the value in WATTER
    // measured at 3.3V (lowest sensor operation value) and at 5V (highest sensor operation value)
    // to the current voltage.
    int sensorWetValue = map(
        vccMv,
        CAP_SOIL_SENSOR_MIN_VOLTAGE,
        CAP_SOIL_SENSOR_MAX_VOLTAGE,
        CAP_SOIL_SENSOR_WET_READ_MIN,
        CAP_SOIL_SENSOR_WET_READ_MAX);

    // We now have the value in AIR, the value in WATTER and the CURRENT value,
    // all  based on our current battery voltage level which affects the sensor readings. 
    // Calculate in %.
    int moisture = map(
        moistureMv,
        sensorDryValue,
        sensorWetValue,
        0,
        100);

    return moisture;
};

long CCapSoilSensor::ReadSensor(int pin)
{
    // from 0000 to 0111 (7) are valid values.
    if (pin < A0 || pin > A7)
        return 0;

    if (pin >= 14) 
        pin -= 14; // allow for channel or pin numbers

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
};