#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n 1000


int main() {
	FILE *fp;
	fp = fopen("5_1D.dat","w");
	int i, j, runs, x;
	int digits, firstDigit;
	double position, position_sq, mean_position_sq, s;
	double low, high, num, r, mean, sum[11];
	int grid[n+1];


	low = 0.0;
	high = 1.0;

	srand(4399);

	for(i=0; i<=n; i++) {
		grid[i] = 0;
	}

	for(i=0; i<=10; i++) {
		sum[i] = 0.0;
	}

	runs = 10000;
	//position = 0.0;
	x=n/2;
	s=0.0;
	for(j=1; j<=runs; j++) {
		for (i=1; i<=n; i++) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			if(r>=0.5) {
				if((x+1) < n) {
					//position += 1.0;
					x = x + 1;
					if(grid[x] == 0) {
						grid[x] = 1;
						s = s + 1.0;
					}
				}
			} else {
				if(x > 0) {
					//position -= 1.0;
					x = x - 1;
					if(grid[x] == 0) {
						grid[x] = 1;
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
		position = 0.0;
		x=n/2;
		s=0.0;
		for(i=0; i<=n; i++) {
			grid[i] = 0;
		}

	}

	for(i=0; i<=10; i++) {
		mean = sum[i]/runs;
		fprintf(fp,"%d %lf \n", i*100, mean);
	}


	fclose(fp);
	return 0;
}


