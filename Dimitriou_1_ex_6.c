#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NR_END 1
#define FREE_ARG char*

#define n 500
#define num_of_particles 100000
#define runs 100000
#define traps 2500

void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
	fprintf(stderr,"Numerical Recipes run-time error...\n");
	fprintf(stderr,"%s\n",error_text);
	fprintf(stderr,"...now exiting to system...\n");
	exit(1);
}


int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
	long q, nrow=nrh-nrl+1,ncol=nch-ncl+1;
	int **m;

	/* allocate pointers to rows */
	m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
	if (!m) nrerror("allocation failure 1 in matrix()");
	m += NR_END;
	m -= nrl;


	/* allocate rows and set pointers to them */
	m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
	if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
	m[nrl] += NR_END;
	m[nrl] -= ncl;

	for(q=nrl+1; q<=nrh; q++) m[q]=m[q-1]+ncol;

	/* return pointer to array of pointers to rows */
	return m;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
	int *v;

	v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
	if (!v) nrerror("allocation failure in ivector()");
	return v-nl+NR_END;
}

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
	double *v;

	v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
	if (!v) nrerror("allocation failure in dvector()");
	return v-nl+NR_END;
}


int main() {
	FILE *fp;
	FILE *fp1;
	fp = fopen("6_trap.dat","w");
	fp1 = fopen("6_non_trap.dat", "w");
	int i, j, x, y, sum_of_traps, t, p_i, p_j, signal, N, N_max, tmax;
	double low, high, r, pr_of_s;

	int **grid;
	grid = imatrix(0,n,0,n);

	int *T;
	T = ivector(0,num_of_particles);

	double *sum;
	sum = dvector(0,num_of_particles);

	N_max = 1;

	for(i=0; i<num_of_particles; i++) {
		sum[t] = 0.0;
		T[i] = 0;
	}

	low = 0.0;
	high = 1.0;
	srand((unsigned int) time(NULL));

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			grid[i][j] = 0;
		}
	}

	sum_of_traps = 0;

	while(sum_of_traps<traps) {
		p_i = rand() % n;
		p_j = rand() % n;

		if (grid[p_i][p_j] == 0) {
			grid[p_i][p_j] = -1;
			sum_of_traps = sum_of_traps + 1;
		}
		if (grid[n/2 - 1][n/1 - 1] == -1) {
			grid[n/2 - 1][n/2 - 1] = 0;
			sum_of_traps = sum_of_traps - 1;
		}
	}
	//printf("traps = %d", sum_of_traps);

	t = 0;
	tmax = 1;
	x = n/2 - 1;
	y = n/2 - 1;
	signal = 1;
	T[0] = num_of_particles; // trapping time matrix

	for(j=1; j<=runs; j++) {
		while(signal == 1) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			t = t + 1;
			if(r>=0.0 && r<=0.25) {
				if((y-1) > 0) {
					y = y - 1;
					if (grid[x][y] == -1) {
						T[t] = T[t] + 1;
						signal = 0;
					}
				}
			} else if (r>0.25 && r<=0.5) {
				if((x+1) < n) {
					x = x + 1;
					if (grid[x][y] == -1) {
						T[t] = T[t] + 1;
						signal = 0;
					}
				}
			} else if (r>0.5 && r<=0.75) {
				if((y+1) < n) {
					y = y + 1;
					if (grid[x][y] == -1) {
						T[t] = T[t] + 1;
						signal = 0;
					}
				}
			} else if (r>0.75 && r<=1) {
				if((x-1) > 0) {
					x = x - 1;
					if (grid[x][y] == -1) {
						T[t] = T[t] + 1;
						signal = 0;
					}
				}
			}
			if(grid[x][y] == 0) {
				N = t;
				sum[t] = sum[t] + 1.0;
				if(N>N_max) {
					N_max = N;
				}
			}
		}

		signal = 1;

		if(t>tmax) {
			tmax = t;
		}

		// ---------- initialization for the next run ---------- //
		t = 0;
		x = n/2 - 1;
		y = n/2 - 1;
		sum_of_traps = 0;
		for(p_i=0; p_i<n; p_i++) {
			for(p_j=0; p_j<n; p_j++) {
				grid[p_i][p_j] = 0;
			}
		}

		while(sum_of_traps<traps) {
			p_i = rand() % n;
			p_j = rand() % n;
			if (grid[p_i][p_j] == 0) {
				grid[p_i][p_j] = -1;
				sum_of_traps = sum_of_traps + 1;
			}
			if (grid[n/2 - 1][n/2 - 1] == -1) {
				grid[n/2 - 1][n/2 - 1] = 0;
				sum_of_traps = sum_of_traps - 1;
			}
		}
		// ---------------------------------------------------------- //
	}

	for(i=0; i<tmax; i++) {
		fprintf(fp,"%d %lf \n", i, T[i]/100000.0);
	}

	for(t=0; t<N_max; t++) {
		pr_of_s = sum[t]/runs;
		fprintf(fp1,"%d %lf \n", t, pr_of_s);
	}

	fclose(fp);
	fclose(fp1);

	return 0;
}