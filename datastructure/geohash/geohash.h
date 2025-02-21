#include <string>

struct GeoPoint {
  double latitude;
  double longitude;
  GeoPoint(const double &lat, const double &longi)
      : latitude(lat), longitude(longi) {}
};

using GeoHash = std::string;
enum class Direction { North, South, East, West };
struct GeoAdjacent {
  GeoHash north;
  GeoHash south;
  GeoHash east;
  GeoHash west;
  GeoHash southeast;
  GeoHash southwest;
  GeoHash northeast;
  GeoHash northwest;
};

class GeoBound;
class GeoHashCalculator {
public:
  GeoHashCalculator();

  static GeoHash encode(const GeoPoint &point);
  static GeoPoint decode(const GeoHash &hash);
  static GeoHash adjecent(const GeoHash &hash, Direction direction);
  static GeoAdjacent adjacent(const GeoHash &hash);

public:
  static int sPrecision;

private:
  static GeoBound bound(const GeoHash &hash);
};
