#pragma once
/* Declaration of basic variables */

#include <stdio.h>

/* Basic Variables */

extern const int L; /* Linear size of the lattice */
extern const int Ns; /* Total amount of sites of the 2d square lattice */
extern const int Nb; /* Total amount of bonds */

extern int NN[][4]; /* The number of the four nearest neighbours of the site */

/* Files */
extern FILE *fp1, *fp2, *fp3, *fp4;
