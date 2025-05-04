#include <ArduinoJson.h>
#include "config.h"
#include "i2c.h"
#include "util.h"
#include "audio.h"
#include "servo.h"
#include "gbhq.h"



String initialScripts = R"(
	{
		"default": [
			{"target": "ghostbusters-theme*", "action": "on", "delay": 1000, "target_type": 1 },
			{"target": "third_floor_left_light", "action": "on", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "off", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "on", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "off", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "on", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "off", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "on", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "off", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "on", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "off", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "on", "delay": 1000, "target_type": 0 },
			{"target": "third_floor_left_light", "action": "off", "delay": 1000, "target_type": 0 }
		]
	}
)";

GBHQ* gbhqController;


GBHQ::GBHQ() {
	isPlaying = false;
	loadScripts();
	setupPins();	
}

void GBHQ::loadScripts() {
	String scriptConfig = getFileContents("/scripts.json");
	String c = (scriptConfig != "") ? scriptConfig : initialScripts;
	DeserializationError e = deserializeJson(scriptList, c);
  if(e) {
	log("Deserialization error: " + String(e.f_str()));
	deserializeJson(scriptList, initialScripts);
  }
  else {
	serializeJson(scriptList, Serial);
  }
}

void GBHQ::saveScripts() {
	String s;
	serializeJson(scriptList, s);
	writeToFile("/scripts.json", s);
}

void GBHQ::loop() {
	actionLoop();
}

void GBHQ::actionLoop() {
	if(isPlaying) {
		if(currentScriptAction < currentScriptSize) {
			if((millis() - lastScriptAction) > currentScript[currentScriptAction].delay) {
				doCurrentScriptAction();
				lastScriptAction = millis();
				currentScriptAction++;
			}
		}
		else {
			isPlaying = false;
		}
	}
}

void GBHQ::doCurrentScriptAction() {
	doScriptAction(currentScriptAction);
}

void GBHQ::doScriptAction(int scriptActionIndex) {
	/*log("doing an action!");
	log(String(scriptActionIndex));
	log(currentScript[scriptActionIndex].targetName);
	log(currentScript[scriptActionIndex].targetType);
	log(currentScript[scriptActionIndex].action);*/
	if (currentScript[scriptActionIndex].targetType == SCRIPT_TARGET_TYPE_PIN ) {
		// b/c I'm using NPN transistors to drive the LED's, the state of the LED
		// and the pin on the MCP23017 are opposite each other.  The MCP pin being high
		// means that the LED is off, and when the MCP pin is low, the LED is on.

		// at least I think that's why it's happening.  I'm at least right about the implications 
		// if not the cause.
		if (strcmp(currentScript[scriptActionIndex].action,"on") == 0) {
			pinOff(currentScript[scriptActionIndex].targetName);
		}
		else {
			pinOn(currentScript[scriptActionIndex].targetName);
		}
	}
	else if (currentScript[scriptActionIndex].targetType == SCRIPT_TARGET_TYPE_AUDIO ) {
		if(strcmp(currentScript[scriptActionIndex].action, "on") == 0) {
			getAudioController()->loadFile(currentScript[scriptActionIndex].targetName);
			getAudioController()->play();
		}
		else {
			getAudioController()->stop();
		}
	}
	else if (currentScript[scriptActionIndex].targetType == SCRIPT_TARGET_TYPE_SERVO) {
		getServoController()->setServoPosition(String(currentScript[scriptActionIndex].targetName).toInt(), String(currentScript[scriptActionIndex].action).toInt());
	}
	else {
		log("Actions: how did we get here?");
		log(currentScript[scriptActionIndex].targetName);
	}
}

void GBHQ::playScript(const char* scriptName) {
	log("Playing script " + String(scriptName));
	currentScriptName = scriptName;

	// reset the array
	memset(currentScript, 0, sizeof(currentScript));

	for (int x = 0; x < scriptList[scriptName].size(); x++) {
		currentScript[x] = {scriptList[scriptName][x]["target_type"], scriptList[scriptName][x]["target"], scriptList[scriptName][x]["action"], scriptList[scriptName][x]["delay"]};
	}

	currentScriptSize = scriptList[scriptName].size();
	currentScriptAction = 0;
	lastScriptAction = 0;
	isPlaying = true;
}

void GBHQ::pinOn(String name) {
	pinConfig pc = getPin(name);
	if(pc.name != "") {
		i2cPinOn(pc.port, pc.pin, pc.bank);
	}
}

void GBHQ::pinOff(String name) {
	pinConfig pc = getPin(name);
	if (pc.name != "") {
		i2cPinOff(pc.port, pc.pin, pc.bank);
	}
}

pinConfig GBHQ::getPin(String name) {
	pinConfig pc;
	for (int x = 0; x < sizeof(pinConfigs)/sizeof(pinConfig); x++) {
		if(pinConfigs[x].name == name) {
			pc = pinConfigs[x];
			return pc;
		}
	}
	return pc;
}
void GBHQ::setupPins() {
	for (int x = 0; x < sizeof(pinConfigs)/sizeof(pinConfig); x++) {
		if ( pinConfigs[x].type == PIN_TYPE_I2C) {
			if (pinConfigs[x].defaultState == MCP23017_HIGH) {
				//i2cPinOn(pinConfigs[x].port, pinConfigs[x].pin, pinConfigs[x].bank);
			}
		}
	}
}

void GBHQ::cyclePins() {
	for (int x = 0; x < sizeof(pinConfigs)/sizeof(pinConfig); x++) {
		log("Cycling " + pinConfigs[x].displayName);
		for ( int y = 0; y < 5 ; y++) {
			i2cPinOff(pinConfigs[x].port, pinConfigs[x].pin, pinConfigs[x].bank);
			delay(500);
			i2cPinOn(pinConfigs[x].port, pinConfigs[x].pin, pinConfigs[x].bank);
			delay(500);
		}
		i2cPinOff(pinConfigs[x].port, pinConfigs[x].pin, pinConfigs[x].bank);
		
	}

}

GBHQ* getGBHQController() {
	return gbhqController;
}


void initGBHQ() {
	gbhqController = new GBHQ();
}