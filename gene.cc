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

    Gene *Gene::varySelf() {
        int i = rand() % nCity;
        int j = rand() % nCity;
        while (i == j) j = rand() % nCity;
        swap(data[i], data[j]);
        return this;
    }

    Gene *Gene::vary() const {
        return (new Gene(*this)) -> varySelf();
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
