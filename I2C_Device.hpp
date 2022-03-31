#pragma once

#include <stdint.h>

#include <Wire.h>


#ifndef __I2C_DEVICE_HPP__
#define __I2C_DEVICE_HPP__

class I2CDevice{
public:

    I2CDevice(uint8_t addr) : _i2c_address(addr){};

protected:

    const uint8_t _i2c_address;

    /*
    Write raw bits into specified registers
    */
    void write_register(uint8_t addr, uint8_t val){
        Wire.beginTransmission(_i2c_address);
        Wire.write(addr);
        Wire.write(val);
        Wire.endTransmission();
    }

    /*
    Read 8 bits (1 register) and return raw value as unsigned byte
    */
    uint8_t read8(uint8_t addr){
        uint8_t val = 0x00;
        Wire.beginTransmission(_i2c_address);
        Wire.write(addr);
        Wire.endTransmission();
        Wire.requestFrom(_i2c_address, (uint8_t) 1u);
        val |= Wire.read();
        return val;
    }

    /*
    Read 16 Bits (2 registers, from *lower_address, *(lower_address + 1)) and return raw value
    */ 
    uint16_t read16(uint8_t lower_addr){
        uint16_t val;
        Wire.beginTransmission(_i2c_address);
        Wire.write(lower_addr);
        Wire.endTransmission();
        Wire.requestFrom(_i2c_address, (uint8_t) 2u);
        val = (Wire.read() << 8) | Wire.read();
        return val;
    }

public:

    /*
    Init function should be provided by all I2CDevice implementations
    */
    virtual void begin() = 0;

};

#endif