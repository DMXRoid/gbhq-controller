#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "util.h"

#include "sd.h"

SDController::SDController() {
	if (SD.begin() < 1) {
		log("Error mounting SD card");
	} 
	else {
		initialized = true;
	}
}

void SDController::read(char* fileName) {
	log("Going to read " + String(fileName));

	File file = SD.open(fileName);
	if(!file){
		log("Failed to open file for reading");
		return;
	}

	while(file.available()){
		log(file.read());
	}
	file.close();
}