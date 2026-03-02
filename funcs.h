#include <cmath>
#include <iostream>


// double pchsisq(double t, int k);


/*
X: sample
p: vector of probs
N: size of p
*/
double chisq_stat(int *X, int sample_size, double *p, int N, int verbose);

double chisq_stat(int *X, int sample_size, double *p, int N, int verbose, double cum_exp_freq_thresh);

template <typename T>
void print_arr(T x, int n){
    std::cout << "[" ;
    for(int i=0; i<n; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << "]\n";
}