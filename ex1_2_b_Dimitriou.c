#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// 2D random walk

int main() {
	int i, j, n, runs;
	double position_sq, mean_position_sq, x, y;
	double low, high, r, sum;

	low = 0.0;
	high = 1.0;
	n = 1000;

	srand(4399);

	sum = 0.0;
	runs = 10000;    // number of experiments
	x = 0.0;
	y = 0.0;
	for(j=1; j<=runs; j++) {
		for (i=0; i<n; i++) {
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
		}
		position_sq = x*x + y*y;
		sum = sum + position_sq;
		
		// return to position = 0 for the new experiment
		x = 0.0;
		y = 0.0;
	}
	
	// mean R^2 for all the runs
	mean_position_sq = sum/runs; 
	printf("The mean value of the R^2 is <R^2> = %lf", mean_position_sq);

	return 0;
}


