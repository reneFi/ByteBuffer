#include <gtest/gtest.h>

#include "ByteBuffer.hpp"

/***************************************************************************************************************
 * Constructors
 ***************************************************************************************************************/

/// @brief test if default construction is working
/// Default construction of ByteBuffer object creates an empty array  
TEST(ByteBuffer, DefaultConstructionOfObject_ShouldReturnBitPositionZero) {
  ByteBuffer::ByteBuffer<1> bp;
  uint8_t emptyBuffer[1] = {0};

  uint8_t *data = bp.getData();
  size_t size = bp.size();
  
  EXPECT_EQ(size,1);
  EXPECT_EQ(*data,*emptyBuffer);
}

/**********************************************************************************************************
 * Set Value from Position
 **********************************************************************************************************/

/// @brief test if insert one bit at BitPosition 0 is working
/// Test if inserting one bit at BitPosition 0 in ByteBuffer object is working 
TEST(ByteBuffer, InsertOneBitAtPositionZero_ShouldReturnByteBufferWithExactlyOneChangedBit) {
  ByteBuffer::ByteBuffer<1> bp1;
  uint8_t data1 = 1;
  uint8_t compareBuffer = 0b00000001;

  bp1.set(ByteBuffer::bitPositionZero,data1,1);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,1);
  EXPECT_EQ(*dataBuf1,compareBuffer);
}

/// @brief test if inserting one bit at given BitPosition is working
/// Test if inserting one Bit at given BitPosition in ByteBuffer object is working 
TEST(ByteBuffer, InsertOneBitAtGivenPosition_ShouldReturnByteBufferWithExactlyOneChangedBit) {
  ByteBuffer::ByteBuffer<1> bp1;
  uint8_t data1 = 1;
  uint8_t compareBuffer = 0b00001000;

  bp1.set(ByteBuffer::BitPosition(0,3),data1,1);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,1);
  EXPECT_EQ(*dataBuf1,compareBuffer);
}

/// @brief test if insert one bit at BitPosition 0 is working
/// Test if inserting one bit of many at BitPosition 0 in ByteBuffer object is working 
TEST(ByteBuffer, InsertOneBitOfManyAtPositionZero_ShouldReturnByteBufferWithExactlyOneChangedBit) {
  ByteBuffer::ByteBuffer<1> bp1;
  uint8_t data1 = 0b11111111;
  uint8_t compareBuffer = 0b00000001;

  bp1.set(ByteBuffer::bitPositionZero,data1,1);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,1);
  EXPECT_EQ(*dataBuf1,compareBuffer);
}

/// @brief test if insert more than once is working
/// Test if inserting a bit pattern more than once returns last value 
TEST(ByteBuffer, InsertSecondValueAtGivenPosition_ShouldReturnByteBufferWithSecondValue) {
  ByteBuffer::ByteBuffer<1> bp1;
  uint8_t data1 = 0b11111111;
  uint8_t data2 = 0b00000101;
  uint8_t compareBuffer = 0b00000101;

  bp1.set(ByteBuffer::bitPositionZero,data1,4);
  bp1.set(ByteBuffer::bitPositionZero,data2,4);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,1);
  EXPECT_EQ(*dataBuf1,compareBuffer);
}

/// @brief test if insert over byte border is working
/// Test if inserting a bit pattern over byte border returns correct value 
TEST(ByteBuffer, InsertValueOverByteBorder_ShouldReturnByteBufferWithCompleteValue) {
  ByteBuffer::ByteBuffer<2> bp1;
  uint8_t data1 = 0b11111111;
  uint8_t data2 = 0b00000101;
  uint16_t compareBuffer = 0b0000011111110101;

  bp1.set(ByteBuffer::bitPositionZero,data2,4);
  bp1.set(ByteBuffer::BitPosition(0,4),data1,7);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,2);
  EXPECT_EQ(memcmp(dataBuf1,&compareBuffer,sizeof(compareBuffer)),0);
}

/// @brief test if insert 32 bit value in shorter buffer is working
/// Test if inserting a 32 bit pattern will truncated and insert in buffer 
TEST(ByteBuffer, Insert32BitValueInShorterBuffer_ShouldReturnByteBufferWithCompleteValue) {
  ByteBuffer::ByteBuffer<2> bp1;
  uint32_t data = 0xabcd;
  uint16_t compareBuffer = 0xabcd;

  bp1.set(ByteBuffer::bitPositionZero,data,sizeof(data) * 8);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,2);
  EXPECT_EQ(memcmp(dataBuf1,&compareBuffer,sizeof(compareBuffer)),0);
}

