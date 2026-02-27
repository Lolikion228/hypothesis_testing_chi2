#include "gen.h"


int rpois1(double lambda, std::mt19937_64 &gen){
    double p = exp(-lambda);
    double s = p;
    int k = 0;

    double alpha = gen() / (double)std::numeric_limits<uint64_t>::max();

    while(alpha > s){
        ++k;
        p *= lambda / k;
        s += p;
    }

    return k;
}


int rpois2(double lambda, std::mt19937_64 &gen){
    double t = 1;
    double c = exp(-lambda);
    int n = 0;

    t *= gen() / (double)std::numeric_limits<uint64_t>::max();

    while (t >= c){
        t *= gen() / (double)std::numeric_limits<uint64_t>::max();
        ++n;
    }

    return n;
}



void sample(int N, int *X, double lambda, std::mt19937_64 &gen, int mod_type){
    switch (mod_type)
    {
    case 0:
        for(int i=0; i<N; ++i)
            X[i] = rpois1(lambda, gen);
        break;

    case 1:
        for(int i=0; i<N; ++i)
            X[i] = rpois2(lambda, gen);
        break;

    default:
        std::cout << "mode type must be 0 or 1\n";
        break;
    }
}