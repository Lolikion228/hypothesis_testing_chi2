#include <iostream>
#include "gen.h"
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

    std::mt19937_64 gen(std::random_device{}());

    double lambda1 = 20.5;
    double lambda2 = 20.9;

    double p = pval(lambda1, lambda2, 10000, gen, 2);
    std::cout << "pval = " << p << "\n";
}


void test_psample(){
    std::mt19937_64 gen(std::random_device{}());
    double lambda1 = 20.1;
    double lambda2 = 20.9;
    const int psample_size = 10000;
    int main_sample_size = 1000;

    double p0[psample_size];
    psample(lambda1, lambda1, psample_size, p0, main_sample_size, gen);
    FILE *f = fopen("./txt/psample_h0.txt", "w+");
    for(int i=0; i<psample_size; ++i){
        fprintf(f, "%f\n", p0[i]);
    }
    fclose(f);

    double p1[psample_size];
    psample(lambda1, lambda2, psample_size, p1, main_sample_size, gen);
    f = fopen("./txt/psample_h1.txt", "w+");
    for(int i=0; i<psample_size; ++i){
        fprintf(f, "%f\n", p1[i]);
    }
    fclose(f);

    f = fopen("./txt/psample_params.txt", "w+");
    fprintf(f, "%f %f %d %d\n", lambda1, lambda2, main_sample_size, psample_size);
    fclose(f);
}


void test_chi2(){
    int N = 100000;
    double h0_param = 9.1;
    double h1_param = 9.1;
    std::mt19937_64 gen(std::random_device{}());

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

    FILE *f = fopen("./txt/chi2.txt", "w+");
    fprintf(f,"%d\n", right_lim - 1);
    int X[N];
    double t0;
    for(int i=0; i<1000; ++i){
        sample(N, X, h1_param, gen, 0);
        fprintf(f, "%f\n", chisq_stat(X, N, p, right_lim, 0));
    }
    fclose(f);

}



void test_ecdf(){

    double X[] = {0.9, 0.9, 0.04, 0.03, 0.5, 0.5, 0.5, 0.5, 0.7};

    double step = 0.05;
    int N = 1 / step;
    double F[N]{};

    ecdf(X, 9, step, F);

    print_arr(X, 9);
    for(int i=0; i<N; ++i){
        printf("%.2f  %.2f\n", step*(i+1), F[i]);
    }
}


int main(){
    //test_rpois();
    //test_pchisq();
    //test_pval();
    test_psample();
    // test_chi2();
    //test_ecdf();

    std::mt19937_64 gen(std::random_device{}());
    pecdf(20.1, 20.9, 0.15, 10000, 1000, gen);
}