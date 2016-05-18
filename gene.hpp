#ifndef __GENE
#define __GENE

#include "city.hpp"

namespace TSP {
    class Gene {
        int data[maxCity], temp[maxCity];
        int nCity;
    public:
        void init(int);
        double evaluate(const Map &) const;
        void varySelf(void);
        Gene vary(void);
        Gene orderCross(const Gene &);
        const int *getData(void) const;
    };
}

#endif
