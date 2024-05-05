#include "BitPosition.h"
namespace ByteBuffer {

BitPosition& operator+=(BitPosition& lhs,const BitPosition& rhs) {
    lhs.bitPos += rhs.bitPos;
    
    // remove wrap around
    lhs.bytePos += lhs.bitPos / 8;
    lhs.bitPos %= 8;

    lhs.bytePos += rhs.bytePos;
    return lhs;
} 

BitPosition& operator-=(BitPosition& lhs, const BitPosition& rhs) {
    
    lhs.bitPos -= rhs.bitPos;
    if (lhs.bitPos > 7)
    {
        uint8_t bitDiff = 256 - lhs.bitPos;
        lhs.bitPos = 8 - bitDiff % 8;
        lhs.bytePos -= 1 + bitDiff / 8;
    }
    lhs.bytePos -= rhs.bytePos;
    return lhs;
}

BitPosition operator-(const BitPosition& lhs,const BitPosition &rhs) {
    BitPosition bp(lhs);
    bp -= rhs;

    return bp;
}

BitPosition operator+(const BitPosition& lhs,const BitPosition& rhs) {
    BitPosition bp(lhs);
    bp += rhs;

    return bp;
}

BitPosition operator+(const BitPosition& lhs,int rhs) {
    BitPosition bp(lhs);
    bp += rhs;

    return bp;
}

BitPosition& operator+=(BitPosition& lhs, const size_t rhs) {
    lhs.bitPos += rhs % 8;
    
    // remove wrap around
    lhs.bytePos += lhs.bitPos / 8;
    lhs.bitPos %= 8;

    lhs.bytePos += rhs/8;    
    return lhs;
}

BitPosition& operator++(BitPosition& lhs,int /* rhs */) {
    operator++(lhs);
    return lhs;
}

BitPosition& operator++(BitPosition& lhs) {
    lhs += 1;
    return lhs;
}

BitPosition& operator--(BitPosition& lhs,int /* rhs */) {
    operator--(lhs);
    return lhs;
}

BitPosition& operator--(BitPosition& lhs) {
    lhs -= 1;
    return lhs;
}

bool operator==(const BitPosition& lhs, const BitPosition& rhs) {
    return lhs.bitPos == rhs.bitPos && lhs.bytePos == rhs.bytePos;
}

bool operator!=(const BitPosition& lhs, const BitPosition& rhs) {
    return !operator==(lhs,rhs);
}
}