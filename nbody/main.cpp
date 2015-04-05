/**
* @file main.cpp
*
* N-Body Simuluation
* Main function of particles simulation program
*
* @author: Dominik Simek <xsimek23@stud.fit.vutbr.cz>
*
*/

#include <cstdio>
#include <cmath>
#include <omp.h>

#include "nbody.h"
#include "../timer.h"

int main(int argc, char **argv)
{
    int i;
    FILE *fp;

    start_timer();

    // particle's structure, initialize
    t_particles_DA *p_DA = particles_alloc(N);
    particles_init(*p_DA);

    if (argc != 3)
    {
        printf("Usage: nbody <input> <output>\n");
        exit(1);
    }

    // read particles from file
    fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Can't open file %s!\n", argv[1]);
        exit(1);
    }

    particles_read(fp, *p_DA);
    fclose(fp);

    // print parameters
    printf("N: %d\n", N);
    printf("dt: %f\n", DT);
    printf("steps: %d\n", STEPS);

    const double t_init = get_timer() / 1000.0f;
    printf("Initialization Time: %.3f\n", t_init);

    // run simulation ...
    particles_simulate(*p_DA);

    const double t_computation = (get_timer() / 1000.0f) - t_init;
    printf("Computation Time: %.3f <---\n", t_computation);

    // write particles to file
    fp = fopen(argv[2], "wb");
    if (fp == NULL)
    {
        printf("Can't open file %s!\n", argv[2]);
        exit(1);
    }

    particles_write(fp, *p_DA);

    // free particle's structure
    particles_free(p_DA);
    fclose(fp);

    const double t_write = (get_timer() / 1000.0f) - t_computation - t_init;
    printf("Writing Time: %.3f\n", t_write);

    const double t_final = get_timer() / 1000.0f;
    printf("Final Time: %.3f\n", t_final);

    return 0;
}
