#ifndef BITRANGE_H
#define BITRANGE_H

#pragma once

#include <cstdint>
#include <cstddef>
#include <tuple>

#include "BitPosition.h"

namespace ByteBuffer  {

/// @brief Represents a contiguous inclusive range of bits inside a `ByteBuffer`.
/// @details Construct using explicit start/end positions or by specifying a start
/// and a count of bits. The `start` and `end` positions are inclusive.
class BitRange
{
public:
    /// @brief Default-construct an empty range at bit position 0.
    constexpr BitRange() : BitRange(BitPosition(0,0), BitPosition(0,0)) {}

    /// @brief Construct a range from inclusive start and end positions.
    constexpr BitRange(BitPosition bitPosStart, BitPosition bitPosEnd) : start(bitPosStart), end(bitPosEnd) {}

    /// @brief Construct a range from a start position and a bit count.
    /// @param bitPosStart The start position of the range.
    /// @param bitCount Number of bits in the range (must be >= 1).
    BitRange(BitPosition bitPosStart, uint16_t bitCount) : start(bitPosStart), end(bitPosStart + (bitCount - 1)) {}
   
    /// @brief Return the inclusive start position of the range.
    BitPosition getStart() const { return start; }

    /// @brief Return the inclusive end position of the range.
    BitPosition getEnd() const { return end; }

    friend std::ostream& operator<<(std::ostream& os, const BitRange& obj) {
        return os << obj.start << " .. " << obj.end;
    }
private:
    BitPosition start;
    BitPosition end;
};

};
#endif