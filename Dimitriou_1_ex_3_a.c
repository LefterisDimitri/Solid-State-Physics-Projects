#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n 1000


int main() {
	FILE *fp;
	fp = fopen("ex1_3_a.dat","w");
	int i, j, runs;
	int digits, firstDigit;
	double position, position_sq, mean_position_sq;
	double low, high, r, sum[n/100 + 1], mean;

	low = 0.0;
	high = 1.0;

	srand(4399);

	for(i=0; i<=10; i++) {
		sum[i] = 0.0;
	}

	runs = 10000;
	position = 0.0;

	for(j=1; j<=runs; j++) {
		for (i=1; i<=n; i++) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			if(r>=0.5) {
				position += 1.0;
			} else {
				position -= 1.0;
			}
			if(i%100 == 0) {
				if(i==1000) {
					firstDigit = 10;
					sum[firstDigit] += position*position;
				} else {
					digits = (int)log10(i);
					firstDigit = (int)(i / pow(10, digits));
					sum[firstDigit] += position*position;
				}
			}
		}
		position = 0.0;
	}

	for(i=0; i<=10; i++) {
		mean = sum[i]/runs;
		fprintf(fp,"%d %lf \n", i*100, mean);
	}

	fclose(fp);
	return 0;
}


