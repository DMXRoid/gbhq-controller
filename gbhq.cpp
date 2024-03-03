#include "gbhq.h"
#include "config.h"



GBHQ* gbhqController;

GBHQ::GBHQ() {
	setupPins();	
}

void GBHQ::loop() {

}

void GBHQ::setupPins() {
	pinConfig[FLOOR_3_LIGHT_1] = 13;
	pinConfig[FLOOR_3_LIGHT_2] = 12;
	pinConfig[FLOOR_2_LIGHT_1] = 14;
	pinConfig[FLOOR_2_LIGHT_2] = 27;
	//pinConfig[FLOOR_1_LIGHT_1] = 26;
	//pinConfig[FLOOR_1_LIGHT_2] = 25;
	pinConfig[SLIMER] = 33;
	pinConfig[BLUE_GHOST] = 32;
	pinConfig[RED_GHOST] = 35;

	for(int x = 0; x < sizeof(pinConfig) / sizeof(int); x++) {
		pinMode(pinConfig[x], OUTPUT);
	}	
}
GBHQ* getGBHQController() {
	return gbhqController;
}

void GBHQ::pinOn(int pinIndex) {
	digitalWrite(pinConfig[pinIndex], HIGH);
}

void GBHQ::pinOff(int pinIndex) {
	digitalWrite(pinConfig[pinIndex], LOW);
}

void initGBHQ() {
	gbhqController = new GBHQ();	
}