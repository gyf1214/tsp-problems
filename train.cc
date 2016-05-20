#include "train.hpp"
#include <cstdlib>

using std::rand;

namespace TSP {
    inline double randDouble() {
        return (double)rand() / (double)(RAND_MAX);
    }

    inline bool comp(Gene *x, Gene *y) {
        return x -> p < y -> p;
    }

    Train::Train(const Map &m) : map(m) {}

    void Train::init(int n) {
        for (int i = 0; i < scale; ++i) pop.push_back((new Gene()) -> init(n));
    }

    void Train::select() {
        for (int i = 0; i < pop.size(); ++i) pop[i] -> p = pop[i] -> evaluate(map);
        sort(pop.begin(), pop.end(), comp);
        for (int i = scale; i < pop.size(); ++i) delete pop[i];
        pop.resize(scale);
    }

    void Train::generate() {
        for (int i = 0; i < scale; ++i) {
            if (randDouble() < pm) {
                Gene *x = pop[i] -> vary(map);
                if (x) pop.push_back(x);
            }
        }
        for (int i = 0; i < scale; ++i) {
            if (randDouble() < pc) {
                int x = rand() % scale;
                while (x == i) x = rand() % scale;
                pop.push_back(pop[i] -> orderCross(pop[x]));
            }
        }
    }

    const Gene *Train::best() {
        return pop[0];
    }
}
