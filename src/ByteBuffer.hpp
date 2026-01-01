#pragma once

#include <array>
#include <ostream>
#include <functional>

#include "BitRange.hpp"

namespace ByteBuffer  {

/// @brief Represents a count in bytes expressed as number of bits.
/// @details Construct by passing a byte count; the member `bits` stores the equivalent
/// number of bits (bytes * 8).
struct Byte {
    explicit Byte(uint8_t count) : bits(static_cast<uint16_t>(count * 8)) {}
    uint16_t bits;
};
/// @brief Helper base class that stores setter/getter callables for bit access.
/// @details `setter` receives a 32-bit value to write; `getter` returns the current 32-bit value.
/// This class is intended for internal use by `Bit` and `Bits` proxies.
class BitAccess {
    public:
    BitAccess(std::function<void(uint32_t)> s, std::function<uint32_t(void)> g):setter(s),getter(g) {}
   
    protected:
    std::function<void(uint32_t)> setter;
    std::function<uint32_t(void)> getter;
};

/// @brief Proxy for operating on a multi-bit field inside a `ByteBuffer`.
/// @details Use `hasValue` to compare the current value and `setValue` to write a new value.
class Bits: public BitAccess {
    public:
    Bits(std::function<void(uint32_t)> s, std::function<uint32_t(void)> g):BitAccess(s,g) {}
    bool hasValue(uint32_t v) const { return (getter() == v); }
    void setValue(uint32_t v) { setter(v); }
    friend std::ostream& operator<<(std::ostream& os, const Bits& obj);
};
inline std::ostream& operator<<(std::ostream& os, const Bits& obj)
{
    return os << obj.getter();
}

/// @brief Proxy for a single bit inside a `ByteBuffer`.
/// @details Provides convenience methods to query and modify the single bit.
class Bit: public BitAccess {
    public:
    Bit(std::function<void(uint32_t)> s, std::function<uint32_t(void)> g):BitAccess(s,g) {}
    bool isSet() const { return (getter() & 0x1) == 0x1; }
    bool isCleared() const { return (getter() & 0x1) == 0x0; }

    void set()   { setter(1); }
    void clear() { setter(0); }

    friend std::ostream& operator<<(std::ostream& os, const Bit& obj);
};
inline std::ostream& operator<<(std::ostream& os, const Bit& obj)
{
    return os << (obj.getter() ? "set" : "cleared");
}

/// @brief Fixed-size byte buffer with bit-level access and helpers.
/// @tparam Bytes Number of bytes stored in the buffer.
template <size_t Bytes>
    class ByteBuffer {
        public:
            /// @brief Construct an empty buffer and zero-initialize its contents.
            ByteBuffer() { buf.fill(0); }
            
            ~ByteBuffer() = default;
        
            /// @brief Insert up to `bitCount` bits of `value` into the buffer starting at bit position `pos`.
            /// @details Bits are taken from `value` starting at its least-significant bit (LSB) and written
            /// sequentially into the buffer. If `bitCount` exceeds the remaining space in the buffer or the width
            /// of `value`, the extra bits are truncated.
            /// @tparam N Integral input type (e.g., uint8_t, uint32_t).
            /// @param pos Bit position within target buffer where insertion begins.
            /// @param value Value supplying bits to be inserted.
            /// @param bitCount Number of bits to insert (from LSB upwards).
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

            /// @brief Insert bits of `value` into the buffer over the specified `range`.
            /// @details The least-significant bits of `value` map to the start of `range`. If `range` extends beyond
            /// the buffer or `value` has fewer bits than `range`, remaining positions are truncated.
            /// @tparam N Integral input type.
            /// @param range Bit range within the buffer.
            /// @param value Value supplying bits to be inserted.
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

        /// @brief Set or clear a single bit at `pos` according to the least-significant bit of `value`.
        /// @tparam N Integral input type.
        /// @param pos Bit position within buffer.
        /// @param value If LSB is 1 the bit is set; otherwise it is cleared.
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
        
        /// @brief Retrieve up to `bitCount` bits starting at `pos`, packed into the return value from LSB upwards.
        /// @tparam N Integral return type.
        /// @param pos Starting bit position within buffer.
        /// @param bitCount Number of bits to retrieve.
        /// @return Value containing the requested bits in its lower bits; higher bits are zero.
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

        /// @brief Retrieve bits from `range` and return them packed in the lower bits of the result.
        /// @tparam N Integral return type.
        /// @param range Bit range within buffer.
        /// @return Value containing bits from `range` in its lower bits.
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
        
        /// @brief Return a `Bits` proxy bound to `range` (allows read/write of the whole range as an integer).
        Bits at(const BitRange range) {
            auto setter = [range,this](uint32_t value) { set<uint32_t>(range,value);};
            std::function<uint32_t(void)> getter = [range,this]() {return get<uint32_t>(range);};
            Bits ret( setter , getter );
            return ret;
        }

        /// @brief Return a `Bits` proxy that represents `b` bytes starting at bit position `pos`.
        Bits at(const BitPosition pos, const Byte b) {
            return at(BitRange(pos,b.bits));
        }

        /// @brief Return a `Bit` proxy bound to the single bit at `pos`.
        Bit at(const BitPosition pos) {
            auto setter = [pos,this](uint32_t value) { set<uint32_t>(pos,value);};
            std::function<uint32_t(void)> getter = [pos,this]() {return get<uint32_t>(pos);};
            Bit ret( setter , getter );
            return ret;
        }

        /// @brief Retrieve a single bit at `pos` and return it in the least-significant bit of the result.
        /// @tparam N Integral return type.
        /// @param pos Bit position within buffer.
        /// @return 0 or 1 in the LSB of the return value.
        template <typename N>
        N get(BitPosition pos) {
            
            N cont = buf.at(pos.getBytePos());
            N cont_without = (cont >> pos.getBitPos());
            return cont_without & 1;
        } 

        /// @brief Fill the internal buffer with the byte pattern `val`.
        /// @param val Byte value used to fill every byte of the buffer.
        void fill(uint8_t val) {buf.fill(val);}
    
        /// @brief Return the number of bytes in the underlying buffer.
        /// @return size of the underlying array in bytes.
        constexpr size_t size() {return buf.size();}

        /// @brief Return a pointer to the internal data array.
        /// @note The caller should verify the number of bytes with `size()`.
        /// @return Pointer to the buffer's data.
        const uint8_t* getData() {return buf.data();}
    private:
        
        /// @brief Set the single bit at `pos`.
        /// @param pos Bit position to set.
        void set(BitPosition pos) {
            buf.at(pos.getBytePos()) |= static_cast<uint8_t>(1 << pos.getBitPos());
        }
        /// @brief Clear the single bit at `pos`.
        /// @param pos Bit position to clear.
        void reset(BitPosition pos) {
            buf.at(pos.getBytePos()) &= static_cast<uint8_t>(~(1 << pos.getBitPos()));
        }

        /// @brief Compute the maximum bit position the operation can reach.
        /// @tparam N Integral type used for value width.
        /// @param pos Starting position.
        /// @param bitCount Number of bits intended to be used.
        /// @return The last legal bit position (exclusive) given buffer size and value width.
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