#include "funcs.h"


double pchsisq(double t, int k){
    double c = pow(0.5, k / 2.) / std::tgamma(k / 2.);
    return c * pow(t, k / 2. - 1) * exp(-t / 2.);
}


double chisq_stat(int *X, int sample_size, double *p, int N){
    double res = 0;
    double freq[N]{};

    for(int i=0; i<sample_size; ++i){
        if( X[i] >= (N - 1) ) ++freq[N - 1];
        else ++freq[ X[i] ];
    }

    for(int i=0; i<N; ++i){
        res += pow(freq[i] - sample_size * p[i], 2) / ( sample_size * p[i] );
    }

    return res;
}