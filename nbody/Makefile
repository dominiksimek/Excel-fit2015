# Makefile
# N-Body Simuluation
# Dominik Simek <xsimek23@stud.fit.vutbr.cz>

CFLAGS=-wd588 -ansi-alias -openmp -mmic
OPT=-O3
REPORT=-vec-report3 -opt-report -opt-report-file opt_report.rpt

N=1000000
DT=0.001f
STEPS=1

PARAMS=-DN=$(N) -DDT=$(DT) -DSTEPS=$(STEPS)

INPUT=../input1000.dat
OUTPUT=out.dat

PAPI_EVENTS=PAPI_FP_OPS|PAPI_SP_OPS|PAPI_L1_DCM|PAPI_L2_DCM

all:
	icc $(CFLAGS) $(OPT) $(REPORT) $(PARAMS) -c nbody.cpp
	icc $(CFLAGS) $(OPT) $(PARAMS) -S -fsource-asm -c nbody.cpp
	icc $(CFLAGS) $(PARAMS) nbody.o main.cpp -o bin/body3000k
	icc $(CFLAGS) gen.cpp -o bin/gen

clean:
	rm -f *.o nbody

clean-all:
	make clean
	rm -f bin/*

run:
	PAPI_EVENTS='$(PAPI_EVENTS)' ./nbody $(INPUT) $(OUTPUT)
