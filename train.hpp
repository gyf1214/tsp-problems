#ifndef __TRAIN
#define __TRAIN

#include "gene.hpp"

namespace TSP {
    const int maxGene = 1001;
    const double pc = 0.5;
    const double pm = 0.2;

    class Train {
        Gene pop[maxGene];
        Gene oldPop[maxGene];
        double p[maxGene];
        const Map &map;
        int best(Gene *);
    public:
        Train(const Map &);
        void init(int);
        void select(void);
        void generate(void);
        const Gene &best(void);
    };
}

#endif
