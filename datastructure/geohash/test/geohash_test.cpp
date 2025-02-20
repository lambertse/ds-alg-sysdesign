
#include "geohash/geohash.h"
#include <gtest/gtest.h>

// Test case for the GeoHashCalculator::encode function
TEST(GeoHashCalculatorTest, Encode) {
  // Known coordinates and their expected geohash values
  struct TestCase {
    GeoPoint point;
    GeoHash expectedHash;
  };

  std::vector<TestCase> testCases = {
      {GeoPoint(37.7749, -122.4194), "9q8yy"}, // San Francisco
      {GeoPoint(40.7128, -74.0060), "dr5re"},  // New York
      {GeoPoint(51.5074, -0.1278), "gcpvj"},   // London
      {GeoPoint(-33.8688, 151.2093), "r3gx2"}, // Sydney
      {GeoPoint(35.6895, 139.6917), "xn774"},  // Tokyo
      {GeoPoint(90, -180), "bpbpb"},           // North Pole, Western Hemisphere
      {GeoPoint(-90, 180), "pbpbp"},           // South Pole, Eastern Hemisphere
      {GeoPoint(90, 180), "zzzzz"},            // North Pole, Eastern Hemisphere
      {GeoPoint(-90, -180), "00000"}           // South Pole, Western Hemisphere
  };

  for (const auto &testCase : testCases) {
    GeoHash actualHash = GeoHashCalculator::encode(testCase.point);
    EXPECT_EQ(actualHash.substr(0, testCase.expectedHash.length()),
              testCase.expectedHash)
        << "Failed for point: (" << testCase.point.latitude << ", "
        << testCase.point.longitude << ")";
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
