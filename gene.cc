#include "gene.hpp"
#include <cstdlib>
#include <algorithm>

using std::memcpy;
using std::memset;
using std::swap;
using std::rand;

namespace TSP {
    void Gene::allocate(int n) {
        nCity = n;
        data = new int[nCity];
        temp = new int[nCity];
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

    Gene &Gene::operator =(const Gene &o) {
        if (!nCity) allocate(o.nCity);
        memcpy(data, o.data, nCity * sizeof(int));
        return *this;
    }

    void Gene::init(int n) {
        allocate(n);
        for (int i = 0; i < nCity; ++i) temp[i] = i;
        for (int i = 0; i < nCity; ++i) {
            int t = rand() % (nCity - i);
            data[i] = temp[t];
            for (; t < nCity - i - 1; ++t) temp[t] = temp[t + 1];
        }
    }

    double Gene::evaluate(const Map &map) const {
        double ret = .0;
        for (int i = 0; i < nCity - 1; ++i) ret += map.distance(data[i], data[i + 1]);
        ret += map.distance(data[nCity - 1], data[0]);
        return 1 / ret;
    }

    void Gene::varySelf() {
        int i = rand() % nCity;
        int j = rand() % nCity;
        while (i == j) j = rand() % nCity;
        swap(data[i], data[j]);
    }

    Gene Gene::vary() {
        Gene ret = *this;
        ret.varySelf();
        return ret;
    }

    Gene Gene::orderCross(const Gene &o) {
        int a = rand() % nCity;
        int b = rand() % nCity;
        while (a == b) b = rand() % nCity;
        if (a > b) swap(a, b);

        memset(temp, 0, nCity * sizeof(int));
        Gene ret(nCity);
        for (int i = a; i < b; ++i) {
            ret.data[i - a] = data[i];
            temp[data[i]] = 1;
        }
        int k = b - a;
        for (int i = b; i < nCity; ++i) {
            if (!temp[o.data[i]]) ret.data[k++] = o.data[i];
        }
        for (int i = 0; i < b; ++i) {
            if (!temp[o.data[i]]) ret.data[k++] = o.data[i];
        }

        return ret;
    }

    const int *Gene::getData() const {
        return data;
    }
}
