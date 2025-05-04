#include <MCP23017.h>
#include "config.h"
#include "util.h"
#include "i2c.h"



MCP23017 bus(I2C_SDA, I2C_SCL);

void initI2C() {
	bus.iodir(MCP23017_PORTA, MCP23017_IODIR_ALL_OUTPUT, MCP23017_ADDRESS_20);
	bus.iodir(MCP23017_PORTB, MCP23017_IODIR_ALL_OUTPUT, MCP23017_ADDRESS_20);
	

	bus.write_gpio(MCP23017_PORTA, 0x00, MCP23017_ADDRESS_20);
	bus.write_gpio(MCP23017_PORTB, 0x00, MCP23017_ADDRESS_20);
}

void i2cPinOn(uint16_t port, uint16_t pin, uint16_t bank) {
	bus.set_gpio_bit(port, pin, bank);
}

void i2cPinOff(uint16_t port, uint16_t pin, uint16_t bank) {
	bus.clear_gpio_bit(port, pin, bank);
}