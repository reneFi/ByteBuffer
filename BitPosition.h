#ifndef BITPOSITION_H
#define BITPOSITION_H

#pragma once

#include <cstdint>
#include <cstddef>

namespace ByteBuffer  {

class BitPosition
{
 public:
     constexpr BitPosition():BitPosition(0,0) {};
     constexpr BitPosition(uint32_t bitPos):BitPosition(bitPos/8,bitPos%8) {};
     constexpr BitPosition(uint32_t bytePos, uint8_t bitPos):bitPos(bitPos),bytePos(bytePos) {};
     
     uint8_t getBitPos() {return bitPos;};
     uint32_t getBytePos() {return bytePos;};

     friend BitPosition& operator+=(BitPosition& lhs, const BitPosition& rhs); 
     friend BitPosition& operator+=(BitPosition& lhs, const size_t rhs); 
     
     friend BitPosition operator+(const BitPosition &lhs, const BitPosition &rhs);
     friend BitPosition operator+(const BitPosition &lhs, int rhs);
     
     friend BitPosition& operator++(BitPosition& lhs, int rhs);
     friend BitPosition& operator++(BitPosition& lhs);

     friend BitPosition& operator-=(BitPosition& lhs, const BitPosition& rhs); 

     friend BitPosition operator-(const BitPosition &lhs, const BitPosition &rhs);

     friend BitPosition& operator--(BitPosition& lhs, int rhs);
     friend BitPosition& operator--(BitPosition& lhs);

     friend bool operator==(const BitPosition& lhs, const BitPosition& rhs);
     friend bool operator!=(const BitPosition& lhs, const BitPosition& rhs);
     friend bool operator>(const BitPosition& lhs, const BitPosition& rhs);
     friend bool operator<(const BitPosition& lhs, const BitPosition& rhs);

    private:
     uint8_t bitPos;
     uint32_t bytePos;

};

constexpr BitPosition bitPositionZero(0,0);
constexpr BitPosition bitPositionMax(UINT32_MAX,(UINT8_WIDTH -1));
}

#endif