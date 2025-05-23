#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>

class WiFi {
	public:
		WiFi(JsonObject);
		static void setMode(int);
		static void setStationSSID(String);
		static void setStationPassword(String);

		static void refresh();


	private:
		static int _wifiMode;
		static String _stationSSID;
		static String _stationPassword;

		static String _softAPSSID;
		static String _softAPPassword;


		static void station();
		static void softAP();
		static void both();
};



void refreshmDNS();
void setmDNSName();
void initWifi();
void initStationWifi();
void initNetworking();
void networkingLoop();
void initOTA();
