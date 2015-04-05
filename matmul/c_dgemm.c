/**
* @file c_dgemm.c
*
* Matrix multiplication
* It using function dgemm() from Intel MKL
*
* @author: Dominik Simek <xsimek23@stud.fit.vutbr.cz>
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "mkl.h"
#include <omp.h>

const double ALPHA = 1.0;
const double BETA = 0.0;

/**
* Main function
*/
int main()
{
    // read enviroment variables
    char* eK;
    unsigned K = 4096;
    unsigned M = 4096;
    unsigned N = 4096;
    unsigned ITER = 1;

    // size of matrix K
    eK = getenv("MATRIX_K");
    if(eK != NULL)
        K = atoi(eK);
    else
        K = 4096;

    // size of matrix M
    char* eM;
    eM = getenv("MATRIX_M");
    if(eM != NULL)
        M = atoi(eM);
    else
        M = 4096;

    // size of matrix N
    char* eN;
    eN = getenv("MATRIX_N");
    if(eN != NULL)
        N = atoi(eN);
    else
        N = 4096;

    // number of iterations
    char* eI;
    eI = getenv("MATRIX_ITER");
    if(eI != NULL)
        ITER = atoi(eI);
    else
        ITER = 1;

    double *A, *B, *C;
    int n;

    // allocate aligned arrays
    A = (double *)mkl_malloc(M * K * sizeof(double), 64);
    B = (double *)mkl_malloc(K * N * sizeof(double), 64);
    C = (double *)mkl_malloc(M * N * sizeof(double), 64);
    if (A == NULL || B == NULL || C == NULL)
    {
        fprintf(stderr, "ERROR: mkl_malloc()\n");
        mkl_free(A);
        mkl_free(B);
        mkl_free(C);

        return EXIT_FAILURE;
    }

    // initialize arrays
    // NUMA Firts Touch Policy
    #pragma omp parallel
    {
        #pragma omp for
        for (unsigned i = 0; i < (M * K); i++)
        {
            A[i] = (double)(i+1);
        }

        #pragma omp for
        for(unsigned i = 0; i < (K * N); i++)
        {
            B[i] = (double)(-i-1);
        }

        #pragma omp for
        for(unsigned i = 0; i < (M * N); i++)
        {
            C[i] = 0.0;
        }
    }

    // start computation
    const double tstart = omp_get_wtime();
    for(unsigned i = 0; i < ITER; i++)
    {
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, ALPHA, A, K, B, N, BETA, C, N);
    }
    const double tend = omp_get_wtime();

    printf("cblas_dgemm(%dx%d, %dx%d), %d iterations\n", M, K, K, N, ITER);
    printf("cblas_dgemm(): %f sec\n", tend - tstart);

    return EXIT_SUCCESS;
}
