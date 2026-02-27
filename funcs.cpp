#include "funcs.h"


template <typename T>
void print_arr(T x, int n){
    std::cout << "[" ;
    for(int i=0; i<n; ++i){
        std::cout << x[i] << " ";
    }
    std::cout << "]\n";
}

template <typename T>
double sum_arr(T x, int n){
    double sum = 0;
    for(int i=0; i<n; ++i){
        sum += x[i];
    }
    return sum;
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
    //std::cout << "obs_freq:\n";
    // print_arr(obs_freq,N);
    // std::cout << "p:\n";
    // print_arr(p,N);
    // std::cout << "exp_freq:\n";
    // print_arr(exp_freq,N);
    std::cout << "sample_size = " << sample_size << "\n";
    std::cout<< "obs_freq_sum = " << sum_arr(obs_freq, N) << "\n";
    std::cout<< "exp_freq_sum = " << sum_arr(exp_freq, N) << "\n";
    
    double cum_exp_freq_hist[N]{};
    double diff_hist[N]{};
    double summand_hist[N]{};
    double cum_exp_freq = 0;
    double cum_obs_freq = 0;
    double diff;
    double summand;

    for(int i=0; i<N; ++i){
        cum_obs_freq += obs_freq[i];
        cum_exp_freq += exp_freq[i];
        cum_exp_freq_hist[i] = cum_exp_freq;
        if(cum_exp_freq >= 5.){
            diff = cum_obs_freq - cum_exp_freq;
            summand = diff * diff / cum_exp_freq;
            res += summand;
            cum_exp_freq = 0;
            cum_obs_freq = 0;
            diff_hist[i] = diff;
            summand_hist[i] = summand;
        }
    }

    if(cum_exp_freq != 0){
        diff = cum_obs_freq - cum_exp_freq;
        summand = diff * diff / cum_exp_freq;
        res += summand;
        diff_hist[N-1] = diff;
        summand_hist[N-1] = summand;
    }

    std::cout << " i  obs_freq  exp_freq  cum_exp_freq   diff  summand\n";
    for(int i=0; i<N; ++i){
        printf("%2d  %8.1f  %8.2f  %12.2f  %5.2f  %7.2f\n",
               i, obs_freq[i], exp_freq[i], cum_exp_freq_hist[i],
               diff_hist[i], summand_hist[i]);
        if(diff_hist[i] != 0){
            for(int j=0; j<52; ++j)
                std::cout << '-';
            std::cout << "\n";
        }
    }
    for(int j=0; j<52; ++j)
        std::cout << '-';
    std::cout << "\n";

    // for(int i=0; i<N; ++i){
    //     res += pow(obs_freq[i] - exp_freq[i], 2) / (sample_size * p[i]);
    // }

    return res;
}