/**
* @file nbody.h
*
* N-Body Simuluation
* Kernel of particles simulation program
*
* @author: Dominik Simek <xsimek23@stud.fit.vutbr.cz
*
*/

#ifndef __NBODY_H__
#define __NBODY_H__

#include <cstdlib>
#include <cstdio>

// gravitational constant
#define G 6.67384e-11f

// particle's structure
typedef struct
{
    float *pos_x;
    float *pos_y;
    float *pos_z;
    float *vel_x;
    float *vel_y;
    float *vel_z;
    float *weight;
    float *fx;
    float *fy;
    float *fz;
    float *ax;
    float *ay;
    float *az;
} t_particles_DA;

// prototypes of functions 
t_particles_DA *particles_alloc(size_t size);

void particles_free(t_particles_DA *p);

void particles_init(t_particles_DA p);

void particles_simulate(t_particles_DA p);

void particles_read(FILE *fp, t_particles_DA p);

void particles_write(FILE *fp, t_particles_DA p);

#endif /* __NBODY_H__ */
