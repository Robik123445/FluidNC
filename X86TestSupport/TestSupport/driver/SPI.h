#pragma once
#include <cstdint>

class SPIClass {
public:
    void begin() {}
    uint16_t transfer16(uint16_t value) { return value; }
};

extern SPIClass SPI;
