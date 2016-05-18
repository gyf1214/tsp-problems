#include "city.hpp"
#include <cmath>

using std::sqrt;

namespace TSP {
    int Map::input(std::istream &is) {
        is >> n;
        for (int i = 0; i < n; ++i) is >> city[i].x >> city[i].y;
        return n;
    }

    double Map::distance(int i, int j) const {
        return sqrt((city[i].x - city[j].x) * (city[i].x - city[j].x)
            + (city[i].y - city[j].y) * (city[i].y - city[j].y));
    }
}
