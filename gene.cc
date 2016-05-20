#include "gene.hpp"
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::memcpy;
using std::memset;
using std::swap;
using std::rand;

namespace TSP {
    Gene* Gene::allocate(int n) {
        nCity = n;
        data = new int[nCity];
        temp = new int[nCity];
        return this;
    }

    Gene::Gene() : data(NULL), temp(NULL), nCity(0) {}

    Gene::Gene(int n) { allocate(n); }

    Gene::Gene(const Gene &o) {
        allocate(o.nCity);
        memcpy(data, o.data, nCity * sizeof(int));
    }

    Gene::~Gene() {
        if (nCity) {
            delete []data;
            delete []temp;
        }
    }

    Gene *Gene::init(int n) {
        if (!nCity) allocate(n);
        for (int i = 0; i < nCity; ++i) temp[i] = i;
        for (int i = 0; i < nCity; ++i) {
            int t = rand() % (nCity - i);
            data[i] = temp[t];
            for (; t < nCity - i - 1; ++t) temp[t] = temp[t + 1];
        }
        return this;
    }

    double Gene::evaluate(const Map &map) const {
        double ret = .0;
        for (int i = 0; i < nCity - 1; ++i) ret += map.distance(data[i], data[i + 1]);
        ret += map.distance(data[nCity - 1], data[0]);
        return ret;
    }

    Gene *Gene::vary(const Map &map) const {
        int a = rand() % nCity;
        int b = (a + 1) % nCity;
        int c, d;
        for (c = (b + 1) % nCity; (d = (c + 1) % nCity) != a; c = (c + 1) % nCity) {
            if (map.distance(data[a], data[b]) + map.distance(data[c], data[d])
                > map.distance(data[a], data[c]) + map.distance(data[b], data[d])) break;
        }
        if (d == a) return NULL;
        Gene *ret = new Gene(nCity);
        for (; b != d; b = (b + 1) % nCity, c = (c - 1 + nCity) % nCity) {
            ret -> data[b] = data[c];
        }
        for (; d != (a + 1) % nCity; d = (d + 1) % nCity) ret -> data[d] = data[d];
        return ret;
    }

    Gene *Gene::orderCross(const Gene *o) const {
        int a = rand() % nCity;
        int b = rand() % nCity;
        while (a == b) b = rand() % nCity;
        if (a > b) swap(a, b);

        memset(temp, 0, nCity * sizeof(int));
        Gene *ret = new Gene(nCity);
        for (int i = a; i < b; ++i) {
            ret -> data[i - a] = data[i];
            temp[data[i]] = 1;
        }
        int k = b - a;
        for (int i = b; i < nCity; ++i) {
            if (!temp[o -> data[i]]) ret -> data[k++] = o -> data[i];
        }
        for (int i = 0; i < b; ++i) {
            if (!temp[o -> data[i]]) ret -> data[k++] = o -> data[i];
        }

        return ret;
    }

    const int *Gene::getData() const {
        return data;
    }
}
