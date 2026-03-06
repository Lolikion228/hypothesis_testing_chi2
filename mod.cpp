#include "mod.h"

const double GOOD_STEP_SIZE = 0.05;
const double GOOD_CUM_EXP_FREQ_THRESH = 5.0;
const double EPS = 1e-6;
const double ALMOST_ONE = 1.0 - EPS;


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
     
    int k;
    double t0 = chisq_stat(X, sample_size, verbose, GOOD_CUM_EXP_FREQ_THRESH, h0_param, k);
    
    if(verbose >= 1){
        std::cout << "d.f. = " << k << "\n";
        std::cout << "chi2 = " << t0 << "\n";
    }
    
    double res = 1 - pChi(t0, k - 1);
    
    return std::min(res, ALMOST_ONE);
}


void psample(double h0_param, double h1_param, int psample_size,
             double *X, int main_sample_size, std::mt19937_64 &gen){
    for(int i=0; i<psample_size; ++i)
        X[i] = pval(h0_param, h1_param, main_sample_size, gen, 0);
}


//F must be F[ (int) (1 / step_size) ]
// X[i] must be from [0,1)  [1 excluded]
void ecdf(double *X, int N, double step_size, double *F){
    int n_bins = (1.0 / step_size);
    for(int i=0; i<N; ++i) ++F[ (int) (X[i] * n_bins) ]; // if X[i]=1 then =( 
    
    F[0] = F[0] / N;
    for(int i=1; i<n_bins; ++i){
        F[i] = F[i-1] + F[i] / N;
    }

}

void pecdf(double lambda1, double lambda2, double alpha,
           int psample_size, int main_sample_size, std::mt19937_64 &gen){
    
    int N = 1 / GOOD_STEP_SIZE;

    double p0[psample_size];
    psample(lambda1, lambda1, psample_size, p0, main_sample_size, gen);        
    double F0[N]{};
    ecdf(p0, psample_size, GOOD_STEP_SIZE, F0);    

    double p1[psample_size];
    psample(lambda1, lambda2, psample_size, p1, main_sample_size, gen);
    double F1[N]{};
    ecdf(p1, psample_size, GOOD_STEP_SIZE, F1);  
    
    std::cout << "pval     F0     F1\n";
    for(int i=0; i<N; ++i){
        printf("%3.2f  %5.3f  %5.3f\n", GOOD_STEP_SIZE*(i+1), F0[i], F1[i]);
    }

    std::cout << "\n";
    printf("on alpha = %.3f\n", alpha);
    int ix = 0;
    if(alpha >= GOOD_STEP_SIZE){
        ix = alpha / GOOD_STEP_SIZE - 1 + EPS;
    }
    printf("ERR_1 = %.3f   POW = %.3f\n", F0[ix], F1[ix]);
}