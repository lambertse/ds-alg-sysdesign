#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
namespace datastructure {
namespace hashing {
template <typename Type> uint32_t hash(const Type &key, const int &seed) {
  static_assert(true, "Type is not supported by hash function");
}

template <> uint32_t hash<int>(const int &key, const int &seed) {
  uint32_t hash = key ^ seed;
  hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
  hash = ((hash >> 16) ^ hash) * 0x45d9f3b;
  hash = (hash >> 16) ^ hash;
  return (hash);
}

template <>
uint32_t hash<std::string>(const std::string &key, const int &seed) {
  const uint32_t FNV_prime = 0x01000193;
  uint32_t hash = seed;

  for (char c : key) {
    hash ^= static_cast<uint32_t>(c);
    hash *= FNV_prime;
  }

  return hash;
}
} // namespace hashing

template <class Type> class CountMinSketch {
public:
  /*
    w=⌈2/error⌉
    d=⌈ln(1−certainty)/ln(1/2)⌉
    error: the error rate of the estimate
    certainty: the probability that the estimate is within the error rate
   * */
  CountMinSketch(double errRate, double certainty) {
    _width = static_cast<uint32_t>(std::ceil(2.0 / errRate));
    _depth = static_cast<uint32_t>(
        std::ceil(std::log(1.0 - certainty) / std::log(0.5)));
    std::cout << "Width: " << _width << " Depth: " << _depth << std::endl;
    _counter.resize(_depth, std::vector<int>(_width, 0));
  }

  CountMinSketch(int width, int depth) : _width(width), _depth(depth) {
    _counter.resize(depth, std::vector<int>(width, 0));
  }
  ~CountMinSketch() {}

  void update(const Type &key, const int &count) {
    for (int i = 0; i < _depth; i++) {
      int hash = hashing::hash<Type>(key, i) % _width;
      _counter[i][hash] += count;
    }
  }

  int estimate(const Type &key) {
    int min_count = INT_MAX;
    for (int i = 0; i < _depth; i++) {
      int hash = hashing::hash<Type>(key, i) % _width;
      min_count = std::min(min_count, _counter[i][hash]);
    }
    return min_count;
  }

  void display() {
    for (int i = 0; i < _depth; i++) {
      for (int j = 0; j < _width; j++) {
        std::cout << _counter[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }

private:
  std::vector<std::vector<int>> _counter;
  int _width;
  int _depth;
};
} // namespace datastructure
