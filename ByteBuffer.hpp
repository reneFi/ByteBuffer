#pragma once

#include <array>

#include "BitPosition.h"

namespace ByteBuffer  {

template <size_t Bytes>
    class ByteBuffer {
        public:
            ByteBuffer() {buf.fill(0);};
            ~ByteBuffer() = default;
        
        template <typename N>
        void set(const BitPosition pos,N value,const uint8_t bitCount) {
            BitPosition _pos = pos;
            
            BitPosition max = maxPosition<N>(pos,bitCount);      

            uint8_t idx = 0;
            while ( _pos < max )
            {
                uint8_t insert = static_cast<uint8_t>(value >> idx);
                set<N>(_pos,insert);
                _pos++;
                idx++;
            }
        }

        template <typename N>
        void set(const BitPosition pos,const N insert) {
            if ((insert & 1) == 1)
            {
                set(pos);
            }else 
            {
                reset(pos);
            }
        }
        
        template <typename N>
        N get(const BitPosition pos,const uint8_t bitCount) {
            BitPosition _pos = pos;

            BitPosition _end = maxPosition<N>(pos,bitCount);

            N ret = 0;
            uint8_t idx = 0;
            while(_pos < _end)
            {
                ret |= static_cast<N>(get<N>(_pos) << idx);
                idx++;
                _pos++;
            }
            return ret;
        }
        
        template <typename N>
        N get(BitPosition pos) {
            
            N cont = buf.at(pos.getBytePos());
            N cont_without = (cont >> pos.getBitPos());
            return cont_without & 1;
        } 
        
        void fill(uint8_t val) {buf.fill(val);};
    
        constexpr size_t size() {return buf.size();};
        uint8_t* getData() {return buf.data();};
    private:
        
        void set(BitPosition pos) {
            buf.at(pos.getBytePos()) |= static_cast<uint8_t>(1 << pos.getBitPos());
        }; 
        void reset(BitPosition pos) {
            buf.at(pos.getBytePos()) &= static_cast<uint8_t>(~(1 << pos.getBitPos()));
        };

        template <typename N>
        BitPosition maxPosition(const BitPosition pos, uint8_t bitCount){
            BitPosition max = pos;
            if (bitCount <= sizeof(N) * 8)
            {
                if (pos + bitCount < BitPosition(Bytes,0))
                {
                    max = pos + bitCount;
                }else
                {
                    max = BitPosition(Bytes,0);
                }
            }else{
                max = BitPosition(Bytes,0);
            }
            return max;
        }
        std::array<uint8_t, Bytes> buf;
    };
}