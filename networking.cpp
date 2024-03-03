#include "config.h"
#include "util.h"
#include "networking.h"


WiFiUDP ntpUDP;
WiFiClient wifiClient;



unsigned long lastRegisterTime;
void initNetworking() {
	lastRegisterTime = 0;
	log("begin init networking");
	initWifi();
	refreshmDNS();
	//initOTA();
	
}


void refreshmDNS() {
	setmDNSName();
	log("Refreshing mDNS setup for " + config[CONFIG_MDNS].as<String>() + "..."); 
	if(!MDNS.begin(config[CONFIG_MDNS].as<String>())) {
		log("mDNS setup failed");
	}
	else {
		MDNS.addService("qdled","tcp", LISTEN_PORT);
		log("mDNS setup complete!");
	}
}

void setmDNSName() {
	String n;
	n = config[CONFIG_MDNS].as<String>();
	log("first ln: " + n);
	if (n == "") {
		n = "new-light-" + String(int(floor(random(1,100))));
		log(n);
	}
	config[CONFIG_MDNS] = n;
}

void initWifi() {

	// defines will override config values if there are no config values 

	if(
		WIFI_SSID != "" 
		&& WIFI_PASSWORD != "" 
		&& config["wifi"]["ssid"] == "" 
		&& config["wifi"]["password"] == ""
		) {
		config["wifi"]["ssid"] = WIFI_SSID;
		config["wifi"]["password"] = WIFI_SSID;
		config["wifi"]["mode"] = WIFI_MODE_STATION;
	}
	switch(int(config["wifi"]["mode"])) {
		case WIFI_MODE_UNCONFIGURED:
			log("unconfigured wifi somehow?");
			delay(1000);
			break;
		
		case WIFI_MODE_STATION:
			initStationWifi();
			break;

		case WIFI_MODE_SOFT_AP:
			break;

		case WIFI_MODE_DUAL:
			break;
	}

}


void initStationWifi() {
	const char* ssid = config["wifi"]["ssid"];
	const char* password = config["wifi"]["password"];

	WiFi.begin(ssid, password);
	
	log("Connecting to " + String(ssid));
	int x = 0;

	while ( WiFi.status() != WL_CONNECTED) {

		delay(1000);
		log("Attempt #" + String(x));
		x++;
	}
	log("Connection established!");	
	log("IP Address: " + WiFi.localIP().toString());
	config["ip_address"] = WiFi.localIP().toString();
	config["mac_address"] = WiFi.macAddress();
	WiFi.setAutoReconnect(true);
	WiFi.persistent(true);
}

void initOTA() {
	log("starting OTA init");
	ArduinoOTA.setHostname(config[CONFIG_MDNS]);
	ArduinoOTA.onStart([]() {
		log("Starting OTA");
	});
	ArduinoOTA.onEnd([]() {
		log("Ending OTA");
	});

	ArduinoOTA.onError([](ota_error_t error) {
		log("OTA Error: " + String(error));
	});

	ArduinoOTA.onProgress([](unsigned int p, unsigned int t) {
		log("OTA Progress: " + String((p / t) * 100));
	});

	ArduinoOTA.begin();
}




void networkingLoop() {
	//ArduinoOTA.handle();
}
