#include <ArduinoJson.h>

#define FASTLED_ALLOW_INTERRUPTS 0
#define LISTEN_PORT 80
#define LEASE_DURATION 3600

#define CONFIG_MDNS "mdns_name"
#define CONFIG_WIFI "wifi"

#define WIFI_MODE_UNCONFIGURED 0
#define WIFI_MODE_STATION 1
#define WIFI_MODE_SOFT_AP 2
#define WIFI_MODE_DUAL 3

#define WIFI_SSID ""
#define WIFI_PASSWORD ""


#define LOG_FILE "/logs.txt"
#define CONFIG_FILE "/config.json"

#define FLOOR_3_LIGHT_1 0
#define FLOOR_3_LIGHT_2 1
#define FLOOR_2_LIGHT_1 2
#define FLOOR_2_LIGHT_2 3
#define FLOOR_1_LIGHT_1 4
#define FLOOR_1_LIGHT_2 5
#define SLIMER 6
#define BLUE_GHOST 7
#define RED_GHOST 8
#define SPEAKER_OUT 9
#define FRONT_LIGHTS 10


extern JsonDocument config;




void initConfig();
void checkIsConfigured();
void saveConfig();
