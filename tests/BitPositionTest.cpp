#include <gtest/gtest.h>

#include "BitPosition.h"

/***************************************************************************************************************
 * Constructors
 ***************************************************************************************************************/

/// @brief test if default construction is working
/// Default construction of Bitposition object sets bit and byte position to zero  
TEST(BitPosition, DefaultConstructionOfObject_ShouldReturnBitPositionZero) {
  ByteBuffer::BitPosition bp;
  
  EXPECT_EQ(bp.getBitPos(), 0);
  EXPECT_EQ(bp.getBytePos(), 0);
}

/// @brief test if construction with byte position and bit position is working
/// Construction of Bitposition object sets bit and byte position according to parameter in constructor 
TEST(BitPosition, ConstructionOfObjectWithTwoParameters_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(356,1);
  
  EXPECT_EQ(bp.getBitPos(), 1);
  EXPECT_EQ(bp.getBytePos(), 356);
}

/// @brief test if construction with bit position is working
/// Construction of Bitposition object sets bit and byte position according to parameter in constructor 
TEST(BitPosition, ConstructionOfObjectWithOneParameter_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(356 * 8 + 2);
  
  EXPECT_EQ(bp.getBitPos(), 2);
  EXPECT_EQ(bp.getBytePos(), 356);
}

constexpr ByteBuffer::BitPosition bp_c(123,5);

/// @brief test if copy construction with bit position is working
/// Construction of Bitposition object sets bit and byte position according to parameter in constructor 
TEST(BitPosition, CopyConstructionOfObject_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(bp_c);
  
  EXPECT_EQ(bp.getBitPos(), 5);
  EXPECT_EQ(bp.getBytePos(), 123);
}

/***************************************************************************************************************
 * Addition assignement operator
 ***************************************************************************************************************/

/// @brief test if Addition assignement without bit overrun of two objects is working
/// Addition assignement of two Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionAssignementOfTwoObjectWithoutBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp += bp_c;
  
  EXPECT_EQ(bp.getBitPos(), 6);
  EXPECT_EQ(bp.getBytePos(), 125);
}

/// @brief test if Addition assignement without bit overrun of one object and a bit offset is working
/// Addition assgnement of bit offset to existing Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionAssignementOfObjectAndBitOffsetWithoutBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp += 3;
  
  EXPECT_EQ(bp.getBitPos(), 4);
  EXPECT_EQ(bp.getBytePos(), 2);
}

/// @brief test if Addition assignement with bit overrun of two objects is working
/// Addition assignement of two Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionAssignementOfTwoObjectWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,7);
  
  bp += bp_c;
  
  EXPECT_EQ(bp.getBitPos(), 4);
  EXPECT_EQ(bp.getBytePos(), 126);
}

/// @brief test if Addition assignement with bit overrun of one object and a bit offset is working
/// Addition assignement of bit offset to existing Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionAssignementOfObjectAndBitOffsetWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp += 33;
  
  EXPECT_EQ(bp.getBitPos(), 2);
  EXPECT_EQ(bp.getBytePos(), 6);
}

/***************************************************************************************************************
 * Assignement operator
 ***************************************************************************************************************/

/// @brief test if Assignement operator of two objects is working
/// Assignement of two Bitposition object sets bit and byte position to assigned value 
TEST(BitPosition, AssignementOfSecondObject_ShouldReturnBitPositionOfSecondObject) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp = bp_c;
  
  EXPECT_EQ(bp.getBitPos(), 5);
  EXPECT_EQ(bp.getBytePos(), 123);
}

/***************************************************************************************************************
 * Addition operator
 ***************************************************************************************************************/

/// @brief test if Addition without bit overrun of two objects is working
/// Addition of two Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionOfTwoObjectWithoutBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  auto bp2 = bp + bp_c;
  
  EXPECT_EQ(bp.getBitPos(),1);
  EXPECT_EQ(bp.getBytePos(), 2);
  EXPECT_EQ(bp2.getBitPos(), 6);
  EXPECT_EQ(bp2.getBytePos(), 125);
}

/// @brief test if Addition without bit overrun of one object and a bit offset is working
/// Addition of bit offset to existing Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionOfObjectAndBitOffsetWithoutBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp = bp + 3;
  
  EXPECT_EQ(bp.getBitPos(), 4);
  EXPECT_EQ(bp.getBytePos(), 2);
}

