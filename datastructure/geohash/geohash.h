#include <iostream>
#include <string>

struct GeoPoint {
  double latitude;
  double longitude;
  GeoPoint(const double &lat, const double &longi)
      : latitude(lat), longitude(longi) {}
};

using GeoHash = std::string;

class GeoHashCalculator {
public:
  GeoHashCalculator();

  static GeoHash encode(const GeoPoint &point);
  static GeoPoint decode(const GeoHash &hash);

public:
  static int sPrecision;

private:
};
