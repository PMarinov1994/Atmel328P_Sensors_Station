#ifndef CAP_SOIL_SENSORT__H
#define CAP_SOIL_SENSORT__H

class CCapSoilSensor
{
public:
    CCapSoilSensor();
    ~CCapSoilSensor();

    unsigned short ReadSensorHumidity(int pin);

private:
    long ReadSensor(int pin);
};

#endif // !CAP_SOIL_SENSORT__H