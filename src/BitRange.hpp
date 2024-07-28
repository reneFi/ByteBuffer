#ifndef BITRANGE_H
#define BITRANGE_H

#pragma once

#include <cstdint>
#include <cstddef>
#include <tuple>

#include "BitPosition.h"

namespace ByteBuffer  {

class BitRange
{
public:
    constexpr BitRange():BitRange({0,0},{0,0}) {};
    constexpr BitRange(BitPosition bitPosStart, BitPosition bitPosEnd):start(bitPosStart),end(bitPosEnd) {};
    BitRange(BitPosition bitPosStart, uint16_t bitCount):start(bitPosStart),end(bitPosStart + bitCount - 1) {};
   
    BitPosition getStart() {return start;};
    BitPosition getEnd() {return end;};

    friend std::ostream& operator<<(std::ostream& os, const BitRange& obj) {
        return os << obj.start << " .. " << obj.end;
    }
private:
    BitPosition start;
    BitPosition end;
};

};
#endif