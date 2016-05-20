#ifndef __GENE
#define __GENE

#include "city.hpp"

namespace TSP {
    class Gene {
        int *data, *temp;
        int nCity;
        Gene *allocate(int);
    public:
        double p;

        Gene(void);
        Gene(int);
        Gene(const Gene &);
        ~Gene(void);

        Gene *init(int);
        double evaluate(const Map &) const;
        Gene *vary(const Map &) const;
        Gene *orderCross(const Gene *) const;
        const int *getData(void) const;
    };
}

#endif
