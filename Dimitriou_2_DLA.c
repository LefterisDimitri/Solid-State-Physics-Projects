#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define n 501


int main() {
	FILE *fp;
	fp = fopen("DLA_dim.dat","w");
	FILE *fp1;
	fp1 = fopen("DLA.dat","w");

	int i, j, runs, x, y, p_i, p_j, signal, p_run, m, low1, high1, low2, high2, low3, high3, low4, high4;
	double low, high, r, r1;
	int grid[n][n];


	low = 0.0;
	high = 1.0;
	srand(4399);

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			grid[i][j] = 0;
		}
	}

	m = 250;

	grid[m][m] = 1;


	runs = 10000;

	signal = 1;

	do {
		r1 = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
		if(r1 >= 0.0 && r1 <= 0.25) {
			low1 = 2;
			high1 = m;
			x = low1 + (int) (rand())/((int) (RAND_MAX/(high1 - low1)));
			y = x + high1;
		} else if(r1 > 0.25 && r1 <= 0.5) {
			low2 = m;
			high2 = n-3;
			x = low2 + (int) (rand())/((int) (RAND_MAX/(high2 - low2)));
			y = abs(x - high2) + low2;
		} else if(r1 > 0.5 && r1 <= 0.75) {
			low3 = m;
			high3 = n-3;
			x = low3 + (int) (rand())/((int) (RAND_MAX/(high3 - low3)));
			y = x - low3;
		} else if(r1 > 0.75 && r1 <= 1.0) {
			low4 = 2;
			high4 = m;
			x = low4 + (int) (rand())/((int) (RAND_MAX/(high4 - low4)));
			y = abs(x - high4);
		}

		while(signal == 1) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			if(r>=0.0 && r<=0.25) {
				if((y-1) > 0) {
					y = y - 1;
					if(grid[x][y-1] == 1 || grid[x-1][y] == 1 || grid[x+1][y] == 1) {
						grid[x][y] = 1;
						fprintf(fp1,"%d %d \n", y, x);
						signal = 0;
					}
				}
			} else if (r>0.25 && r<=0.5) {
				if((x+1) < (n-1)) {
					x = x + 1;
					if(grid[x+1][y] == 1 || grid[x][y-1] == 1 || grid[x][y+1] == 1) {
						grid[x][y] = 1;
						fprintf(fp1,"%d %d \n", y, x);
						signal = 0;
					}
				}
			} else if (r>0.5 && r<=0.75) {
				if((y+1) < (n-1)) {
					y = y + 1;
					if(grid[x][y+1] == 1 || grid[x-1][y] == 1 || grid[x+1][y] == 1) {
						grid[x][y] = 1;
						fprintf(fp1,"%d %d \n", y, x);
						signal = 0;
					}
				}
			} else if (r>0.75 && r<=1.0) {
				if((x-1) > 0) {
					x = x - 1;
					if(grid[x-1][y] == 1 || grid[x][y-1] == 1 || grid[x][y+1] == 1) {
						grid[x][y] = 1;
						fprintf(fp1,"%d %d \n", y, x);
						signal = 0;
					}
				}
			}
		}
		signal = 1;
	} while (x+y>250 && x+y<750  && abs(x-y)<250); // bountaries

	int p_1, p_2, N, s;
	s = 0;
	p_1 = m-1; //249; //223;
	p_2 = m+1; //251; //225;
	N = p_2 - p_1 + 1;

	while(N<=101) {
		for(i=p_1; i<=p_2; i++) {
			for(j=p_1; j<=p_2; j++) {
				if(grid[i][j] == 1) {
					s = s + 1;
				}
			}
		}
		fprintf(fp,"%lf %lf  \n", log(N), log(s));
		printf("(N,M) = (%d,%d)  \n", N, s);
		p_1 = p_1 - 1;
		p_2 = p_2 + 1;
		N = p_2 - p_1 + 1;
		s = 0;
	}

	fclose(fp);
	fclose(fp1);
	return 0;
}