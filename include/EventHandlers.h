#ifndef EVENT_HANDLERS__H
#define EVENT_HANDLERS__H

void ChargeUpSensors();
void ReadSensorData();
void PowerUpStation();
void InitStationConfig();
void ConnectToWifi();
void ConnectToMQTT();
void PublishA0();
void PublishA1();
void PublishBatteryLevel();
void PublishMeasureInterval();
void DisconnectMQTT();
void DisconnectWifi();
void PowerDownStation();
void EnterPowerSaveMode();
void Idle();

#endif // !EVENT_HANDLERS__H