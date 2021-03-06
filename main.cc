#include "train.hpp"
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace TSP;

Map map;
Train train(map);
const int batchSize = 10000;
const int logSize = 1000;

double print(const Gene *best, int n, ostream &o) {
    for (int i = 0; i < n - 1; ++i) o << best -> getData()[i] << " ";
    o << best -> getData()[n - 1] << endl;
    double ans = best -> evaluate(map);
    o << ans << endl;
    return ans;
}

void work(ostream &out, ostream &logger, int n) {
    train.select();
    double lastAns = print(train.best(), n, logger);
    for (;;) {
        double ans;
        for (int i = 0; i < batchSize / logSize; ++i) {
            for (int j = 0; j < logSize; ++j) {
                train.generate();
                train.select();
            }
            ans = print(train.best(), n, logger);
        }
        if (ans == lastAns) {
            print(train.best(), n, out);
            break;
        } else lastAns = ans;
    }
}

int main(int argc, char **argv) {
    assert(argc == 2);
    string prefix(argv[1]);

    fstream fin((prefix + "/in").c_str(), ios::in);
    fstream fout((prefix + "/out").c_str(), ios::out);
    fstream ferr((prefix + "/log").c_str(), ios::out);

    int n = map.input(fin);
    srand(time(NULL));
    train.init(n);

    work(fout, ferr, n);

    return 0;
}
