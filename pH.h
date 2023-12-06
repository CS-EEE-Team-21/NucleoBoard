#define PH_SENSOR A0
#define ACID_PUMP 13
#define ALKALI_PUMP 12

float getPH(void);
void controlPH(float);
void changeTargetPH(float);
void displayTargetPH(void);
