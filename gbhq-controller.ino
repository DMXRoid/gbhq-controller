#include "config.h"
#include "networking.h"
#include "util.h"
#include "http.h"
#include "audio.h"
#include "servo.h"
#include "gbhq.h"

void initAll() {
	initFS();
	initConfig();
	initNetworking();
	getHttpServer()->init();
	initAudio();
	initI2C();
	initServos();
	initGBHQ();
}

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
	initAll();
}

void loop() {
  networkingLoop();
  getHttpServer()->loop();
  getAudioController()->loop();
  getGBHQController()->loop();
  

}
