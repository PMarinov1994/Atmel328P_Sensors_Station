#ifndef CAP_SOIL_SENSORT__H
#define CAP_SOIL_SENSORT__H

#define CAP_SOIL_SENSOR_MIN_VOLTAGE 3300
#define CAP_SOIL_SENSOR_MAX_VOLTAGE 5000

#define CAP_SOIL_SENSOR_DRY_READ_MIN 1256
#define CAP_SOIL_SENSOR_DRY_READ_MAX 1895

#define CAP_SOIL_SENSOR_WET_READ_MIN 2953
#define CAP_SOIL_SENSOR_WET_READ_MAX 4447

class CCapSoilSensor
{
public:
    CCapSoilSensor() {};
    ~CCapSoilSensor() {};

    unsigned short ReadSensorHumidity(int pin);

private:
    long ReadSensor(int pin);
};

#endif // !CAP_SOIL_SENSORT__H