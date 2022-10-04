#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NR_END 1
#define FREE_ARG char*

#define n 1000


int main() {
	
	FILE *fp;
	fp = fopen("free_scale.dat", "w");
	int i;
	int s[n];
	int dist[n];

	for(i=0; i<n; i++) {
		s[i] = 0;
		dist[i] = 0;
	}

	double gamma;
	double ymin, ymax, y;
	double x;
	
	ymax = n - 1.0;
	ymin = 1.0;
	gamma = 3.0;

	srand((unsigned int) time(NULL));

	double low, high;
	low = 0.0;
	high = 1.0;

    int runs;
	for(runs = 1; runs <= 1000; runs ++) {
		
		for(i=0; i<n; i++) {
			x = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			y = (pow(ymax,1-gamma) - pow(ymin,1-gamma))*x + pow(ymin,1-gamma);
			s[i] = pow(y,1.0/(1.0-gamma));
		}
		
		for(i=0; i<n; i++) {
			dist[s[i]] = dist[s[i]] + 1;
		}
		
		for(i=0; i<n; i++) {
			s[i] = 0;
		}
		
	}
	
	for(i=1; i<n; i++) {
		if(dist[i] != 0.0)
		{
			fprintf(fp,"%lf %lf \n", log(i), log(dist[i]/1000.0));
		}
		
	}
	
	fclose(fp);


	return 0;
}





