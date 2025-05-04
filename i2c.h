#include "MCP23017.h"

#define I2C_BANK_1 MCP23017_ADDRESS_20
#define I2C_BANK_2 MCP23017_ADDRESS_21

void initI2C();
void i2cPinOn(uint16_t, uint16_t, uint16_t);
void i2cPinOff(uint16_t, uint16_t, uint16_t);