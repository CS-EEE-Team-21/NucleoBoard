#define PH_SENSOR A3
#define ACID_PUMP D4
#define ALKALI_PUMP D7

float getPH(void);
void controlPH(float);
void changeTargetPH(float);
void displayTargetPH(void);
