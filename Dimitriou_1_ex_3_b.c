#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n 1000


int main() {
	FILE *fp;
	fp = fopen("ex1_3_b.dat","w");
	int i, j, runs;
	int digits, firstDigit;
	double position_sq, mean_position_sq, x, y;
	double f;
	double low, high, r, sum[n/100 + 1], mean;

	low = 0.0;
	high = 1.0;

	srand(4399);

	for(i=0; i<=10; i++) {
		sum[i] = 0.0;
	}
	runs = 10000;
	x = 0.0;
	y = 0.0;

	for(j=1; j<=runs; j++) {
		for (i=1; i<=n; i++) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			if(r>=0.0 && r<=0.25) {
				y = y + 1;
			} else if (r>0.25 && r<=0.5) {
				x = x + 1;
			} else if (r>0.5 && r<=0.75) {
				y = y - 1;
			} else if (r>0.75 && r<=1) {
				x = x - 1;
			}
			if(i%100 == 0) {
				if(i==1000) {
					firstDigit = 10;
					sum[firstDigit] += x*x + y*y;
				} else {
					digits = (int)log10(i);
					firstDigit = (int)(i / pow(10, digits));
					sum[firstDigit] += x*x + y*y;
				}
			}
		}
		x = 0.0;
		y = 0.0;
	}

	for(i=0; i<=10; i++) {
		mean = sum[i]/runs;
		fprintf(fp,"%d %lf \n", i*100, mean);
	}

	fclose(fp);
	return 0;
}


