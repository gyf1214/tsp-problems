#ifndef __TRAIN
#define __TRAIN

#include "gene.hpp"
#include <vector>

namespace TSP {
    const int scale = 200;
    const double pc = 0.1;
    const double pm = 1;

    class Train {
        std::vector<Gene *> pop;
        const Map &map;
    public:
        Train(const Map &);
        void init(int);
        void select(void);
        void generate(void);
        const Gene *best(void);
    };
}

#endif