/// @brief test if Addition with bit overrun of two objects is working
/// Addition of two Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionOfTwoObjectWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,7);
  
  ByteBuffer::BitPosition bp2 = bp + bp_c;
  
  EXPECT_EQ(bp.getBitPos(),7);
  EXPECT_EQ(bp.getBytePos(), 2);
  EXPECT_EQ(bp2.getBitPos(), 4);
  EXPECT_EQ(bp2.getBytePos(), 126);
}

/// @brief test if Addition with bit overrun of one object and a bit offset is working
/// Addition  of bit offset to existing Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionOfObjectAndBitOffsetWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp = bp + 33;
  
  EXPECT_EQ(bp.getBitPos(), 2);
  EXPECT_EQ(bp.getBytePos(), 6);
}

/// @brief test if Addition of exactly one byte to bitposition object works
/// Addition  of one byte to existing Bitposition object sets bit and byte position according to result in operation 
TEST(BitPosition, AddittionOfOneByteToObjectWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(0,0);
  
  bp = bp + 8;
  
  EXPECT_EQ(bp.getBitPos(), 0);
  EXPECT_EQ(bp.getBytePos(), 1);
}
/***************************************************************************************************************
 * Inkrement operator
 ***************************************************************************************************************/

/// @brief test if Inkrement operator without bit overrun  is working
/// Inkrement of Bitposition object inkrements bit by 1 
TEST(BitPosition, PrefixInkrementOfObjectWithoutBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp++;

  EXPECT_EQ(bp.getBitPos(),2);
  EXPECT_EQ(bp.getBytePos(), 2);
  
}

// @brief test if Inkrement operator with bit overrun  is working
/// Inkrement of Bitposition object inkrements bit by 1 
TEST(BitPosition, PrefixInkrementOfObjectWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,7);
  
  bp++;

  EXPECT_EQ(bp.getBitPos(),0);
  EXPECT_EQ(bp.getBytePos(), 3);
  
}

/// @brief test if Inkrement operator without bit overrun  is working
/// Inkrement of Bitposition object inkrements bit by 1 
TEST(BitPosition, PostfixInkrementOfObjectWithoutBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  ++bp;

  EXPECT_EQ(bp.getBitPos(),2);
  EXPECT_EQ(bp.getBytePos(), 2);
  
}

// @brief test if Inkrement operator with bit overrun  is working
/// Inkrement of Bitposition object inkrements bit by 1 
TEST(BitPosition, PostfixInkrementOfObjectWithBitOverrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,7);
  
  ++bp;

  EXPECT_EQ(bp.getBitPos(),0);
  EXPECT_EQ(bp.getBytePos(), 3);
  
}


/***************************************************************************************************************
 * Dekrement operator
 ***************************************************************************************************************/

/// @brief test if Dekrement operator without bit underrun  is working
/// Dekrement of Bitposition object dekrements bit by 1 
TEST(BitPosition, PrefixDekrementOfObjectWithoutBitUnderrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  bp--;

  EXPECT_EQ(bp.getBitPos(),0);
  EXPECT_EQ(bp.getBytePos(), 2);
  
}

// @brief test if Dekrement operator with bit underrun  is working
/// Dekrement of Bitposition object dekrements bit by 1 
TEST(BitPosition, PrefixDekrementOfObjectWithBitUnderrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,0);
  
  bp--;

  EXPECT_EQ(bp.getBitPos(),7);
  EXPECT_EQ(bp.getBytePos(), 1);
  
}

/// @brief test if Dekrement operator without bit underrun  is working
/// Dekrement of Bitposition object dekrements bit by 1 
TEST(BitPosition, PostfixDekrementOfObjectWithoutBitUnderrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,1);
  
  --bp;

  EXPECT_EQ(bp.getBitPos(),0);
  EXPECT_EQ(bp.getBytePos(), 2);
  
}

// @brief test if Dekrement operator with bit overrun  is working
/// Dekrement of Bitposition object dekrements bit by 1 
TEST(BitPosition, PostfixDekrementOfObjectWithBitUnderrun_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(2,0);
  
  --bp;

  EXPECT_EQ(bp.getBitPos(),7);
  EXPECT_EQ(bp.getBytePos(), 1);
  
}

/***************************************************************************************************************
 * comparison operators
 ***************************************************************************************************************/

/// @brief test if Equality of two BitPositions is working
/// content comapre two objects of equality 
TEST(BitPosition, EqualsCompareOfEqualObjects_ShouldReturnTrue) {
  ByteBuffer::BitPosition bp2(2,1);
  ByteBuffer::BitPosition bp1(2,1);
  ByteBuffer::BitPosition bp3(2,2);
  ByteBuffer::BitPosition bp4(1,1);

  EXPECT_TRUE(bp1 == bp2);
  EXPECT_FALSE(bp1 == bp3);
  EXPECT_FALSE(bp1 == bp4);
}

