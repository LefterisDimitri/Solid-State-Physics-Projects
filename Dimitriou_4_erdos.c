#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NR_END 1
#define FREE_ARG char*

#define n 10000

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
	long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
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

	for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

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


int main() {
	FILE *fp;
	fp = fopen("erdos.dat", "w");

	int i, j, runs;
	double low, high, r;

	int **grid;
	grid = imatrix(0,n,0,n);
	//int s[n];
	//int dist[n];
	int *s;
	int *dist;
	s = ivector(0,n);
	dist = ivector(0,n);


	low = 0.0;
	high = 1.0;

	srand((unsigned int) time(NULL));

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			grid[i][j] = 0;
		}
	}
	for(i=0; i<n; i++) {
		s[i] = 0;
		dist[i] = 0;
	}

	for(runs = 1; runs <= 1000; runs++) {
		for(i=0; i<n; i++) {
			for(j=i+1; j<n; j++) {
				r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
				if(r < 1.0/6.0) {
					grid[i][j] = 1;
					grid[j][i] = 1;
				}
			}
		}
		
		for(i=0; i<n; i++)
		{
			for(j=0; j<n; j++)
			{
				if(grid[i][j] == 1)
				{
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
				grid[i][j] = 0;
			}
		}
	}

	for(i=0; i<2000; i++) {
		fprintf(fp,"%d %lf \n", i, dist[i]/1000.0);
	}
	

	fclose(fp);

	return 0;
}