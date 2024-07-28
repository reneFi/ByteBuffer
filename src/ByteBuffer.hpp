#pragma once

#include <array>
#include <ostream>
#include <functional>

#include "BitRange.hpp"

namespace ByteBuffer  {

/// @brief make code readable
struct Byte {
    Byte(uint8_t count) {bits = count * 8;};
    uint16_t bits;
};
class BitAccess {
    public:
    BitAccess(std::function<void(uint32_t)> s, std::function<uint32_t(void)> g):setter(s),getter(g) {};
   
    protected:
    std::function<void(uint32_t)> setter;
    std::function<uint32_t(void)> getter;
};

class Bits: public BitAccess {
    public:
    Bits(std::function<void(uint32_t)> s, std::function<uint32_t(void)> g):BitAccess(s,g) {};
    bool hasValue(uint32_t v) { return (getter() == v);};
    void setValue(uint32_t v) { setter(v);};
    friend std::ostream& operator<<(std::ostream& os, const Bits& obj);
};
std::ostream& operator<<(std::ostream& os, const Bits& obj)
{
    return os << obj.getter();
}

class Bit: public BitAccess {
    public:
    Bit(std::function<void(uint32_t)> s, std::function<uint32_t(void)> g):BitAccess(s,g) {};
    bool isSet() { return (getter() & 0x1) == 0x1; };
    bool isCleared() {return (getter() & 0x1) == 0x0;};

    void set()   { setter(1); };
    void clear() { setter(0); };

    friend std::ostream& operator<<(std::ostream& os, const Bit& obj);
};
std::ostream& operator<<(std::ostream& os, const Bit& obj)
{
    return os << (obj.getter()?"set":"cleared");
}

/// @brief 
/// @tparam Bytes 
template <size_t Bytes>
    class ByteBuffer {
        public:
            /// @brief Constructor constructs a object
            /// The internal buffer is filled with 0.
            ByteBuffer() { buf.fill(0); };
            
            ~ByteBuffer() = default;
        
            /// @brief This method sets or resets bitCount bits from given value starting from position pos in buffer.
            /// This method inserts bitCount bits from value to buffer starting from position pos. If bitcount exceeds buffers bit size or 
            /// values bit size the bits outside of border are truncated.  
            /// @tparam N - integral type of input value
            /// @param pos - bit position within target buffer
            /// @param value - value to be inserted
            /// @param bitCount - count of bits from value
            template <typename N>
            void set(const BitPosition pos,N value,const uint8_t bitCount) {
            
                static_assert(std::is_integral<N>::value,"only integral types are allowed");
            
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

            /// @brief This method sets or resets a range of within the buffer.
            /// This method inserts bitCount bits from value to buffer in given range. If range exceeds buffers range or 
            /// values bit size is larger than bit buffer the rest is truncated.  
            /// @tparam N - integral type of input value
            /// @param pos - bit position within target buffer
            /// @param value - value to be inserted
            /// @param bitCount - count of bits from value
            template <typename N>
            void set(const BitRange range,N value) {
            
                static_assert(std::is_integral<N>::value,"only integral types are allowed");
                BitRange cur = range;
                BitPosition _pos = cur.getStart();
                BitPosition max =  cur.getEnd();//maxPosition<N>(pos,bitCount);      

                uint8_t idx = 0;
                while ( _pos <= max )
                {
                    uint8_t insert = static_cast<uint8_t>(value >> idx);
                    set<N>(_pos,insert);
                    _pos++;
                    idx++;
                }
            }

        /// @brief This method sets or resets one bit from given value starting from position pos in buffer.
        /// This method inserts the lsb from value to buffer starting from position pos. 
        /// @tparam N - integral type of input value
        /// @param pos - bit position within buffer
        /// @param value - value to be inserted
        template <typename N>
        void set(const BitPosition pos,const N value) {

            static_assert(std::is_integral<N>::value,"only integral types are allowed");

            if ((value & 1) == 1)
            {
                set(pos);
            }else 
            {
                reset(pos);
            }
        }
        
        /// @brief This method gets bitCount Bits from buffer starting at position pos
        /// This method returns bitCount bits from buffer starting at position pos. The returning bits are filled from bit 0 to bit bitCount-1. All other bits are 0.  
        /// @tparam N - integral type of return value
        /// @param pos - bit position within buffer
        /// @param bitCount - count of bits returned by this function
        /// @return value from buffer
        template <typename N>
        N get(const BitPosition pos,const uint8_t bitCount) {

            static_assert(std::is_integral<N>::value,"only integral types are allowed");

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

        /// @brief This method gets bit range range from buffer
        /// This method returns bits from buffer in given pos. The returning bits are filled from bit 0 to bit bitCount-1. All other bits are 0.  
        /// @tparam N - integral type of return value
        /// @param range - bit range within buffer
        /// @return value from buffer
        template <typename N>
        N get(const BitRange range) {
            
            static_assert(std::is_integral<N>::value,"only integral types are allowed");

            BitRange cur = range;
            BitPosition _pos = cur.getStart();
            BitPosition _end = cur.getEnd();//maxPosition<N>(range.start,range.end);

            N ret = 0;
            uint8_t idx = 0;
            while(_pos <= _end)
            {
                ret |= static_cast<N>(get<N>(_pos) << idx);
                idx++;
                _pos++;
            }
            return ret;
        }
        
        Bits at(const BitRange range) {
            auto setter = [range,this](uint32_t value) { set<uint32_t>(range,value);};
            std::function<uint32_t(void)> getter = [range,this]() {return get<uint32_t>(range);};
            Bits ret( setter , getter );
            return ret;
        }

        Bits at(const BitPosition pos, const Byte b) {
            return at(BitRange(pos,b.bits));
        }

        Bit at(const BitPosition pos) {
            auto setter = [pos,this](uint32_t value) { set<uint32_t>(pos,value);};
            std::function<uint32_t(void)> getter = [pos,this]() {return get<uint32_t>(pos);};
            Bit ret( setter , getter );
            return ret;
        }

        /// @brief This method gets one bit from buffer starting at position pos
        /// This method returns one bit from buffer starting at position pos. The returning bits are filled in bit 0. All other bits are 0.  
        /// @tparam N - integral type of return value
        /// @param pos - bit position within buffer
        /// @return value from buffer
        template <typename N>
        N get(BitPosition pos) {
            
            N cont = buf.at(pos.getBytePos());
            N cont_without = (cont >> pos.getBitPos());
            return cont_without & 1;
        } 

        /// @brief This method fills the buffer with value val.
        /// The bit pattern represented by val will be filled in all bytes of internal buffer
        /// @param val - bit pattern to fill in all bytes of buffer
        void fill(uint8_t val) {buf.fill(val);};
    
        /// @brief This method returns the byte size of the underlaying array returned by getData.
        /// @return size of underlaying array of data.
        constexpr size_t size() {return buf.size();};

        /// @brief This method returns a pointer to data array.
        /// The size of the array must be checked by using size() function.
        /// @return pointer to array
        const uint8_t* getData() {return buf.data();};
    private:
        
        /// @brief 
        /// @param pos 
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