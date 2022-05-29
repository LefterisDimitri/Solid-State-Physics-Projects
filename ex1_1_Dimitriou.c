#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	fp = fopen("ex1_1.dat","w");
	int i, n;
	double low, high, r, sum, mean;

	low = 0.0;
	high = 1.0;
	n = 10;

	srand(4399);

	sum = 0.0;
	do {
		for (i=0; i<n; i++) {
			r = low + (double) (rand())/((double) (RAND_MAX/(high - low)));
			sum = sum + r;
		}
		mean = sum/n;
		fprintf(fp,"%d %lf \n", n, mean);
		n *= 10;
		sum = 0.0;
	} while(n<=1000000);

	fclose(fp);

	return 0;
}


