#include "funcs.h"
#include "gen.h"
#include "PROBDIST.H"

double pval(double h0_param, double h1_param, int sample_size, std::mt19937_64 &gen, int verbose);

void psample(double h0_param, double h1_param, int psample_size,
             double *X, int main_sample_size, std::mt19937_64 &gen);