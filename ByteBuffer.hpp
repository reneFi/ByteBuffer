#pragma once

#include <array>

#include "BitPosition.h"

namespace ByteBuffer  {

#define ROUND_UP_BYTE(_X) ((_X == 0)? 0 : (_X / 8) + ( ( _X % 8 == 0 ) ? 0 : 1)  )

template <size_t Bytes>
    class ByteBuffer {
        public:
            ByteBuffer() {buf.fill(0);};
            ~ByteBuffer() = default;
        
        template <typename N>
        void set(const BitPosition pos,N value,const uint8_t bitCount) {
            BitPosition _pos = pos;
            BitPosition max = pos;
            if (bitCount <= sizeof(N) * 8)
            {
                if (_pos + bitCount < BitPosition(Bytes,0))
                {
                    max = _pos + bitCount;
                }else
                {
                    max = BitPosition(Bytes,0);
                }
            }
            
            uint8_t idx = 0;
            while ( _pos < max )
            {
                uint8_t insert = (value >> idx);
                insert &= 1;
                if (insert == 1)
                {
                    set(_pos);
                }else 
                {
                    reset(_pos);
                }
                _pos++;
                idx++;
            }
        }
        
        uint32_t get(const BitPosition pos,const uint8_t bitCount) {
            BitPosition _pos = pos;
            BitPosition _end = pos + bitCount;
            uint32_t ret = 0;
            uint8_t idx = 0;
            while(_pos < _end)
            {
                ret |= (get(_pos) << idx);
                idx++;
                _pos++;
            }
            return ret;
        };
        
        void fill(uint8_t val) {buf.fill(val);};
    
        constexpr size_t size() {return buf.size();};
        uint8_t* getData() {return buf.data();};
    private:
        
        void set(BitPosition pos) {
            buf.at(pos.getBytePos()) |= (1 << pos.getBitPos());
        }; 
        void reset(BitPosition pos) {
            buf.at(pos.getBytePos()) &= ~(1 << pos.getBitPos());
        };

        uint8_t get(BitPosition pos) {
            
            uint8_t cont = buf.at(pos.getBytePos());
            uint8_t cont_without = (cont >> pos.getBitPos());
            return cont_without & 1;
        } 
        std::array<uint8_t, Bytes> buf;
    };
}