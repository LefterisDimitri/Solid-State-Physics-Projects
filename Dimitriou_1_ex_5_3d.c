#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define n 1000
#define N 50


int main() {
	FILE *fp;
	fp = fopen("5_3D.dat","w");
	int i, j, k, runs, x, y, z, p_i, p_j, p_k;
	int digits, firstDigit;
	double position, position_sq, mean_position_sq, s;
	double low, high, num, r, mean, sum[11];
	int grid[N][N][N];


	low = 0.0;
	high = 1.0;

	srand(4399);

	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			for(k=0; k<N; k++) {
				grid[i][j][k] = 0;
			}
		}
	}

	for(i=0; i<=10; i++) {
		sum[i] = 0.0;
	}

	runs = 10000;

	x=25;
	y=25;
	z=25;
	s=0.0;
	for(j=1; j<=runs; j++) {
		for (i=1; i<=n; i++) {
			r = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
			//printf("run = %d \n", j);
			if(r>=0.0 && r<=1.0/6.0) {
				if(y > 0) {
					y = y - 1;
					if(grid[x][y][z] == 0) {
						grid[x][y][z] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>1.0/6.0 && r<=2.0/6.0) {
				if((x+1) < N) {
					x = x + 1;
					if(grid[x][y][z] == 0) {
						grid[x][y][z] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>2.0/6.0 && r<=3.0/6.0) {
				if((y+1) < N) {
					y = y + 1;
					if(grid[x][y][z] == 0) {
						grid[x][y][z] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>3.0/6.0 && r<=4.0/6.0) {
				if(x > 0) {
					x = x - 1;
					if(grid[x][y][z] == 0) {
						grid[x][y][z] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>4.0/6.0 && r<=5.0/6.0) {
				if(z > 0) {
					z = z - 1;
					if(grid[x][y][z] == 0) {
						grid[x][y][z] = 1;
						s = s + 1.0;
					}
				}
			} else if (r>5.0/6.0 && r<=1.0) {
				if((z+1) < N) {
					z = z + 1;
					if(grid[x][y][z] == 0) {
						grid[x][y][z] = 1;
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
		x=25;
		y=25;
		z=25;
		s=0.0;
		for(p_i=0; p_i<N; p_i++) {
			for(p_j=0; p_j<N; p_j++) {
				for(p_k=0; p_k<N; p_k++) {
					grid[p_i][p_j][p_k] = 0;
				}
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


