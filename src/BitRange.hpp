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
   
    BitPosition getStart() {return start;};
    BitPosition getEnd() {return end;};
private:
    BitPosition start;
    BitPosition end;
};

};
#endif