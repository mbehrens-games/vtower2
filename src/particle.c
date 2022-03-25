/*******************************************************************************
** particle.c (particle)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "particle.h"

/*******************************************************************************
** particle_init()
*******************************************************************************/
short int particle_init(particle* p)
{
  if (p == NULL)
    return 1;

  p->pos_x      = 0;
  p->pos_y      = 0;
  p->vel_x      = 0;
  p->vel_y      = 0;
  p->acc_x      = 0;
  p->acc_y      = 0;

  p->life_count = 0;

  p->color_r    = 0;
  p->color_g    = 0;
  p->color_b    = 0;

  return 0;
}

/*******************************************************************************
** particle_create()
*******************************************************************************/
particle* particle_create()
{
  particle* p;

  p = malloc(sizeof(particle));
  particle_init(p);

  return p;
}

/*******************************************************************************
** particle_deinit()
*******************************************************************************/
short int particle_deinit(particle* p)
{
  if (p == NULL)
    return 1;

  return 0;
}

/*******************************************************************************
** particle_destroy()
*******************************************************************************/
short int particle_destroy(particle* p)
{
  if (p == NULL)
    return 1;

  particle_deinit(p);
  free(p);

  return 0;
}

/*******************************************************************************
** particle_reset()
*******************************************************************************/
short int particle_reset(particle* p)
{
  if (p == NULL)
    return 1;

  p->pos_x      = 0;
  p->pos_y      = 0;
  p->vel_x      = 0;
  p->vel_y      = 0;
  p->acc_x      = 0;
  p->acc_y      = 0;

  p->life_count = 0;

  p->color_r    = 0;
  p->color_g    = 0;
  p->color_b    = 0;

  return 0;
}

