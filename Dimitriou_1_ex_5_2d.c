#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 1000
#define n 500


int main() {
	FILE *fp;
	fp = fopen("5_2D.dat","w");
	int i, j, runs, x, y, p_i, p_j;
	int digits, firstDigit;
	double position, position_sq, mean_position_sq, s;
	double low, high, num, r, mean, sum[11];
	int grid[n][n];

	low = 0.0;
	high = 1.0;

	srand(4399);

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			grid[i][j] = 0;
		}
	}

	for(i=0; i<=10; i++) {
		sum[i] = 0.0;
	}

	runs = 10000;

	x=n/2-1;
	y=n/2-1;
	s=0.0;
	for(j=1; j<=runs; j++) {
		for (i=1; i<=N; i++) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			if(r>=0.0 && r<=0.25) {
				if(y > 0) {
					y = y - 1;
					if(grid[x][y] == 0) {
						grid[x][y] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>0.25 && r<=0.5) {
				if((x+1) < n) {
					x = x + 1;
					if(grid[x][y] == 0) {
						grid[x][y] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>0.5 && r<=0.75) {
				if((y+1) < n) {
					y = y + 1;
					if(grid[x][y] == 0) {
						grid[x][y] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>0.75 && r<=1) {
				if(x > 0) {
					x = x - 1;
					if(grid[x][y] == 0) {
						grid[x][y] = 1;
						s = s + 1.0;
					}
				}
			}
			if(i%100 == 0) {
				if(i==1000) {
					firstDigit = 10;
					sum[firstDigit] += s;
				} else {
					digits = (int)log10(i);
					firstDigit = (int)(i / pow(10, digits));
					sum[firstDigit] += s;
				}
			}

		}
		x=n/2-1;
		y=n/2-1;
		s=0.0;
		for(p_i=0; p_i<n; p_i++) {
			for(p_j=0; p_j<n; p_j++) {
				grid[p_i][p_j] = 0;
			}
		}

	}

	for(i=0; i<=10; i++) {
		mean = sum[i]/runs;
		fprintf(fp,"%d %lf \n", i*100, mean);
	}


	fclose(fp);
	return 0;
}


