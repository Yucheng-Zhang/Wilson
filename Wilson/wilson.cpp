/* Wilson Algorithm for Spanning Trees */
/* Loop-erased random walk */
/* Two dimensional square lattice */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rdng.h"
#include "wilson.h"
#include "variables.h"

/* Calculate the N.N. with Periodic Boundary Condition */
void CalNN()
{
	for (int i = 0; i < Ns; i++) {
		NN[i][0] = (i + 1) % L + (i / L) * L; /* right */
		NN[i][1] = (i - 1 + L) % L + (i / L) * L; /* left */
		NN[i][2] = (i + L) % (L * L); /* up */
		NN[i][3] = (i - L + L * L) % (L * L); /* down */
	}
}

/* Choose the next site to walk to */
int RandomSuccessor(int u)
{
	int r = int(Random() * 4); /* four n.n. on square lattice */
	return NN[u][r];
}

/* Variables used in the algorithm */

bool *InTree; /* Array InTree[Ns]. Whether the site is in the tree or not */
int *Next; /* Array Next[Ns] The next site of the current site */

int *OrderSites; /* Array OrderSites[Ns]. Random array of sites created at the beginning */

int HittingTimeSum; /* Sum of hitting time, i.e., the total steps of random walk */

static double *TimeSize; /* Time ~ Size */

static int TreeSize;

static int tau; /* first hitting time */

/* Dynamic Memory Allocation */
void WDMA()
{
	InTree = (bool *)malloc(Ns * sizeof(bool));
	Next = (int *)malloc(Ns * sizeof(int));
	OrderSites = (int *)malloc(Ns * sizeof(int));
	TimeSize = (double *)malloc(Ns * sizeof(double));
}

/* Create a random array of sites at the beginning */
void CreateSitesOrder()
{
	for (int i = 0; i < Ns; i++) {
		OrderSites[i] = i;
	}
	int j, temp;
	for (int i = 0; i < Ns; i++) {
		j = i + int((Ns - i)*Random());
		temp = OrderSites[i];
		OrderSites[i] = OrderSites[j];
		OrderSites[j] = temp;
	}
}

/* Loop-Erased Random Walk */
int LoopEraRanWalk(int leaf) /* leaf is the beginning site of the random walk */
{
	int PathLength = 0;
	int u = leaf;
	while (true) {
		if (InTree[u]) break;
		Next[u] = RandomSuccessor(u);
		u = Next[u]; /* Automatically loop-erased */
		HittingTimeSum++;
	}
	u = leaf;
	while (true) {
		if (InTree[u]) break;
		InTree[u] = true;
		u = Next[u];
		PathLength++;
	}
	return PathLength;
}

/* Random Tree With Root */
void RanTreeWithRoot(int root, int ntrees)
{
	/* Initialize the data */
	for (int i = 0; i < Ns; i++) {
		InTree[i] = false;
	}
	InTree[root] = true;
	Next[root] = root;
	HittingTimeSum = 0;
	TreeSize = 1;
	tau = 0;
	/* Choose the leaf and start the walk */
	for (int i = 0; i < Ns; i++) {
		if (!InTree[OrderSites[i]]) {
			int temp1 = TreeSize;
			int temp2 = HittingTimeSum;
			TreeSize += LoopEraRanWalk(OrderSites[i]);
			if (temp1 == 1) tau = HittingTimeSum;
			for (int i = temp1 - 1; i < TreeSize - 1; i++) {
				TimeSize[i] += double(temp2) / ntrees;
			}
		}
	}
	TimeSize[TreeSize - 1] += double(HittingTimeSum) / ntrees;
}

/* Output the tree */
void OutputWTree(int n, int root)
{
	fprintf(fp1, "Tree No. %d, root = %d\n", n + 1, root);
	for (int i = 0; i < Ns; i++) {
		fprintf(fp1, "%d %d\n", i, Next[i]);
	}
}

/* Wilson Algorithm */
void Wilson(int ntrees)
{
	/* Preparation */
	WDMA();
	CalNN();
	CreateSitesOrder();
	for (int i = 0; i < Ns; i++) {
		TimeSize[i] = 0;
	}
	/* Wilson algorithm with random walk */
	for (int i = 0; i < ntrees; i++) {
		int root = int(Random() * Ns); /* Choose the random root uniformly */
		RanTreeWithRoot(root, ntrees);
		fprintf(fp2, "%d\n", HittingTimeSum);
		//		OutputWTree(i, root);
		fprintf(fp4, "%d %lf\n", tau, double(tau) / HittingTimeSum);
	}
	for (int i = 0; i < Ns; i++) {
		fprintf(fp3, "%lf %d\n", TimeSize[i], i + 1);
	}
}

/* Calculate the length of path between two vertexs */
//int PathLength(int x, int y)
//{
//	int length = 0;
//
//}
