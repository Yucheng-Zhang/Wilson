/* Definition of basic variables */

#include "variables.h"

/* Basic Variables */

const int L = 32; /* Linear size of the lattice */
const int Ns = L * L; /* Total amount of sites of the 2d square lattice */
const int Nb = 2 * Ns; /* Total amount of bonds */

int NN[Ns][4]; /* The number of the four nearest neighbours of the site */

/* Files */

FILE *fp1, *fp2, *fp3, *fp4;

errno_t err1 = fopen_s(&fp1, "wilson_tree.txt", "w");

errno_t err5 = fopen_s(&fp2, "wilson_hittingtimesum_32.txt", "w");

errno_t err7 = fopen_s(&fp3, "wilson_size_time_32.txt", "w");

errno_t err8 = fopen_s(&fp4, "wilson_tau_ratio_32.txt", "w");
