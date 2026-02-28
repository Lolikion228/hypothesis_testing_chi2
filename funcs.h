#include <cmath>
#include <iostream>


double pchsisq(double t, int k);

double chisq_stat(int *X, int sample_size, double *p, int N, int verbose);


template <typename T>
void print_arr(T x, int n){
    std::cout << "[" ;
    for(int i=0; i<n; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << "]\n";
}