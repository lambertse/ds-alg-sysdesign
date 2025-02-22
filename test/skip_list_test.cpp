
#include "skip_list/skip_list.h"
#include <gtest/gtest.h>
#include <limits.h>
using namespace datastructure;

// Custom object for testing
class CustomObject {
public:
  int key;
  CustomObject(int k) : key(k) {}
  CustomObject() { key = INT_MIN; }

  bool operator==(const CustomObject &other) const { return key == other.key; }
  bool operator<(const CustomObject &other) const { return key < other.key; }
  bool operator>(const CustomObject &other) const { return key > other.key; }
  bool operator<=(const CustomObject &other) const { return key <= other.key; }
  bool operator>=(const CustomObject &other) const { return key >= other.key; }
};

// Test fixture for SkipList
class SkipListTest : public ::testing::Test {
protected:
  SkipList<int> intSkipList;
  SkipList<CustomObject> customSkipList;
};

TEST_F(SkipListTest, IntegerInsert) {
  EXPECT_TRUE(intSkipList.insert(5));
  EXPECT_TRUE(intSkipList.insert(10));
  EXPECT_TRUE(intSkipList.insert(15));

  EXPECT_FALSE(intSkipList.insert(5));
  EXPECT_FALSE(intSkipList.insert(15));
}

// Test inserting and finding integers
TEST_F(SkipListTest, IntegerInsertAndFind) {
  EXPECT_TRUE(intSkipList.insert(5));
  EXPECT_TRUE(intSkipList.insert(10));
  EXPECT_TRUE(intSkipList.insert(15));

  EXPECT_TRUE(intSkipList.contain(5));
  EXPECT_TRUE(intSkipList.contain(10));
  EXPECT_TRUE(intSkipList.contain(15));
  EXPECT_FALSE(intSkipList.contain(20));
}

TEST_F(SkipListTest, IntegerDeleteAndFind) {
  EXPECT_TRUE(intSkipList.insert(5));
  EXPECT_TRUE(intSkipList.insert(10));
  EXPECT_TRUE(intSkipList.insert(15));

  EXPECT_TRUE(intSkipList.deleteValue(5));
  EXPECT_FALSE(intSkipList.contain(5));

  EXPECT_FALSE(intSkipList.deleteValue(10000));

  EXPECT_TRUE(intSkipList.deleteValue(10));
  EXPECT_FALSE(intSkipList.contain(10));

  EXPECT_TRUE(intSkipList.deleteValue(15));
  EXPECT_FALSE(intSkipList.contain(15));

  EXPECT_FALSE(intSkipList.deleteValue(10000));
}

// Test inserting and finding custom objects
TEST_F(SkipListTest, CustomObjectInsertAndFind) {
  CustomObject obj1(1);
  CustomObject obj2(2);
  CustomObject obj3(3);

  customSkipList.insert(obj1);
  customSkipList.insert(obj2);
  customSkipList.insert(obj3);

  EXPECT_TRUE(customSkipList.contain(obj1));
  EXPECT_TRUE(customSkipList.contain(obj2));
  EXPECT_TRUE(customSkipList.contain(obj3));
  EXPECT_FALSE(customSkipList.contain(CustomObject(4)));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
