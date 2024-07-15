#ifndef BITPOSITION_H
#define BITPOSITION_H

#pragma once

#include <cstdint>
#include <cstddef>
#include <tuple>

namespace ByteBuffer  {

constexpr uint16_t maxBitPos = 256;
constexpr uint16_t bitPerByte = 8;

class BitPosition
{
 public:
     
     constexpr BitPosition():BitPosition(0,0) {};
     constexpr BitPosition(uint32_t bitPos):BitPosition(bitPos / bitPerByte,bitPos % bitPerByte) {};
     constexpr BitPosition(uint32_t bytePos, uint8_t bitPos):bitPos(bitPos),bytePos(bytePos) {};
     
     uint8_t getBitPos() {return bitPos;};
     uint32_t getBytePos() {return bytePos;};

     // addition assignement operators
     
     /// @brief This method implements the addition assignement operator of two Bitposition objects 
     /// @param lhs - object to which is added 
     /// @param rhs - object to add
     /// @return modified lhs
     friend BitPosition& operator+=(BitPosition& lhs, const BitPosition& rhs) {
        lhs.bitPos += rhs.bitPos;
    
        // remove wrap around
        lhs.bytePos += lhs.bitPos / bitPerByte;
        lhs.bitPos %= bitPerByte;

        lhs.bytePos += rhs.bytePos;
        return lhs;
     }
     
     /// @brief This method implements the addition assignement operator of two Bitposition objects 
     /// @param lhs - object to which is added 
     /// @param rhs - offset to add
     /// @return modified lhs 
     friend BitPosition& operator+=(BitPosition& lhs, const uint32_t rhs){
    
        lhs.bitPos += rhs % bitPerByte;
    
        // remove wrap around
        lhs.bytePos += lhs.bitPos / bitPerByte;
        lhs.bitPos %= bitPerByte;

        lhs.bytePos += rhs/bitPerByte;    
        return lhs;
     } 
      

     // addition operators 

     /// @brief This method implements the addition operator of two Bitposition objects 
     /// @param lhs - first summand
     /// @param rhs - second summand
     /// @return sum of both objects
     friend BitPosition operator+(const BitPosition &lhs, const BitPosition &rhs){
        BitPosition bp(lhs);
        bp += rhs;

        return bp;
     }

     /// @brief This method implements the addition operator of two Bitposition objects 
     /// @param lhs - first summand
     /// @param rhs - second summand
     /// @return sum of both objects
     friend BitPosition operator+(const BitPosition &lhs, int rhs) {
        BitPosition bp(lhs);
        bp += rhs;

        return bp;
     }
     

     // inkrement operators

     /// @brief This method implements the postfix inkrement operator of Bitposition object 
     /// @param lhs - object to be inkremented
     /// @param rhs - second summand is ignored
     /// @return inkremented object
     friend BitPosition& operator++(BitPosition& lhs, int /*rhs*/) {
        operator++(lhs);
        return lhs;
     }

     /// @brief This method implements the prefix inkrement operator of Bitposition object 
     /// @param lhs - object to be inkremented
     /// @return inkremented object
     friend BitPosition& operator++(BitPosition& lhs) {
        lhs += 1;
        return lhs;
     }


     // subtraction assignement operators
     
     /// @brief This method implements the subtraction assignement operator of two Bitposition objects 
     /// @param lhs - object from which is subtracted 
     /// @param rhs - object to subtract
     /// @return modified lhs
     friend BitPosition& operator-=(BitPosition& lhs, const BitPosition& rhs) {
        lhs.bitPos -= rhs.bitPos;
        if (lhs.bitPos > 7){
            uint8_t bitDiff = static_cast<uint8_t>(maxBitPos - lhs.bitPos);
            lhs.bitPos = bitPerByte - bitDiff % bitPerByte;
            lhs.bytePos -= 1 + bitDiff / bitPerByte;
        }
        lhs.bytePos -= rhs.bytePos;
        return lhs;
     } 

     // subtraction operators 

     /// @brief This method implements the subtraction operator of two Bitposition objects 
     /// @param lhs - first 
     /// @param rhs - second 
     /// @return difference of both objects
     friend BitPosition operator-(const BitPosition &lhs, const BitPosition &rhs) {
        BitPosition bp(lhs);
        bp -= rhs;

        return bp;
     }

     // decrement operators

     /// @brief This method implements the postfix decrement operator of Bitposition object 
     /// @param lhs - object to be decremented
     /// @param rhs - second argument is ignored
     /// @return decremented object
     friend BitPosition& operator--(BitPosition& lhs, int /*rhs*/){
        operator--(lhs);
        return lhs;
     }

     /// @brief This method implements the prefix decrement operator of Bitposition object 
     /// @param lhs - object to be decremented
     /// @return decremented object
     friend BitPosition& operator--(BitPosition& lhs){
        lhs -= 1;
        return lhs;
     }

     // comparison operator

     /// @brief This method implements the equality comparison operator of two Bitposition objects 
     /// @param lhs - first object to be compared
     /// @param rhs - second object to be compared
     /// @return compare result
     friend bool operator==(const BitPosition& lhs, const BitPosition& rhs){
        return std::tie(lhs.bitPos,lhs.bytePos) == std::tie(rhs.bitPos,rhs.bytePos);
     }

     /// @brief This method implements the unequality comparison operator of two Bitposition objects 
     /// @param lhs - first object to be compared
     /// @param rhs - second object to be compared
     /// @return compare result
     friend bool operator!=(const BitPosition& lhs, const BitPosition& rhs){
        return !operator==(lhs,rhs);
     }

     /// @brief This method implements the greather than operator of two Bitposition objects 
     /// @param lhs - first object to be compared
     /// @param rhs - second object to be compared
     /// @return compare result
     friend bool operator>(const BitPosition& lhs, const BitPosition& rhs){
        return lhs.bytePos > rhs.bytePos || (lhs.bytePos == rhs.bytePos && lhs.bitPos > rhs.bitPos);
     }

     /// @brief This method implements the less than operator of two Bitposition objects 
     /// @param lhs - first object to be compared
     /// @param rhs - second object to be compared
     /// @return compare result
     friend bool operator<(const BitPosition& lhs, const BitPosition& rhs){
        return lhs.bytePos < rhs.bytePos || (lhs.bytePos == rhs.bytePos && lhs.bitPos < rhs.bitPos);
     }

     /// @brief This method implements the less than equals operator of two Bitposition objects 
     /// @param lhs - first object to be compared
     /// @param rhs - second object to be compared
     /// @return compare result
     friend bool operator<=(const BitPosition& lhs, const BitPosition& rhs){
        return (lhs < rhs || lhs == rhs);
     }

 private:
     uint8_t bitPos;
     uint32_t bytePos;

};

constexpr BitPosition bitPositionZero(0,0);
constexpr BitPosition bitPositionMax(UINT32_MAX,(UINT8_WIDTH -1));
}

#endif