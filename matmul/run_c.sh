#!/usr/bin/env bash

# MKL test for C version
# Run matrix multiplication for more matrix's size

echo "= = = = = = = = = = = = = = = = = = = ="
echo "= = = = = = C VERSION DGEMM = = = = = ="
echo "= = = = = = = = = = = = = = = = = = = ="
echo

TEST=1

# perform test
test_mic()
{
    echo "Test $TEST: C version with MKL"
    echo "Test $TEST: (MIC version)"
    echo "Test $TEST: $OMP_NUM_THREADS threads"

    ./c_dgemm

    echo "Test $TEST: complete"
    echo -e "\n====================\n"

    TEST=$((TEST + 1))
}

export MKL_MIC_ENABLE=0
export OFFLOAD_REPORT=2
export OMP_NUM_THREADS=240
export KMP_AFFINITY=compact

export MATRIX_K=2048
export MATRIX_M=2048
export MATRIX_N=2048

test_mic

export MATRIX_K=4096
export MATRIX_M=4096
export MATRIX_N=4096

test_mic

export MATRIX_K=8192
export MATRIX_M=8192
export MATRIX_N=8192

test_mic

export MATRIX_K=16384
export MATRIX_M=16384
export MATRIX_N=16384

test_mic

echo "* * * * * * * * * * * * * * * * * * * *"
echo "* * * * * * C VERSION END * * * * * * *"
echo "* * * * * * * * * * * * * * * * * * * *"
echo

