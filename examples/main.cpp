
#include "ByteBuffer.hpp"

#include <iostream>

constexpr ByteBuffer::BitPosition byte0_bit0(0,0);
constexpr ByteBuffer::BitPosition byte4_bit0(4,0);
constexpr ByteBuffer::BitPosition byte5_bit0(5,0);
constexpr ByteBuffer::BitRange range_byte5_bit1_to_byte5_bit3( {5,1}, {5,3} );
constexpr ByteBuffer::BitPosition byte5_bit4(5,4);

int  main(int argc, char** /*argv[]*/) {

    if (argc == 1)
    {
        ByteBuffer::ByteBuffer<6> b;

        b.at(byte0_bit0,ByteBuffer::Byte(4)).setValue(0x7f454c46);
        b.at(byte4_bit0,ByteBuffer::Byte(1)).setValue(0x12);
        std::cout << "Bytebuffer value at " << byte4_bit0 << ":" << b.at(byte4_bit0,ByteBuffer::Byte(1)) << std::endl;
        b.at(byte5_bit0).set();
        b.at(range_byte5_bit1_to_byte5_bit3).setValue(2);
        b.at(byte5_bit4).clear();
        
        std::cout << "Bytebuffer has value 0x7f454c46 at " << byte0_bit0 << " " << (b.at(byte0_bit0,ByteBuffer::Byte(4)).hasValue(0x7F454c46)?"yes":"no") << std::endl;
        std::cout << "Bytebuffer has value 0x12 at Byte " << byte4_bit0 << " "  << (b.at(byte4_bit0,ByteBuffer::Byte(1)).hasValue(0x12)?"yes":"no") << std::endl;
        std::cout << "Bytebuffer Byte 5 Bit 0 is Set " << (b.at(byte5_bit0).isSet()?"yes":"no") << std::endl;
        std::cout << "Bytebuffer has value 2 at Byte 5 Bit 3 " << (b.at(range_byte5_bit1_to_byte5_bit3).hasValue(2)?"yes":"no") << std::endl;
        std::cout << "Bytebuffer Byte 5 Bit 4 is Cleared " << (b.at(byte5_bit4).isCleared()?"yes":"no") << std::endl;
        
        std::cout << "Bytebuffer value at " << byte0_bit0 << ":" << b.at(byte0_bit0,ByteBuffer::Byte(4)) << std::endl;
        std::cout << "Bytebuffer value at " << byte4_bit0 << ":" << b.at(byte4_bit0,ByteBuffer::Byte(1)) << std::endl;
        std::cout << "Bytebuffer value at " << range_byte5_bit1_to_byte5_bit3 << ":" << b.at(range_byte5_bit1_to_byte5_bit3) << std::endl;
    }
    return 0;
}