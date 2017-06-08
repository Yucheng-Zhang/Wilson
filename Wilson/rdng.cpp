/* Shuffled Random Number Generator, [0, 1] */
#include <stdio.h>
#include <math.h>
#include "rdng.h"

int rdn_I;
const int rdn_list_len = 100;
double rdn_list[100];
double rdn_y;

void set_seed(int Iseed)
{
	rdn_I = abs(Iseed);
	printf_s(":: Setting seed completed.\n");
	init_list();
}

/* Linear congruential generator */
double rndm1()
{
	const int a = 16807, q = 127773, r = 2836, m = 2147483647;
	rdn_I = a * (rdn_I % q) - r * (rdn_I / q);
	if (rdn_I < 0) rdn_I += m;
	return double(rdn_I) / m;
}

/* Initialize the rdn_list and rdn_y, using congruential generator */
void init_list()
{
	for (int i = 0; i < rdn_list_len; i++)
	{
		rdn_list[i] = rndm1();
	}
	rdn_y = rndm1();
	printf_s(":: Initializing Shuffled Random Number Generator completed.\n");
}

/* Output a random number, update the rdn_y and rdn_list */
double Random()
{
	int k;
	double ran;
	k = int(rdn_y * rdn_list_len);
	ran = rdn_list[k];
	rdn_y = rdn_list[k];
	rdn_list[k] = rndm1();
	return ran;
}
