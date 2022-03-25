/*******************************************************************************
** particle.h (particle)
*******************************************************************************/

#ifndef PARTICLE_H
#define PARTICLE_H

/* number of bits in mantissa of pos/vel/acc */
#define PARTICLE_MANTISSA 10

typedef struct particle
{
  /* position, velocity, acceleration */
  int             pos_x;
  int             pos_y;
  int             vel_x;
  int             vel_y;
  int             acc_x;
  int             acc_y;

  /* remaining lifetime */
  int             life_count;

  /* color */
  unsigned char   color_r;
  unsigned char   color_g;
  unsigned char   color_b;
} particle;

/* function declarations */
short int particle_init(particle* p);
particle* particle_create();
short int particle_deinit(particle* p);
short int particle_destroy(particle* p);

short int particle_reset(particle* p);

#endif
