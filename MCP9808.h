/*
  Copyright (C) 2014 Alik <aliktab@gmail.com> 

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __MCP9808__
#define __MCP9808__

#include <inttypes.h>
#include <limits.h>

class MCP9808 
{
 public:

  // Create MCP9808 object and link it with specified I2C address.
  MCP9808(uint8_t _i2c_addr);

  // Initialize MCP9808 and check it presence.
  bool initialize();  

  // Read temperature from sensor.
  float read_temp_C() const;

  // Put sensor in low consumtion mode
  void shutdown();

  // Return sensor from low consumption to normal mode.
  void wakeup();

 protected:

  uint16_t read_16(uint8_t _reg) const;

  void write_16(uint8_t _reg, uint16_t _val);

 private:

  uint8_t m_i2c_addr;
};

#endif // __MCP9808__
