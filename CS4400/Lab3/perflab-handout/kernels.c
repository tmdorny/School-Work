/*******************************************
 * Solutions for the CS:APP Performance Lab
 ********************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following student struct 
 */
student_t student = {
  "Tim Dorny",     /* Full name */
  "u0829896@utah.edu",  /* Email address */

};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_pinwheel - The naive baseline version of pinwheel 
 */
char naive_pinwheel_descr[] = "naive_pinwheel: Naive baseline implementation";
void naive_pinwheel(int dim, pixel *src, pixel *dest)
{
  int i, j;

  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim/2 - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
    
  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim/2 - 1 - j, dim/2 + i, dim)] = src[RIDX(i, dim/2 + j, dim)];

  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim - 1 - j, i, dim)] = src[RIDX(dim/2 + i, j, dim)];

  for (i = 0; i < dim/2; i++)
    for (j = 0; j < dim/2; j++)
      dest[RIDX(dim - 1 - j, dim/2 + i, dim)] = src[RIDX(dim/2 + i, dim/2 + j, dim)];
}

/* 
 * rotate - Your current working version of pinwheel
 * IMPORTANT: This is the version you will be graded on
 */
char pinwheel_descr[] = "pinwheel: Current working version";
void pinwheel(int dim, pixel *src, pixel *dest)
{
  int i, j;
  int dum = dim >> 1;

  for (j = 0; j < dum; j++)
    for (i = 0; i < dum; i++)
      dest[RIDX(dum - 1 - j, i, dim)] = src[RIDX(i, j, dim)];

  for (j = 0; j < dum; j++)
    for (i = 0; i < dum; i++)
      dest[RIDX(dum - 1 - j, dum + i, dim)] = src[RIDX(i, dum + j, dim)];

  for (j = 0; j < dum; j++)
    for (i = 0; i < dum; i++)
      dest[RIDX(dim - 1 - j, i, dim)] = src[RIDX(dum + i, j, dim)];

  for (j = 0; j < dum; j++)
    for (i = 0; i < dum; i++)
      dest[RIDX(dim - 1 - j, dum + i, dim)] = src[RIDX(dum + i, dum + j, dim)];
}

/*********************************************************************
 * register_pinwheel_functions - Register all of your different versions
 *     of the pinwheel kernel with the driver by calling the
 *     add_pinwheel_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_pinwheel_functions() {
  add_pinwheel_function(&pinwheel, pinwheel_descr);
  add_pinwheel_function(&naive_pinwheel, naive_pinwheel_descr);
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
} pixel_sum;

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
  sum->red = sum->green = sum->blue = 0;
  return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_weighted_sum(pixel_sum *sum, pixel p, double weight) 
{
  sum->red += (int) p.red * weight;
  sum->green += (int) p.green * weight;
  sum->blue += (int) p.blue * weight;
  return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
  current_pixel->red = (unsigned short)sum.red;
  current_pixel->green = (unsigned short)sum.green;
  current_pixel->blue = (unsigned short)sum.blue;
  return;
}

/* 
 * weighted_combo - Returns new pixel value at (i,j) 
 */
static pixel weighted_combo(int dim, int i, int j, pixel *src) 
{
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;
  double weights[3][3] = { { 0.50, 0.03125, 0.00 },
                           { 0.03125, 0.25, 0.03125 },
                           { 0.00, 0.03125, 0.125 } };

  initialize_pixel_sum(&sum);
  for(ii=0; ii < 3; ii++)
    for(jj=0; jj < 3; jj++) 
      if ((i + ii < dim) && (j + jj < dim))
        accumulate_weighted_sum(&sum,
                                src[RIDX(i+ii,j+jj,dim)],
                                weights[ii][jj]);
    
  assign_sum_to_pixel(&current_pixel, sum);
 
  return current_pixel;
}


/******************************************************
 * Your different versions of the motion kernel go here
 ******************************************************/

/*
 * naive_motion - The naive baseline version of motion 
 */
char naive_motion_descr[] = "naive_motion: Naive baseline implementation";
void naive_motion(int dim, pixel *src, pixel *dst) 
{
  int i, j;
    
  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = weighted_combo(dim, i, j, src);
}


/*
 * motion - Your current working version of motion.
 * IMPORTANT: This is the version you will be graded on
 */
char motion_descr[] = "motion: Current working version";
void motion(int dim, pixel *src, pixel *dst)
{
  int i, j;
  for (j = 0; j < dim; j++)
    for (i = 0; i < dim; i++){
      int ii, jj;
      pixel_sum sum;
      pixel current_pixel;

      sum.red = sum.green = sum.blue = 0;
      for(ii=0; ii < 3; ii++)
        for(jj=0; jj < 3; jj++)
          if ((i + ii < dim) && (j + jj < dim)){
            // Replace array access and multiplication with bitshifting and if statements
            if (ii + jj == 0){
            sum.red += (int) src[RIDX(i+ii,j+jj,dim)].red >> 1;
            sum.green += (int) src[RIDX(i+ii,j+jj,dim)].green >> 1;
            sum.blue += (int) src[RIDX(i+ii,j+jj,dim)].blue >> 1;
            }

            else if (ii + jj == 1 || ii + jj == 3){
            sum.red += (int) src[RIDX(i+ii,j+jj,dim)].red >> 5;
            sum.green += (int) src[RIDX(i+ii,j+jj,dim)].green >> 5;
            sum.blue += (int) src[RIDX(i+ii,j+jj,dim)].blue >> 5;
            }

            else if (ii && jj == 1){
            sum.red += (int) src[RIDX(i+ii,j+jj,dim)].red >> 2;
            sum.green += (int) src[RIDX(i+ii,j+jj,dim)].green >> 2;
            sum.blue += (int) src[RIDX(i+ii,j+jj,dim)].blue >> 2;
            }

            else if (ii + jj == 4){
            sum.red += (int) src[RIDX(i+ii,j+jj,dim)].red >> 3;
            sum.green += (int) src[RIDX(i+ii,j+jj,dim)].green >> 3;
            sum.blue += (int) src[RIDX(i+ii,j+jj,dim)].blue >> 3;
            }
          }
      current_pixel.red = (unsigned short)sum.red;
      current_pixel.green = (unsigned short)sum.green;
      current_pixel.blue = (unsigned short)sum.blue;

      dst[RIDX(i, j, dim)] = current_pixel;
}
}

/********************************************************************* 
 * register_motion_functions - Register all of your different versions
 *     of the motion kernel with the driver by calling the
 *     add_motion_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_motion_functions() {
  add_motion_function(&motion, motion_descr);
  add_motion_function(&naive_motion, naive_motion_descr);
}
