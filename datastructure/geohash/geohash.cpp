#include "geohash.h"

constexpr int MAX_LONGITUDE = 180;
constexpr int MIN_LONGITUDE = -180;
constexpr int MAX_LATITUDE = 90;
constexpr int MIN_LATITUDE = -90;

/*
                  longitude
-180                                            180
<------------------------------------------------->
===================================================
=                                                 =
=                                                 =
=                                                 =
=                                                 =
=                WORLD MAP                        =
=                                                 =
=                                                 =
=                                                 =
=                                                 =
=                                                 =
===================================================
 */

const static std::string kBase32 = "0123456789bcdefghjkmnpqrstuvwxyz";

int GeoHashCalculator::sPrecision = 12;

GeoHash GeoHashCalculator::encode(const GeoPoint &point) {
  if (point.longitude < MIN_LONGITUDE || point.longitude > MAX_LONGITUDE ||
      point.latitude < MIN_LATITUDE || point.latitude > MAX_LATITUDE) {
    throw std::invalid_argument("Invalid latitude or longitude");
  }

  GeoHash hash;
  int base = kBase32.length();
  int bit = 0;
  int step = 0;
  int isEven = true; // Start from bit 0 to 31st bit
  int index = 0;

  double leftLong = MIN_LONGITUDE;
  double rightLong = MAX_LONGITUDE;
  // 2 parts:  [-180, 0), [0,180)

  double leftLat = MIN_LATITUDE;
  double rightLat = MAX_LATITUDE;
  // 2 parts: [-90, 0), [0, 90)

  while (hash.length() < sPrecision) {
    if (isEven) {
      // bitsec with longitude
      double mid = (rightLong + leftLong) / 2;
      if (point.longitude >= mid) {
        index = (index << 1) + 1;
        leftLong = mid;
      } else {
        index = index << 1;
        rightLong = mid;
      }
    } else {
      // bitsec with latitude
      double mid = (rightLat + leftLat) / 2;
      if (point.latitude >= mid) {
        index = (index << 1) + 1;
        leftLat = mid;
      } else {
        index = index << 1;
        rightLat = mid;
      }
    }

    isEven = !isEven;
    // With base 32, each number has 5 bit
    if (++bit == 5) {
      hash += kBase32[index];
      index = 0;
      bit = 0;
    }
  }

  return hash;
}
