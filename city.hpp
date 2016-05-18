#ifndef __CITY
#define __CITY

#include <iostream>

namespace TSP {
    const int maxCity = 1000;

    struct City {
        double x, y;
    };

    class Map {
        City city[maxCity];
        int n;
    public:
        int input(std::istream &);
        double distance(int, int) const;
    };
}

#endif
