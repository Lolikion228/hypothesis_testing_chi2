#include "mod.h"

const double good_step_size = 0.05;

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

int comp(const void* a, const void* b) {
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
    
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

//F must be F[ (int) (1 / step_size) ]
// X[i] must be from [0,1]
void ecdf(double *X, int N, double step_size, double *F){
    double sorted_X[N];
    memcpy(sorted_X, X, sizeof(double)*N);
    qsort(X, N, sizeof(double), comp);

    int n_bins = (1.0 / step_size);
    double t = step_size;
    int j = 0;

    for(int i=0; i<N; ++i){
        // std::cout << "i = "<< i << "\n";
        // std::cout << "X[i] = "<< X[i] << "\n";
        while(X[i] >= t){
            // std::cout << "fix "<< j << " " << t << "\n";
            ++j;
            t += step_size;
        }
        // std::cout << "good "<< j << " " << t << "\n\n";
        ++F[j];
    }

    F[0] = F[0] / N;
    double cum = F[0];
    for(int i=1; i<n_bins; ++i){
        F[i] = F[i-1] + F[i] / N;
    }

}

void pecdf(double lambda1, double lambda2, double alpha,
           int psample_size, int main_sample_size, std::mt19937_64 &gen){
    
    int N = 1 / good_step_size;

    double p0[psample_size];
    psample(lambda1, lambda1, psample_size, p0, main_sample_size, gen);        
    double F0[N]{};
    ecdf(p0, psample_size, good_step_size, F0);    

    double p1[psample_size];
    psample(lambda1, lambda2, psample_size, p1, main_sample_size, gen);
    double F1[N]{};
    ecdf(p1, psample_size, good_step_size, F1);  
    
    std::cout << "pval     F0     F1\n";
    for(int i=0; i<N; ++i){
        printf("%3.2f  %5.3f  %5.3f\n", good_step_size*(i+1), F0[i], F1[i]);
    }

    std::cout << "\n";
    printf("on alpha = %.3f\n", alpha);
    int ix = 0;
    if(alpha >= good_step_size){
        ix = alpha / good_step_size - 1 + 1e-6;
    }
    printf("ERR_1 = %.3f   POW = %.3f\n", F0[ix], F1[ix]);
}