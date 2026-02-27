#include "mod.h"


double pval(double h0_param, double h1_param, int sample_size, std::mt19937_64 &gen, int verbose){
    int X[sample_size];
    sample(sample_size, X, h1_param, gen, 0);


    int right_lim = h0_param + 3 * sqrt(h0_param);
    double p[right_lim];
    
    double t = exp(-h0_param);
    double sum = t;

    p[0] = t;

    for(int i=1; i<right_lim; ++i){
        t *= h0_param / i;
        p[i] = t;
        sum += p[i];
    }

    p[right_lim - 1] += (1 - sum);

    double t0 = chisq_stat(X, sample_size, p, right_lim, verbose);
    
    if(verbose >= 1)
        std::cout << "chi2 = " << t0 << "\n";

    return 1 - pChi(t0, right_lim - 1);
}


void psample(double h0_param, double h1_param, int psample_size,
             double *X, int main_sample_size, std::mt19937_64 &gen){
    for(int i=0; i<psample_size; ++i)
        X[i] = pval(h0_param, h1_param, main_sample_size, gen, 0);
}