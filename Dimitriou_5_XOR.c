#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NR_END 1
#define FREE_ARG char*


double f(double u) {
	return 1.0/(1.0 + exp(-u));
}

int main() {
	int i, j, p_i;
	double low, high;
	double n;
	

	double x[2];
	x[0] = 0.0;
	x[1] = 0.0;
	

	double A[4][2];
	A[0][0] = 0.0;
	A[1][0] = 0.0;
	A[2][0] = 1.0;
	A[3][0] = 1.0;
	A[0][1] = 0.0;
	A[1][1] = 1.0;
	A[2][1] = 0.0;
	A[3][1] = 1.0;
	
	
	double delta_w[10];
	
	for(i=0; i<10; i++) {
		delta_w[i] = 0.0;
	}
	
	double d[6];
	double U[6];
	double y[6];
	
	for(i=0; i<6; i++)
	{
		d[i] = 0.0;
		U[i] = 0.0;
		y[i] = 0.0;
	}

	low = -1.0;
	high = 1.0;

	srand((unsigned int) time(NULL));

	double w[10];
	w[0] = 0.0;
	w[1] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[2] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[3] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[4] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[5] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[6] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[7] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[8] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	w[9] = low + (float) (rand())/((float) (RAND_MAX/(high - low)));
	
	//for(i=1; i<10; i++)
	//{
	//	printf("w[%d] = %lf \n\n", i, w[i]);
    //}
	
	double output[4];

	output[0] = 0.0;
	output[1] = 0.0;
	output[2] = 0.0;
	output[3] = 0.0;
	
	double GT[4];

	GT[0] = 0.0;
	GT[1] = 1.0;
	GT[2] = 1.0;
	GT[3] = 0.0;

	double error[4];
	for(i=0; i<4; i++) {
		error[i] = 0.0;
	}
	
	n = 0.2;

	int epoch = 0;
	while(epoch <= 10000) {
		for(i=0; i<4; i++) {
			for(j=0; j<2; j++) {
				x[j] = A[i][j];
				//U[4] = U[4] + w[j+j]*x[j];
				//U[3] = U[3] + w[j+j+1]*x[j];
			}		
			
			//U[4] = U[4] + w[4];
			//U[3] = U[3] + w[5];
			
			y[1] = x[0];
			y[2] = x[1];
			
			U[4] = w[1]*y[1] + w[3]*y[2] + w[5];
			U[3] = w[2]*y[1] + w[4]*y[2] + w[6];
			
			y[4] = f(U[4]);
			y[3] = f(U[3]);

			U[5] = w[7]*y[4] + w[8]*y[3] + w[9];

			y[5] = f(U[5]);

			error[i] = 0.5*(y[5] - GT[i])*(y[5] - GT[i]);

			if(error[i] < 0.01) 
			{
				output[i] = y[5];
			} 
			else 
			{			
				// ---------- Back-propagation ---------- //

				d[5] = y[5]*(1.0 - y[5])*(GT[i] - y[5]);
				d[4] = y[4]*(1.0 - y[4])*d[5]*w[7];
				d[3] = y[3]*(1.0 - y[3])*d[5]*w[8];
				d[2] = y[2]*(1.0 - y[2])*(d[4]*w[3] + d[3]*w[4]);
				d[1] = y[1]*(1.0 - y[1])*(d[4]*w[1] + d[3]*w[2]);


				delta_w[1] = n*d[4]*y[1];
				delta_w[2] = n*d[3]*y[1];
				delta_w[3] = n*d[4]*y[2];
				delta_w[4] = n*d[3]*y[2];
				delta_w[5] = n*d[4];
				delta_w[6] = n*d[3];
				delta_w[7] = n*d[5]*y[4];
				delta_w[8] = n*d[5]*y[3];
				delta_w[9] = n*d[5];

				for(p_i=1; p_i<10; p_i++) {
					w[p_i] = w[p_i] + delta_w[p_i];
				}
			}
			
		}		
		if(error[0] < 0.01 && error[1] < 0.01 && error[2] < 0.01 && error[3] < 0.01)
		{
			printf("\nout\n");
			break;
		}
		epoch ++ ;
	}

	for(i=0; i<4; i++) {
		printf("%.10lf \n", output[i]);
	}
	
	printf("\n");
	for(i=0; i<10; i++) {
		printf("w[%d] = %.10lf \n", i, w[i]);
	}

	return 0;
}





