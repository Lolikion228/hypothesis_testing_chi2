#include "funcs.h"
#include "gen.h"
#include "probdist.h"


double pval(double h0_param, double h1_param, int sample_size, std::mt19937_64 &gen, int verbose);


void psample(double h0_param, double h1_param, int psample_size,
             double *X, int main_sample_size, std::mt19937_64 &gen);


void pecdf(double lambda1, double lambda2, double alpha,
           int psample_size, int main_sample_size, std::mt19937_64 &gen);

void ecdf(double *X, int N, double step_size, double *F);

