#include <iostream>
#include "gen.h"
#include "funcs.h"
#include "mod.h"
#include "PROBDIST.H"

const int seed = 1337;

void test_rpois(){
    std::mt19937_64 gen(seed);
    const int N = 10000;
    double lambda = 10.7;
    int a[N];

    sample(N, a, lambda, gen, 1);
    
    FILE *f = fopen("./pois_res.txt", "w+");
    fprintf(f, "%f\n", lambda);

    for(int i=0; i<N; ++i)
        fprintf(f, "%d\n", a[i]);
    fclose(f);
}


void test_pchisq(){
    FILE *f = fopen("./chisq_res.txt", "w+");

    double k = 10;
    double a = 0.01;
    double b = 20; 
    fprintf(f, "%f\n", k);

    int N = 100;
    double d = (b  - a)/N;
    double x;

    for(int i=0; i<N; ++i){
        x =  a + d*i;   
        fprintf(f, "%f %f\n", x, pChi(x, k));
    }
    fclose(f);
}


void test_pval(){
    std::mt19937_64 gen(seed);

    double lambda1 = 10.5;
    double lambda2 = 12.5;

    double p = pval(lambda1, lambda2, 50, gen);
    std::cout << "pval = " << p << "\n";
}



void test_chisq_stat(){


}


int main(){
    //test_rpois();
    //test_pchisq();
    test_pval();

    // double chi2 = chisq_stat()
}