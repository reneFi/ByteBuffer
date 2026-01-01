#ifndef BITPOSITION_H
#define BITPOSITION_H

#pragma once

#include <cstdint>
#include <cstddef>
#include <tuple>

namespace ByteBuffer  {

constexpr uint16_t maxBitPos = 256;
constexpr uint16_t bitPerByte = 8;

/// @brief Represents a position within a byte buffer at bit resolution.
/// @details Tracks both the byte index and the bit index (0..7) within that byte.
/// Provides arithmetic and comparison operators for convenient manipulation.
class BitPosition
{
 public:
     /// @brief Default-construct a zero bit position (byte 0, bit 0).
     constexpr BitPosition():BitPosition(0,0) {}

     /// @brief Construct from an absolute bit index; converts to (byte,bit).
     constexpr BitPosition(uint32_t bitPos):BitPosition(bitPos / bitPerByte,bitPos % bitPerByte) {}

     /// @brief Construct from a byte index and a bit index.
     constexpr BitPosition(uint32_t bytePos, uint8_t bitPos):bitPos(bitPos),bytePos(bytePos) {}
     
     /// @brief Get the bit index within the byte (0..7).
     constexpr uint8_t getBitPos() const {return bitPos;}

     /// @brief Get the byte index containing the bit.
     constexpr uint32_t getBytePos() const {return bytePos;}

     // addition assignment operators
     
     /// @brief Add another BitPosition to this one (wraps bits into bytes).
     /// @param lhs The left-hand-side being modified.
     /// @param rhs The right-hand-side added to `lhs`.
     /// @return Reference to modified `lhs`.
     friend BitPosition& operator+=(BitPosition& lhs, const BitPosition& rhs) {
        lhs.bitPos += rhs.bitPos;

        // remove wrap around
        lhs.bytePos += lhs.bitPos / bitPerByte;
        lhs.bitPos %= bitPerByte;

        lhs.bytePos += rhs.bytePos;
        return lhs;
     }
     
     /// @brief Add a number of bits to this position.
     /// @param lhs The left-hand-side being modified.
     /// @param rhs The number of bits to add.
     /// @return Reference to modified `lhs`.
     friend BitPosition& operator+=(BitPosition& lhs, const uint32_t rhs){

        lhs.bitPos += rhs % bitPerByte;

        // remove wrap around
        lhs.bytePos += lhs.bitPos / bitPerByte;
        lhs.bitPos %= bitPerByte;

        lhs.bytePos += rhs/bitPerByte;    
        return lhs;
     } 
      

     // addition operators 

     /// @brief Return the sum of two bit positions.
     friend BitPosition operator+(const BitPosition &lhs, const BitPosition &rhs){
        BitPosition bp(lhs);
        bp += rhs;

        return bp;
     }

     /// @brief Return the sum of a bit position and a bit offset.
     friend BitPosition operator+(const BitPosition &lhs, int rhs) {
        BitPosition bp(lhs);
        bp += rhs;

        return bp;
     }
     

     // increment operators

     /// @brief Postfix increment.
     friend BitPosition& operator++(BitPosition& lhs, int /*rhs*/) {
        operator++(lhs);
        return lhs;
     }

     /// @brief Prefix increment.
     friend BitPosition& operator++(BitPosition& lhs) {
        lhs += 1;
        return lhs;
     }


     // subtraction assignment operators
     
     /// @brief Subtract another BitPosition from this one (handles borrow from bytes).
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

     /// @brief Return the difference of two bit positions.
     friend BitPosition operator-(const BitPosition &lhs, const BitPosition &rhs) {
        BitPosition bp(lhs);
        bp -= rhs;

        return bp;
     }

     // decrement operators

     /// @brief Postfix decrement.
     friend BitPosition& operator--(BitPosition& lhs, int /*rhs*/){
        operator--(lhs);
        return lhs;
     }

     /// @brief Prefix decrement.
     friend BitPosition& operator--(BitPosition& lhs){
        lhs -= 1;
        return lhs;
     }

     // comparison operator

     /// @brief Equality comparison.
     friend bool operator==(const BitPosition& lhs, const BitPosition& rhs){
        return std::tie(lhs.bitPos,lhs.bytePos) == std::tie(rhs.bitPos,rhs.bytePos);
     }

     /// @brief Inequality comparison.
     friend bool operator!=(const BitPosition& lhs, const BitPosition& rhs){
        return !operator==(lhs,rhs);
     }

     /// @brief Greater-than comparison.
     friend bool operator>(const BitPosition& lhs, const BitPosition& rhs){
        return lhs.bytePos > rhs.bytePos || (lhs.bytePos == rhs.bytePos && lhs.bitPos > rhs.bitPos);
     }

     /// @brief Less-than comparison.
     friend bool operator<(const BitPosition& lhs, const BitPosition& rhs){
        return lhs.bytePos < rhs.bytePos || (lhs.bytePos == rhs.bytePos && lhs.bitPos < rhs.bitPos);
     }

     /// @brief Less-than-or-equal comparison.
     friend bool operator<=(const BitPosition& lhs, const BitPosition& rhs){
        return (lhs < rhs || lhs == rhs);
     }

     /// @brief Stream output in the form "byte.bit" (e.g. "3.5").
     friend std::ostream& operator<<(std::ostream& os, const BitPosition& obj) {
        return os << (int)(obj.bytePos) << "." << (int)(obj.bitPos);
     }
 private:
     uint8_t bitPos;
     uint32_t bytePos;

};

constexpr BitPosition bitPositionZero(0,0);
constexpr BitPosition bitPositionMax(UINT32_MAX,(UINT8_WIDTH -1));
}

#endif