#pragma once

#include <stdint.h>

#include <Wire.h>

#ifndef __I2C_REGISTER_HPP__
#define __I2C_REGISTER_HPP__

class I2CDevice
{
public:
    I2CDevice(uint8_t addr)
        : _i2c_address(addr){};

protected:
    const uint8_t _i2c_address;

    /*
     *     Write raw bits into specified registers
     */
    bool write_register(uint8_t reg_addr, uint8_t val)
    {
        Wire.beginTransmission(_i2c_address);
        Wire.write(reg_addr);
        Wire.write(val);
        return Wire.endTransmission() == 0;
    }

    /*
     *     Read N*8 Bits (N registers, from *lower_address, *(lower_address + 1)) and return raw value
     */
    size_t read_register(uint8_t reg_addr, size_t length, uint8_t *data)
    {
        Wire.beginTransmission(_i2c_address);
        Wire.write(reg_addr);
        Wire.endTransmission();

        size_t receivedBytes = Wire.requestFrom(_i2c_address, length);
        if (receivedBytes)
            Wire.readBytes(data, length);
        return receivedBytes;
    }

    /*
     *     Read 8 bits (1 register) and return raw value as unsigned byte
     */
    uint8_t read8(uint8_t reg_addr)
    {
        uint8_t val = 0x00;
        this->read_register(reg_addr, 1, (uint8_t *)&val);
        return val;
    }

    /*
     *     Read 16 Bits (2 registers, from *lower_address, *(lower_address + 1)) and return raw value
     */
    uint16_t read16(uint8_t reg_addr)
    {
        uint16_t val;
        this->read_register(reg_addr, 2, (uint8_t *)&val);
        return val;
    }

public:
    /*
     *     Init function should be provided by all I2CDevice implementations
     */
    virtual void begin() = 0;
};

#endif
