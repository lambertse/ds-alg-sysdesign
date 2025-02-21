#include "geohash.h"

constexpr double MAX_LONGITUDE = 180.0;
constexpr double MIN_LONGITUDE = -180.0;
constexpr double MAX_LATITUDE = 90.0;
constexpr double MIN_LATITUDE = -90.0;

#define GetBit(num, idx) (num >> idx) & 1
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

namespace util {
int findIdx(const char &c);
}

struct GeoBound {
  double minLong;
  double maxLong;
  double minLat;
  double maxLat;
  GeoBound(int minLat, int minLong, int maxLat, int maxLong)
      : minLat(minLat), minLong(minLong), maxLat(maxLat), maxLong(maxLong) {}
};

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

GeoBound GeoHashCalculator::bound(const GeoHash &hash) {
  int i = 0;
  double minLong = MIN_LONGITUDE;
  double maxLong = MAX_LONGITUDE;
  double minLat = MIN_LATITUDE;
  double maxLat = MAX_LATITUDE;
  bool isEven = true;

  for (const auto &c : hash) {
    int index = util::findIdx(c);
    for (int i = 4; i >= 0; i--) {
      int bit = GetBit(index, i);
      if (isEven) {
        // Handle longitude
        double mid = (minLong + maxLong) / 2;
        if (bit) {
          minLong = mid;
        } else {
          maxLong = mid;
        }
      } else {
        // Handle latitude
        double mid = (minLat + maxLat) / 2;
        if (bit) {
          minLat = mid;
        } else {
          maxLat = mid;
        }
      }
      isEven = !isEven;
    }
  }

  GeoBound bound(0, 0, 0, 0);
  bound.minLat = minLat;
  bound.maxLat = maxLat;
  bound.minLong = minLong;
  bound.maxLong = maxLong;

  return bound;
}

GeoPoint GeoHashCalculator::decode(const GeoHash &hash) {
  GeoBound bound = GeoHashCalculator::bound(hash);
  /*
   * std::cout << "minLat: " << bound.minLat << " maxLat: " << bound.maxLat
   *             << " minLong: " << bound.minLong << " maxLong: " <<
   * bound.maxLong
   *                         << std::endl;
   * */
  GeoPoint ret(0, 0);
  ret.latitude = (bound.maxLat + bound.minLat) / 2;
  ret.longitude = (bound.maxLong + bound.minLong) / 2;
  return ret;
}

namespace util {
int findIdx(const char &c) {
  for (int i = 0; i < kBase32.length(); i++) {
    if (kBase32[i] == c)
      return i;
  }
  return -1;
}
} // namespace util
