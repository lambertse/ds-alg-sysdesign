
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

// Test case for the GeoHashCalculator::decode function
TEST(GeoHashCalculatorTest, Decode) {
  // Known geohash values and their expected coordinates
  struct TestCase {
    GeoHash hash;
    GeoPoint expectedPoint;
  };

  std::vector<TestCase> testCases = {
      {"9q8yy", GeoPoint(37.7749, -122.4194)}, // San Francisco
      {"dr5re", GeoPoint(40.7128, -74.0060)},  // New York
      {"gcpvj", GeoPoint(51.5074, -0.1278)},   // London
      {"r3gx2", GeoPoint(-33.8688, 151.2093)}, // Sydney
      {"xn774", GeoPoint(35.6895, 139.6917)},  // Tokyo
      {"bpbpb", GeoPoint(90, -180)},           // North Pole, Western Hemisphere
      {"pbpbp", GeoPoint(-90, 180)},           // South Pole, Eastern Hemisphere
      {"zzzzz", GeoPoint(90, 180)},            // North Pole, Eastern Hemisphere
      {"00000", GeoPoint(-90, -180)}           // South Pole, Western Hemisphere
  };

  for (const auto &testCase : testCases) {
    GeoPoint actualPoint = GeoHashCalculator::decode(testCase.hash);
    EXPECT_NEAR(actualPoint.latitude, testCase.expectedPoint.latitude, 0.1)
        << "Failed for hash: " << testCase.hash;
    EXPECT_NEAR(actualPoint.longitude, testCase.expectedPoint.longitude, 0.1)
        << "Failed for hash: " << testCase.hash;
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
