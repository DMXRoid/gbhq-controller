#include <LittleFS.h>
#include <ArduinoJson.h>

#include "config.h"
#include "util.h"

String initialConfig = R"(
	{
		"wifi": {
			"mode": 1,
			"ssid": "",
			"password": "",
			"pk": ""
		},
		"mdns_name": "gbhq",
		"ip_address": "0.0.0.0",
		"mac_address": ""

	}
)";

bool isConfigured;

JsonDocument config;

void initConfig() {
	
  File configFile = LittleFS.open(CONFIG_FILE, "r");
  String cf = configFile.readString();
  configFile.close();
  String c = (cf != "") ? cf : initialConfig;
  log("c string:::" + c);
  DeserializationError e = deserializeJson(config, c);
  if(e) {
	log("Deserialization error: " + String(e.f_str()));
	deserializeJson(config, initialConfig);
	}
  saveConfig();
  /*else {
		log("Initial config: " + initialConfig + " ... ");
		deserializeJson(config, initialConfig);
		serializeJson(config, configFile);
	}*/
}

void checkIsConfigured() {
  if (!isConfigured) {
	initConfig();
  }
}

void saveConfig() {
	File configFile = LittleFS.open(CONFIG_FILE, "w");
	serializeJson(config, configFile);
	configFile.close();
}
