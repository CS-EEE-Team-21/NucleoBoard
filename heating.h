#define thermistorPin A1
#define heaterGatePin D2

float getTemperature(void);
void controlTemperature(float);
void changeTargetTemperature(float);
void displayTargetTemperature(void);