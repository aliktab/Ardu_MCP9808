/*
  Copyright (C) 2014 Alik <aliktab@gmail.com> All rights reserved.

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

#include <I2C.h>
#include <MCP9808.h>


#define MCP9808_ADDRESS                (uint8_t)0x18
#define MCP9808_ADDRMASK               (uint8_t)0x07

#define MCP9808_REG_CONFIG             (uint8_t)0x01

#define MCP9808_REG_CONFIG_SHUTDOWN    (uint8_t)0x0100
#define MCP9808_REG_CONFIG_CRITLOCKED  (uint8_t)0x0080
#define MCP9808_REG_CONFIG_WINLOCKED   (uint8_t)0x0040
#define MCP9808_REG_CONFIG_INTCLR      (uint8_t)0x0020
#define MCP9808_REG_CONFIG_ALERTSTAT   (uint8_t)0x0010
#define MCP9808_REG_CONFIG_ALERTCTRL   (uint8_t)0x0008
#define MCP9808_REG_CONFIG_ALERTSEL    (uint8_t)0x0002
#define MCP9808_REG_CONFIG_ALERTPOL    (uint8_t)0x0002
#define MCP9808_REG_CONFIG_ALERTMODE   (uint8_t)0x0001

#define MCP9808_REG_RESOLUTION_5       (uint8_t)0x00
#define MCP9808_REG_RESOLUTION_25      (uint8_t)0x01
#define MCP9808_REG_RESOLUTION_125     (uint8_t)0x02
#define MCP9808_REG_RESOLUTION_625     (uint8_t)0x03

#define MCP9808_REG_UPPER_TEMP         (uint8_t)0x02
#define MCP9808_REG_LOWER_TEMP         (uint8_t)0x03
#define MCP9808_REG_CRIT_TEMP          (uint8_t)0x04
#define MCP9808_REG_AMBIENT_TEMP       (uint8_t)0x05
#define MCP9808_REG_MANUF_ID           (uint8_t)0x06
#define MCP9808_REG_DEVICE_ID          (uint8_t)0x07
#define MCP9808_REG_RESOLUTION         (uint8_t)0x08


extern I2C I2c;


MCP9808::MCP9808(uint8_t _i2c_addr)
{
  m_i2c_addr = MCP9808_ADDRESS | (_i2c_addr & MCP9808_ADDRMASK);
}

bool MCP9808::initialize()
{
  if (read_16(MCP9808_REG_MANUF_ID)  != 0x0054)
    return false;

  if (read_16(MCP9808_REG_DEVICE_ID) != 0x0400)
    return false;

  return true;
}

float MCP9808::read_temp_C() const
{
  uint16_t temp = read_16(MCP9808_REG_AMBIENT_TEMP);

  float result = (float)(temp & 0x0FFF) / 16.0;
  if (temp & 0x1000) result = 256.0 - result;

  return result;


//#TODO
  // if (temp & 0x8000){ }//TA 3 TCRIT
  // if (temp & 0x4000){ }//TA > TUPPER
  // if (temp & 0x2000){ }//TA < TLOWER


}

void MCP9808::shutdown()
{
  uint16_t conf_reg = read_16(MCP9808_REG_CONFIG);
  conf_reg |= MCP9808_REG_CONFIG_SHUTDOWN;
  write_16(MCP9808_REG_CONFIG, conf_reg);
}

void MCP9808::wakeup()
{
  uint16_t conf_reg = read_16(MCP9808_REG_CONFIG);
  conf_reg ^= MCP9808_REG_CONFIG_SHUTDOWN;
  write_16(MCP9808_REG_CONFIG, conf_reg);
}

uint16_t MCP9808::read_16(uint8_t _reg) const
{
  uint8_t Data[2] = { 0, 0 };

  I2c.read(m_i2c_addr, _reg, sizeof(Data), Data);

  return (Data[0] << 8) | Data[1];
}

void MCP9808::write_16(uint8_t _reg, uint16_t _val)
{
  uint8_t Data[2] =
  {
    (_val >> 8) & 0xff, (_val & 0xff)
  };

  I2c.write(m_i2c_addr, _reg, Data, sizeof(Data));
}

