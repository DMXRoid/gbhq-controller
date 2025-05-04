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

#define WIFI_SSID "bearony"
#define WIFI_PASSWORD "bloodyshits"


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


#define I2C_SDA 21
#define I2C_SCL 22

#define MCP23017_PORT_A 0x00
#define MCP23017_PORT_B 0x01

#define MCP23017_PIN_LOW 0x00
#define MCP23017_PIN_HIGH 0xFF

#define MCP23017_HIGH 0xFF
#define MCP23017_LOW 0x00

#define PIN_TYPE_NATIVE 0
#define PIN_TYPE_I2C 1

#define CONTACT_SENSOR_PIN T0

extern JsonDocument config;




void initConfig();
void checkIsConfigured();
void saveConfig();
