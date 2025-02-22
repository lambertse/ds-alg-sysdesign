#include "countmin_sketch/countmin_sketch.h"
#include <chrono>
#include <gtest/gtest.h>
#include <string>

using namespace datastructure;

TEST(CountMinSketchTest, test) {
  CountMinSketch<int> sketch(0.001, 0.999);
  int range = 1000;
  for (int i = 0; i < range; i++) {
    sketch.update(i, i);
  }
  int failed = 0;
  for (int i = 0; i < range; i++) {
    if (i != sketch.estimate(i)) {
      failed++;
    }
  }
  std::cout << "Failed: " << failed << std::endl;
  EXPECT_LE((double)failed / range, 0.01);
}

// Test with string key
TEST(CountMinSketchTest, testString) {
  CountMinSketch<std::string> sketch(0.001, 0.999);
  int range = 1000;
  for (int i = 0; i < range; i++) {
    sketch.update(std::to_string(i), i);
  }
  int failed = 0;
  for (int i = 0; i < range; i++) {
    if (i != sketch.estimate(std::to_string(i))) {
      failed++;
    }
  }
  std::cout << "Failed: " << failed << std::endl;
  EXPECT_LE((double)failed / range, 0.01);
}
// Test to compare time between CountMinSketch and std::multiset
TEST(CountMinSketchTest, compareTime) {
  CountMinSketch<int> sketch(0.00001, 0.999);
  std::multiset<int> multiset;
  int range = 10000;

  auto start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < range; i++) {
    sketch.update(i, i);
  }
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> sketch_insert_time = end - start;

  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < range; i++) {
    for (int j = 0; j < i; j++) {
      multiset.insert(i);
    }
  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> multiset_insert_time = end - start;

  int failedCMS = 0;
  int failedMultiset = 0;
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < range; i++) {
    if (sketch.estimate(i) != i) {
      failedCMS++;
    }
  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> sketch_count_time = end - start;

  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < range; i++) {
    if (multiset.count(i) != i) {
      failedMultiset++;
    }
  }
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> multiset_count_time = end - start;

  std::cout << "CountMinSketch insert time: " << sketch_insert_time.count()
            << " seconds" << std::endl;
  std::cout << "std::multiset insert time: " << multiset_insert_time.count()
            << " seconds" << std::endl;
  std::cout << "CountMinSketch count time: " << sketch_count_time.count()
            << " seconds" << std::endl;
  std::cout << "std::multiset count time: " << multiset_count_time.count()
            << " seconds" << std::endl;
  EXPECT_LE((double)failedCMS / range, 0.01);
  EXPECT_LE((double)failedMultiset / range, 0.01);
  std::cout << "Failed CMS: " << failedCMS << std::endl;
  std::cout << "Failed Multiset: " << failedMultiset << std::endl;
}
int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
