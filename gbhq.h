#include <ArduinoJson.h>
#include "config.h"
#include "i2c.h"

#define SCRIPT_ACTION_OFF 0
#define SCRIPT_ACTION_ON 1

#define SCRIPT_TARGET_TYPE_PIN 0
#define SCRIPT_TARGET_TYPE_AUDIO 1
#define SCRIPT_TARGET_TYPE_SERVO 2

#define SCRIPT_MAX_SIZE 500

class GBHQ;

struct pinConfig {
	int type;
	uint16_t defaultState;
	uint16_t bank;
	uint16_t port;
	uint16_t pin;
	String name;
	String displayName;
};

struct scriptAction {
	int targetType;
	const char *targetName;
	const char *action;
	int delay;
};

class GBHQ {
	public:
		GBHQ();
		void loop();
		void pinOn(String);
		void pinOff(String);
		void playScript(const char*);
		void saveScripts();
		void cyclePins();
		void loadScripts();

	private:
		JsonDocument scriptList;
		bool isPlaying;
		int msBetweenTouchPolls = 1000;
		int lastTouchPoll;
		int msToNextScriptAction = 1000;
		int lastScriptAction;
		int currentScriptAction;
		int currentScriptSize;
		scriptAction currentScript[SCRIPT_MAX_SIZE];
		
		String currentScriptName;
		pinConfig pinConfigs[15] = {
			// overhead lights
			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_A, 0, "third_floor_left_light", "Third Floor, Left Light"},  // The left overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_A, 1, "third_floor_right_light", "Third Floor, Right Light"},  // The right overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_A, 4, "second_floor_left_light", "Second Floor, Left Light"},  // The left overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_A, 6, "second_floor_right_light", "Second Floor, Right Light"},  // The right overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_B, 1, "first_floor_left_light", "First Floor, Left Light"},  // The left overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_B, 0, "first_floor_right_light", "First Floor, Right Light"},  // The right overhead light on the 3rd floor

			// Red lights along the door
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_B, 6, "left_door_light", "Left Door Light"},  // The left overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW,  I2C_BANK_1, MCP23017_PORT_B, 4, "right_door_light", "Right Door Light"},  // The right overhead light on the 3rd floor

			// Ghosts

			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_B, 2, "slimer", "Slimer"},  // The left overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_B, 5, "blue_ghost", "Blue Ghost"},  // The right overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_B, 3, "pink_ghost", "Pink Ghost"},  // The left overhead light on the 3rd floor

			// Traffic Light

			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_A, 3, "red_traffic_light", "Red Traffic Light"},  // The left overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_A, 2, "yellow_traffic_light", "Yellow Traffic Light"},  // The right overhead light on the 3rd floor
			{PIN_TYPE_I2C, MCP23017_LOW, I2C_BANK_1, MCP23017_PORT_A, 5, "green_traffic_light", "Green Traffic Light"}  // The left overhead light on the 3rd floor


			// Fireplace
			// Toilet


		};
		
		void setupPins();
		void actionLoop();
		void doCurrentScriptAction();
		void doScriptAction(int);
		
		void touchPoll();
		pinConfig getPin(String);

		
};




void initGBHQ();
GBHQ* getGBHQController();