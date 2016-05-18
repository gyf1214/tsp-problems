#include "train.hpp"
#include <cstdlib>

using std::rand;

namespace TSP {
    inline double randDouble() {
        return (double)rand() / (double)(RAND_MAX);
    }

    Train::Train(const Map &m) : map(m) {}

    void Train::init(int n) {
        for (int i = 0; i < maxGene; ++i) oldPop[i].init(n);
    }

    void Train::select() {
        pop[0] = oldPop[best(oldPop)];

        p[0] = oldPop[0].evaluate(map);
        for (int i = 1; i < maxGene; ++i) p[i] = p[i - 1] + oldPop[i].evaluate(map);
        for (int i = 0; i < maxGene; ++i) p[i] /= p[maxGene - 1];
        for (int i = 1; i < maxGene; ++i) {
            double next = randDouble();
            int k;
            for (k = 0; k < maxGene; ++k) if (next < p[k]) break;
            pop[i] = oldPop[k];
        }
    }

    void Train::generate() {
        oldPop[0] = pop[0];
        for (int i = 1; i < maxGene; ++i) if (randDouble() < pm) pop[i].varySelf();
        for (int i = 1; i < maxGene; i += 2) {
            if (randDouble() < pc) {
                oldPop[i] = pop[i].orderCross(pop[i + 1]);
                oldPop[i + 1] = pop[i + 1].orderCross(pop[i]);
            } else {
                oldPop[i] = pop[i];
                oldPop[i + 1] = pop[i + 1];
            }
        }
    }

    const Gene &Train::best() {
        return pop[0];
     }

     int Train::best(Gene *pop) {
         int ans = 0;
         double best = pop[ans].evaluate(map);
         for (int i = 1; i < maxGene; ++i) {
             double now = pop[i].evaluate(map);
             if (now > best) {
                 best = now;
                 ans = i;
             }
         }
         return ans;
     }
}