/// @brief test if Unequality of two BitPositions is working
/// content comapre two objects of unequality 
TEST(BitPosition, UnequalsCompareOfEqualObjects_ShouldReturnTrue) {
  ByteBuffer::BitPosition bp2(2,1);
  ByteBuffer::BitPosition bp1(2,1);
  ByteBuffer::BitPosition bp3(2,2);
  ByteBuffer::BitPosition bp4(1,1);

  EXPECT_FALSE(bp1 != bp2);
  EXPECT_TRUE(bp1 != bp3);
  EXPECT_TRUE(bp1 != bp4);
}

/// @brief test if greater than operator is working
/// content compare two objects of greater than relation 
TEST(BitPosition, GreaterThanCompareOfEqualObjects_ShouldReturnTrue) {
  ByteBuffer::BitPosition bp1(2,2);
  ByteBuffer::BitPosition bp2(2,1);
  ByteBuffer::BitPosition bp3(2,0);
  ByteBuffer::BitPosition bp4(1,6);
    
  EXPECT_TRUE(bp1 > bp2);
  EXPECT_FALSE(bp1 > bp1);
  EXPECT_TRUE(bp1 > bp3);
  EXPECT_TRUE(bp1 > bp4);
  EXPECT_TRUE(ByteBuffer::bitPositionMax > ByteBuffer::bitPositionZero);
}

/// @brief test if less than operator is working
/// content compare two objects of less than relation 
TEST(BitPosition, LessThanCompareOfEqualObjects_ShouldReturnTrue) {
  ByteBuffer::BitPosition bp1(2,2);
  ByteBuffer::BitPosition bp2(2,1);
  ByteBuffer::BitPosition bp3(2,0);
  ByteBuffer::BitPosition bp4(1,6);
  
  EXPECT_TRUE(bp2 < bp1);
  EXPECT_FALSE(bp1 < bp1);
  EXPECT_TRUE(bp3 < bp1);
  EXPECT_TRUE(bp4 < bp1);
  EXPECT_TRUE(ByteBuffer::bitPositionZero < ByteBuffer::bitPositionMax);
}

/// @brief test if less than equals operator is working
/// compare content of two objects using less than equals relation 
TEST(BitPosition, LessThanEqualsCompareOfEqualObjects_ShouldReturnTrue) {
  ByteBuffer::BitPosition bp1(2,2);
  ByteBuffer::BitPosition bp2(2,1);
  ByteBuffer::BitPosition bp3(2,2);
  ByteBuffer::BitPosition bp4(2,3);
  
  EXPECT_TRUE(bp2 <= bp1);
  EXPECT_TRUE(bp1 <= bp1);
  EXPECT_TRUE(bp3 <= bp1);
  EXPECT_FALSE(bp4 <= bp1);
  EXPECT_TRUE(ByteBuffer::bitPositionZero < ByteBuffer::bitPositionMax);
}

/**************************************************************************************************
 * Wrap around in operation
 **************************************************************************************************/
// @brief test if Dekrement of Pos 0 is working 
/// Dekrement of Bitposition Zero  
TEST(BitPosition, DekrementBitPositionOfZero_ShouldReturnBitPositionMax) {
  ByteBuffer::BitPosition bp(0,0);
  
  --bp;

  EXPECT_TRUE(bp == ByteBuffer::bitPositionMax);
  
}

// @brief test if subtract larger BitPosition from smaller is working 
/// Subtract larger BitPosition from smaller one
TEST(BitPosition, SubktractLargerBitPositionFromSmaller_ShouldReturnCorrectBitPosition) {
  ByteBuffer::BitPosition bp(6,124);
  
  bp -= bp_c;

  EXPECT_EQ(bp.getBitPos(),7);
  EXPECT_EQ(bp.getBytePos(), 4294967161);
  
}

// @brief test if Inkrement of BitPosition Max is working 
/// Inkrement of Bitposition Max  
TEST(BitPosition, InkrementBitPositionMax_ShouldReturnBitPositionZero) {
  ByteBuffer::BitPosition bp(ByteBuffer::bitPositionMax);
  
  ++bp;

  EXPECT_TRUE(bp == ByteBuffer::bitPositionZero);
  
}