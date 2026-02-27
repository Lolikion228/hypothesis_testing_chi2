#include "mod.h"


double pval(double h0_param, double h1_param, int sample_size, std::mt19937_64 &gen){
    int X[sample_size];
    sample(sample_size, X, h1_param, gen, 1);

    int right_lim = h1_param + 3 * sqrt(h1_param);
    double p[right_lim];

    for(int i=0; i<right_lim; ++i){
        p[i] = 1;
    }

    double t0 = chisq_stat(X, sample_size, p, right_lim);
    return 1 - pchsisq(t0, right_lim);
}