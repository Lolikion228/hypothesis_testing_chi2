#include "funcs.h"


template <typename T>
void print_arr(T x, int n){
    std::cout << "[" ;
    for(int i=0; i<n; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << "]\n";
}


double dchsisq(double t, int k){
    double c = pow(0.5, k / 2.) / std::tgamma(k / 2.);
    return c * pow(t, k / 2. - 1) * exp(-t / 2.);
}

double pchsisq(double t, int k){
    double c = pow(0.5, k / 2.) / std::tgamma(k / 2.);
    return c * pow(t, k / 2. - 1) * exp(-t / 2.);
}


double chisq_stat(int *X, int sample_size, double *p, int N){
    double res = 0;

    double obs_freq[N]{};
    double exp_freq[N]{};

    for(int i=0; i<sample_size; ++i){
        if( X[i] >= (N - 1) ) {
            ++obs_freq[N - 1];
        }
        else {
            ++obs_freq[ X[i] ];
        }
    }

    for(int i=0; i<N; ++i){
        exp_freq[i] = sample_size * p[i];
    }

    // std::cout << "sample:\n";
    // print_arr(X, sample_size);
    // std::cout << "obs_freq:\n";
    // print_arr(obs_freq,N);
    // std::cout << "p:\n";
    // print_arr(p,N);
    // std::cout << "exp_freq:\n";
    // print_arr(exp_freq,N);
    


    for(int i=0; i<N; ++i){
        res += pow(obs_freq[i] - exp_freq[i], 2) / (sample_size * p[i]);
    }

    return res;
}