/// @brief test if insert 32 byte border is working
/// Test if inserting a bit pattern larger than one byte works as expected 
TEST(ByteBuffer, Insert32BitValueInEmptyBuffer_ShouldReturnByteBufferWithCompleteValue) {
  ByteBuffer::ByteBuffer<4> bp1;
  uint32_t data = 0xabcd1234;
  uint32_t compareBuffer = 0xabcd1234;

  bp1.set(ByteBuffer::bitPositionZero,data,sizeof(data) * 8);
  uint8_t *dataBuf1 = bp1.getData();
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,4);
  EXPECT_EQ(memcmp(dataBuf1,&compareBuffer,sizeof(compareBuffer)),0);
}

/**********************************************************************************************************
 * get Value from Position
 **********************************************************************************************************/

/// @brief test if getting an bit from empty buffer is working
/// Test if getting a bit works as expected 
TEST(ByteBuffer, Get1BitValueFromEmptyBuffer_ShouldReturnZero) {
  ByteBuffer::ByteBuffer<2> bp1;
 
  uint8_t data = bp1.get<uint8_t>(ByteBuffer::bitPositionZero,1);
  size_t sizeBuf1 = bp1.size();
  
  ASSERT_EQ(sizeBuf1,2);
  EXPECT_EQ(data,0);
}

/// @brief test if getting an bit from defined buffer is working
/// Test if getting a bit works as expected
TEST(ByteBuffer, Get1BitValueFromDefinedBuffer_ShouldReturnCorrectValue) {
  ByteBuffer::ByteBuffer<2> bp1;
  uint8_t dataInsert = 0b0101;
  bp1.set(ByteBuffer::bitPositionZero,dataInsert,4);

  uint8_t data = bp1.get<uint8_t>(ByteBuffer::bitPositionZero,1);
  EXPECT_EQ(data,1);
  data = bp1.get<uint8_t>(ByteBuffer::BitPosition(0,1),1);
  EXPECT_EQ(data,0);
  data = bp1.get<uint8_t>(ByteBuffer::BitPosition(0,2),1);
  EXPECT_EQ(data,1);
  data = bp1.get<uint8_t>(ByteBuffer::BitPosition(0,3),1);
  EXPECT_EQ(data,0);
}

/// @brief test if getting defined range of bits from defined buffer is working
/// Test if getting defined range of bits within a byte works as expected
TEST(ByteBuffer, GetBitRangeWithinByteFromDefinedBuffer_ShouldReturnCorrectValue) {
  ByteBuffer::ByteBuffer<2> bp1;
  uint8_t dataInsert = 0b1101;
  bp1.set(ByteBuffer::bitPositionZero,dataInsert,4);

  uint8_t data = bp1.get<uint8_t>(ByteBuffer::bitPositionZero,4);
  EXPECT_EQ(data,dataInsert);
}

/// @brief test if getting defined range of bits from defined buffer is working
/// Test if getting defined range of bits within a byte works as expected
TEST(ByteBuffer, GetBitRangeOverlapByteBorderFromDefinedBuffer_ShouldReturnCorrectValue) {
  ByteBuffer::ByteBuffer<2> bp1;
  constexpr uint8_t dataInsert = 0b11011101;
  constexpr uint8_t dataCompare = 0b0111; 
  bp1.set(ByteBuffer::bitPositionZero,dataInsert,8);
  bp1.set(ByteBuffer::BitPosition(1,0),dataInsert,8);

  uint8_t data = bp1.get<uint8_t>(ByteBuffer::BitPosition(0,6),4);
  EXPECT_EQ(data,dataCompare);
}

/// @brief test if getting defined range of bits from defined buffer is working
/// Test if getting defined range of bits within a byte works as expected
TEST(ByteBuffer, GetToLargeBitRangeFromDefinedBuffer_ShouldReturnTruncatedValue) {
  ByteBuffer::ByteBuffer<2> bp1;
  constexpr uint8_t dataInsert = 0b11011101;
  constexpr uint16_t dataCompare = 0b0000001101110111; 
  bp1.set(ByteBuffer::bitPositionZero,dataInsert,8);
  bp1.set(ByteBuffer::BitPosition(1,0),dataInsert,8);

  uint16_t data = bp1.get<uint16_t>(ByteBuffer::BitPosition(0,6),32);
  EXPECT_EQ(data,dataCompare);
}
