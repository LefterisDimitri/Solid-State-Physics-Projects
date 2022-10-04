#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NR_END 1
#define FREE_ARG char*

#define n 1000

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

int main() {
	FILE *fp;
	fp = fopen("small_world.dat", "w");

	int i, j, l, k, runs;
	int p_i, p_j;
	double low, high, r;

	int **grid;
	grid = imatrix(0,n,0,n);

	int s[n];
	int dist[n];

	low = 0.0;
	high = 1.0;

	k = 7;

	srand((unsigned int) time(NULL));

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			grid[i][j] = 1;
		}
	}

	for(i=0; i<n; i++) {
		s[i] = 0;
	}

	for(i=0; i<n; i++) {
		dist[i] = 0;
	}

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			if((abs(i-j) >=  k+1 && abs(i-j) <= n-(k+1)) || abs(i-j) == 0) {
				grid[i][j] = 0;
			}
		}
	}


	int signal;

	for(runs=1; runs<=1000; runs++) {
		for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
				if(grid[i][j] == 1) {
					r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
					if(r<=0.2) {
						grid[i][j] = 0;
						grid[j][i] = 0;
						signal = 0;
						while(signal == 0) {
							p_j = rand() % n;
							if(grid[i][p_j] == 0 && abs(i-p_j) > 0 && abs(j-p_j) > 0) {
								grid[i][p_j] = 1;
								grid[p_j][i] = 1;
								signal = 1;
							}
						}
					}
				}
			}
		}

		for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
				if(grid[i][j] == 1) {
					s[i] += 1;
				}
			}
		}

		for(i=0; i<n; i++) {
			dist[s[i]] = dist[s[i]] + 1;
		}

		for(i=0; i<n; i++) {
			s[i] = 0;
		}

		for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
				grid[i][j] = 1;
			}
		}

		for(i=0; i<n; i++) {
			for(j=0; j<n; j++) {
				if((abs(i-j) >=  k+1 && abs(i-j) <= n-(k+1)) || abs(i-j) == 0) {
					grid[i][j] = 0;
				}
			}
		}

	}
	
	for(i=0; i<30; i++) {
		fprintf(fp,"%d %lf \n", i, dist[i]/1000.0);
	}

	fclose(fp);

	return 0;
}









/*if(r<0.2) {
			p_j = rand() % n;
			signal = 0;
			while(signal == 0) {
				if(grid[i][j] != 0) {
					if(grid[i][p_j] == 0) {
						grid[i][p_j] = 1;
						signal = 1;
					} else {
						p_j = rand() % n;
					}
				} else {
					j++;
				}
			}
		}*/


/*p_i = rand() % n;
p_j = rand() % n;
int signal1 = 0;
while(signal1 == 0)
{
	if(grid[p_i][p_j] == 1)
	{
		r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
		if(r<0.2)
		{
			p_jn = rand() % n;
			signal = 0;
			while(signal == 0)
			{
				if(grid[p_i][p_jn] == 0)
				{
					grid[p_i][p_jn] = 1;
					grid[p_i][p_j] == 0;
					grid[p_jn][p_i] = 1;
					grid[p_j][p_i] == 0;
					signal = 1;
				}
				else
				{
					p_jn = rand() % n;
				}
			}
		}
		signal1 = 1;
	}
	else
	{
		p_j = rand() % n;
	}
} */