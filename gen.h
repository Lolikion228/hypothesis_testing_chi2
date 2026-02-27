#include <random>
#include <iostream>


int rpois1(double lambda, std::mt19937_64 &gen);

int rpois2(double lambda, std::mt19937_64 &gen);

void sample(int N, int *X, double lambda, std::mt19937_64 &gen, int mod_type);