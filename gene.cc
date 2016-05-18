#include "gene.hpp"
#include <cstdlib>
#include <algorithm>

using std::swap;
using std::rand;

namespace TSP {
    void Gene::init(int n) {
        nCity = n;
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

        for (int i = 0; i < nCity; ++i) temp[i] = 0;
        Gene ret;
        ret.nCity = nCity;
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
