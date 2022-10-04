#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	fp = fopen("4_a.dat","w");
	FILE *fp1;
	fp1 = fopen("4_b.dat","w");

	int i, j, runs, n;
	int digits, firstDigit;
	double position, position_sq, mean_position_sq;
	double f;
	double low, high, num, r, dist[100000], mean;

	low = 0.0;
	high = 1.0;

	srand(4399);

	runs = 100000;

	for (n=1000; n<=2000; n += 1000) {
		for(i=0; i<=runs; i++) {
			dist[i] = 0.0;
		}
		position = 0.0;
		for(j=0; j<runs; j++) {
			for (i=1; i<=n; i++) {
				r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
				if(r>=0.5) {
					position += 1.0;
				} else {
					position -= 1.0;
				}
			}
			dist[j] = position;
			if(n==1000) {
				fprintf(fp,"%lf \n", dist[j]);
			} else {
				fprintf(fp1,"%lf \n", dist[j]);
			}
			position = 0.0;
		}
	}


	fclose(fp);
	fclose(fp1);
	return 0;
}


