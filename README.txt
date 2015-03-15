Arduino Library for the MCP9808 chip (used Arduino I2C Master Library).

Microchip Technology Inc.’s MCP9808 digital temperature sensor converts temperatures between
-20°C and +100°C to a digital word with ±0.25°C/±0.5°C (typical/maximum) accuracy.

The MCP9808 comes with user-programmable registersthat provide flexibility for temperature sensing
applications. The registers allow user-selectable settings such as Shutdown or Low-Power modes and
the specification of temperature Alert window limits and critical output limits. When the temperature 
changes beyond the specified boundary limits, the MCP9808 outputs an Alert signal. The user has the 
option of setting the Alert output signal polarity as an active-low or activehigh comparator output 
for thermostat operation, or as a temperature Alert interrupt output for microprocessorbased systems. 
The Alert output can also be configured as a critical temperature output only.

MCP9808 data-sheet can be found here: http://www.adafruit.com/datasheets/MCP9808.pdf

It uses I2C library for communication with MCP9808 chip. You have to initialize I2c 
instance on your own. Somehow like that:

// Initialize I2C interface.
I2c.begin();
I2c.setSpeed(true);

You can use the same I2c instance for cummunication with more then one chip at the same time.
