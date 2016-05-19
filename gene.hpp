#ifndef __GENE
#define __GENE

#include "city.hpp"

namespace TSP {
    class Gene {
        int *data, *temp;
        int nCity;
        void allocate(int);
    public:
        Gene(void);
        Gene(int);
        Gene(const Gene &);
        ~Gene(void);
        Gene &operator =(const Gene &);

        void init(int);
        double evaluate(const Map &) const;
        void varySelf(void);
        Gene vary(void);
        Gene orderCross(const Gene &);
        const int *getData(void) const;
    };
}

#endif
