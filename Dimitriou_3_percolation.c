#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define NR_END 1
#define FREE_ARG char*

#define n 500
#define dim 60000         // dimensions for L and S
#define dim1 30
//#define dim_s 340000


int main() {
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4;
	FILE *fp5;
	fp = fopen("P_max.dat", "w");
	fp1 = fopen("num_of_1.dat", "w");
	fp2 = fopen("P_Iav.dat", "w");
	fp3 = fopen("P_Iav_dot.dat", "w");
	fp4 = fopen("exp_P_max.dat", "w");
	fp5 = fopen("exp_Iav.dat", "w");

	int i, j, p_i, p_j, l, num_of_experiments;
	int k, S_max, L_max;
	double sum_of_traps, num_of_1;
	double P, Pmax, I_av, dot_Iav;

	int grid[n][n];
	int L[dim];
	int S[dim];
	double P_max[dim1];
	double Iav[dim1];
	double dotIav[dim1];

	double P_matrix[dim1];

	for(i=0; i<dim1; i++) {
		P_matrix[i] = 0.0;
	}
	for(i=1; i<dim1-2; i++) {
		P_matrix[i] = P_matrix[i-1] + 0.1;

		if(P_matrix[i-1] >= 0.5 && P_matrix[i-1] <= 0.7) {
			P_matrix[i] = P_matrix[i-1] + 0.01;
		}
	}

	for(j=0; j<dim1; j++) {
		P_max[j] = 0.0;
		Iav[j] = 0.0;
		dotIav[j] = 0.0;
	}
	//int S_new[dim];
	//int s[dim_s];


	/*for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			grid[i][j] = 0;
		}
	}*/

	srand((unsigned int) time(NULL));

	int q = 0;

	double step;
	step = 0.10;
	for(num_of_experiments = 1; num_of_experiments <= 100; num_of_experiments ++) {
		q = 0;
		for(P=0.100; P<=1.0; P = P + step) {
			q = q + 1;
			if(P >= 0.500 && P <= 0.700) {
				step = 0.01;
			} else {
				step = 0.100;
			}

			for(i=0; i<n; i++) {
				for(j=0; j<n; j++) {
					grid[i][j] = 0;
				}
			}

			sum_of_traps = 0;
			num_of_1 = P*n*n;

			while(sum_of_traps<num_of_1) {
				p_i = 1 + abs((rand() % n) - 1); //rand() % n;
				p_j = 1 + abs((rand() % n) - 1); //rand() % n;

				if (grid[p_i][p_j] == 0) {
					grid[p_i][p_j] = 1;
					sum_of_traps = sum_of_traps + 1;
				}
				/*if(grid[0][p_j] == 1 || grid[p_i][0] == 1) {
					grid[p_i][p_j] = 0;
					sum_of_traps = sum_of_traps - 1;
				}*/
			}

			/*for(i=0; i<n; i++) {
				grid[i][0] = 0;
			}

			for(j=0; j<n; j++) {
				grid[0][j] = 0;
			} */

			int sum1 = 0;
			for (i=0; i<n; i++) {
				for (j=0; j<n; j++) {
					sum1 = sum1 + grid[i][j];
				}
			}

			//fprintf(fp1,"%d %lf \n", sum1, num_of_1);
			//printf("%d %lf \n", sum1, num_of_1);

			for(j=0; j<dim; j++) {
				L[j] = 0;
				S[j] = 0;
				//S_new[j] = 0;
				//s[j] = 0;
			}
			/*for(j=0; j<dim_s; j++)
			{
				s[j] = 0;
			} */


			k = 1;

			for(j=1; j<n; j++) {
				for(i=1; i<n; i++) {
					if(grid[i][j] != 0) { // Is the index of site i equal to 0 : NO
						if(grid[i][j-1] != 0) { // Is the index of site left to i equal to 0 : NO
							grid[i][j] = L[grid[i][j-1]]; // step 1
							S[L[grid[i][j]]] += 1;       // step 2
							if(grid[i-1][j] != 0 && grid[i-1][j] != L[grid[i][j-1]]) { // Is the index of site above i equal to 0 : NO
								for(l=0; l<dim; l++) {
									if(L[l] == grid[i-1][j]) {
										L[l] = L[grid[i][j-1]];
									}
								}
								S[L[grid[i][j-1]]] = S[L[grid[i][j-1]]] + S[grid[i-1][j]]; // step 2
								S[grid[i-1][j]] = 0; // step 3
							}
						} else if(grid[i][j-1] == 0) { // Is the index of site left to i equal to 0 : YES
							if(grid[i-1][j] != 0) { // Is the index of site above i equal to 0 : NO
								grid[i][j] = L[grid[i-1][j]];
								S[L[grid[i][j]]] += 1;
							} else if(grid[i-1][j] == 0) { // Is the index of site above i equal to 0 : YES
								L[k] = k;
								grid[i][j] = L[k];
								S[L[grid[i][j]]] += 1;
								k = k + 1;
							}
						}
					}
				}
			}
			/*for(j=1; j<n; j++) {
				for(i=1; i<n; i++) {
					if(grid[i][j] != 0) {
						grid[i][j] = L[grid[i][j]];
						//S_new[L[grid[i][j]]] += 1;
					}
				}
			}*/

			L_max = 0;

			for(i=1; i<dim; i++) {
				if(L[i] > L_max) {
					L_max = L[i];
				}
			}

			fprintf(fp1,"for k = %d : L_max = %d \n", k, L_max);



			S_max = 0;
			for(i=0; i<dim; i++) {
				if(S[i] > S_max) {
					S_max = S[i];
				}
			}

			//	printf("S_max = %d \n", S_max);

			Pmax = S_max/(P*n*n);
			P_max[q] += Pmax;
			//fprintf(fp,"%lf %lf\n", P, P_max[q]);

			/*for(i=0; i<dim-1; i++) {
				for(j=0; j<dim; j++) {

					if(S[i] == S[j] && S[i] != 0) {
						s[S[i]] += 1;
					}

				}

				while(s[S[i+1]] > 0) {
					i = i + 1;
				}
			}*/

			/*for(i=0; i<k+1; i++)
			{
				Iav = Iav + s[S_new[i]]*S_new[i]/(P*(n-1)*(n-1));
				fprintf(fp2,"%lf %lf \n", P, Iav);
				//printf("s[%d] = %d\n", S_new[i], s[S_new[i]]);
				//fprintf(fp2, "plhthos cluster = %d , megethous = %d",  s[S_new[i]], S_new[i]);
			} */


			I_av = 0.0;
			/*int m;
			for(m=1; m<=S_max; m++) {
				Iav += s[m]*pow(m,2)/num_of_1;
			}*/

			for(i=0; i<dim; i++) {
				I_av += (S[i]/num_of_1)*S[i];
			}

			Iav[q] += I_av;

			//fprintf(fp2,"%lf %lf \n", P, Iav[q]);

			dot_Iav = I_av - Pmax*S_max;

			dotIav[q] += dot_Iav;

			//fprintf(fp3,"%lf %lf \n", P, dotIav[q]);

			/*if(P>=0.60 && P<=0.65) {
				printf("p = %lf \n", P);
				fprintf(fp4,"%lf %lf\n", log(fabs(P-0.59)), log(P_max[q]));
				fprintf(fp5,"%lf %lf\n", log(fabs(P-0.59)), log(Iav[q]));
			}*/


		}
	}

	printf("num_of_experiments = %d \n", num_of_experiments);



	for(q=1; q<dim1-2; q++) {
		fprintf(fp,"%lf %lf\n", P_matrix[q], P_max[q]/100.0);
		fprintf(fp2,"%lf %lf \n", P_matrix[q], Iav[q]/100.0);
		fprintf(fp3,"%lf %lf \n", P_matrix[q], dotIav[q]/100.0);
	}

	for(q=1; q<dim1-2; q++) {
		if(P_matrix[q] > 0.1 && P_matrix[q] < 0.59) {
			fprintf(fp5,"%lf %lf\n", log(fabs(P_matrix[q]-0.59)), log(Iav[q]/100.0));
			printf("p1 = %lf \n", P_matrix[q]);
		}
		if(P_matrix[q] >= 0.60 && P_matrix[q] < 0.7) {
			fprintf(fp4,"%lf %lf\n", log(P_matrix[q]-0.59), log(P_max[q]/100.0));
			printf("p2 = %lf \n", P_matrix[q]);
		}
	}


	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	return 0;
}