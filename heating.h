#define thermistorPin A1
#define heaterGatePin D3

float getTemperature(void);
void controlTemperature(float);
void changeTargetTemperature(float);
void displayTargetTemperature(void);