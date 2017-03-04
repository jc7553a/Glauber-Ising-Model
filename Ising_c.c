#include <stdio.h>
//#include <conio.h>
#include <math.h>
#include <stdlib.h>
#define nSamples 200000
#define nTime  200
#define n  9
#define t0 100
#define j0 4
#define nTOT  20000
#pragma warning(disable:4996)

int magMatrix[nSamples][nTime];
int atomMatrix[nSamples][nTime][n];
int corrMatrix[nSamples][t0][n];
double corrAvg[nTime][n];
double energyMatrix[nSamples][nTime];


int main(void)
{
	int zz;
	int hh;
	double BB = 0;
	double Gamma;
	int myNum = 0;

	for (zz = 0; zz < 8; ++zz)
	{
		if (zz < 3  )
			{
				BB = BB + .2;
			}
			else
			{
				BB = BB + .4;
			}
		Gamma = 1;
		for (hh = 0; hh < 1; ++hh)
		{

			monteCarlo(BB, Gamma, myNum);
			Gamma += .2;
			myNum = myNum + 1;
			printf("Num: %d HH: %d zz: %d\n ", myNum, hh, zz);
			getchar();
		}

		
	}
	//getchar();
	return 0;


}//end main

int monteCarlo(double B, double gamma, int Z)
{
	/*Variables for effective Temperature*/
	double D = (B / 2.0);
	double tD = (4 * D);
	double T_eff = ((tD / 4) * (1 + (pow(gamma, 2) / pow(tD, 2))));
	//Calculate effective beta*J
	double JJ = 2;
	double J_eff = (JJ / 4);
	double beta = (1 / T_eff);
	double J = (beta*J_eff);
	//printf("\nbeta: %.4f \nJ: %.4f \nJ_eff: %.4f", beta, J, J_eff);


	/*NEW CALCULATION OF GAMMA*/
	double gG = (J_eff*tD)/gamma;
	double dt = (10/gamma);
	double tGamma = gG *dt;
	tGamma = .1;
	

	int tt = 0;
	int atoms[n];
	int atoms_new[n];
	//double energy[nSamples][nTime];
	double energySum;
	//int mag[nSamples][nTime];
	int magSum;

	/*Var Update Loop*/
	double probabilityOfFlip;
	int lside;
	int rside;
	int current;
	int lindex;
	int rindex;
	double val;

	
	//int dist[nTime];

	

	/*Var for Loops*/
	int aaa;
	int bbb;
	int yy;
	int samples;
	int i;
	int updateLoop;
	int time;
	int k;
	int ss;
	int qq;
	int kk;
	int w;
	int e;
	int ww;
	int ee;
	int uu;
	int www;
	int eee;
	int uuu;
	/*
	for (aaa = 0; aaa < nTime; ++aaa)
	{
		for (bbb = 0; bbb < (n); ++bbb)
		{
			mag[aaa][bbb] = 0;
		}
	}
	*/

	/*File Pointers*/

	FILE * engPointer;
	FILE * magPointer;
	//FILE * corrPointer;
	FILE * corrAvgPointer;
	
	char fileBuffer[30];
	char fileBuffer2[30];
	char fileBuffer3[30];
	snprintf(fileBuffer, sizeof(char) * 30, "CorrAvg.dat_B_%2.1f_g_%2.1f", B, gamma);
	snprintf(fileBuffer2, sizeof(char) * 30, "Energy.dat_B_%2.1f_g_%2.1f", B, gamma);
	snprintf(fileBuffer3, sizeof(char) * 30, "Mag.dat_B_%2.1f_g_%2.1f", B, gamma);
	
	//corrPointer = fopen("Corr.dat", "w");

	corrAvgPointer = fopen(fileBuffer, "w");
	engPointer = fopen(fileBuffer2, "w");
	magPointer = fopen(fileBuffer3, "w");

	gamma = 0.1;

	for (samples = 0; samples < nSamples; ++samples)
	{
		for (i = 0; i < n; ++i)
		{
			atoms[i] = -1;
		}//end create array
		for (time = 0; time < nTime; ++time)
		{
			//Start Updating Array
			for (updateLoop = 0; updateLoop < n; ++updateLoop)
			{
				val = ((double)(rand())) / ((double)(RAND_MAX));
				current = atoms[updateLoop];
				lindex = updateLoop - 1;
				rindex = updateLoop + 1;
				if (lindex < 0)
				{
					lindex = n -1;
				}
				
					lside=atoms[lindex];
				
				if (rindex == n)
				{
					rindex = 0;
				}
					rside = atoms[rindex];

				current = atoms[updateLoop];
				atoms_new[updateLoop] = current;
				probabilityOfFlip = (0.5*(double)(tGamma))*(1 - ((double)(current)*(double)(tanh(J*lside + J*rside))));
		
				if (val < probabilityOfFlip)
				{
					atoms_new[updateLoop] = -1 * current;
				}
			}// end update loop

			for (yy = 0; yy < n; ++yy)
			{
				atoms[yy] = atoms_new[yy];
			}


			/*Mag Calculation*/
			
			magSum = 0;
			for (kk = 0; kk < n; ++kk)
			{
				magSum = magSum + atoms[kk];
			}
			//fprintf(magPointer, "%d ", magSum);
			magMatrix[samples][time] = magSum;

			/*Energy Calculation*/

			energySum = 0;
			for (k = 0; k < n-1; ++k)
			{
				energySum = energySum - J_eff*atoms[k] * atoms[k + 1];
			}
			//fprintf(engPointer, "%f ", energySum);
			energyMatrix[samples][time] = energySum;
			

			
			
			
			for (qq = 0; qq < n; ++qq)
			{
				atomMatrix[samples][time][qq] = atoms[qq];
			}
				
			
			if (time >= t0)
			{
				tt = time - t0;
					
					for (ss = 0; ss < n; ++ss)
					{
						corrMatrix[samples][tt][ss] =  (atoms[ss] * atomMatrix[samples][t0][j0]);
					}
					
			}//end if
			
		}// end time loop
		//fprintf(engPointer, "\n");
		//fprintf(magPointer, "\n");
	}// end sample loop
	
/*
	for (w = 0; w < nSamples; ++w)
	{
		for (e = 0; e < nTime; ++e)
		{
			//fprintf(magPointer, "%d ", mag[w][e]);
			//fprintf(engPointer, "%f ", energy[w][e]);
		}// end column
		//fprintf(magPointer, "\n");
		//fprintf(engPointer, "\n");
	}// end  row
	
*/
	
	for (ww = 0; ww < n; ++ww)
	{
		for (ee = 0; ee < (nSamples); ++ee)
		{
			for (uu = 0; uu < t0; ++uu)
			{
				//fprintf(corrPointer, "%d", corrMatrix[ee][uu][ww]);
			}//end column
			//fprintf(corrPointer, "\n");
		}// end row
		printf("\n");
		
	}// end page
	
	int t;
	double energyAvg;
	double magAvg;
	/*Calculate Energy Average and Mag Avg*/
	for (i = 0; i < nTime; ++i)
	{
		energyAvg = 0;
		for(t = 0; t < nSamples; ++t)
		{
			energyAvg = energyAvg + energyMatrix[t][i];
			magAvg = magAvg + magMatrix[t][i];
		}
		energyAvg = energyAvg/nSamples;
		magAvg = magAvg / nSamples;
		fprintf(engPointer, "%f ", energyAvg);
		fprintf(magPointer, "%f ", magAvg);
	}
	fprintf(engPointer, "\n");
	fprintf(magPointer, "\n");

	/*Calculating Correlation Average*/

	for (www = 0; www < n; ++www)
	{	
		for (eee = 0; eee < (t0); ++eee)
		{
			for (uuu = 0; uuu < nSamples; ++uuu)
			{
				corrAvg[eee][www] = (corrAvg[eee][www] + corrMatrix[uuu][eee][www]);
			}//end column
			corrAvg[eee][www] = (corrAvg[eee][www] /(double) nSamples);
			fprintf(corrAvgPointer, "%f ", corrAvg[eee][www]);
		}// end row
		fprintf(corrAvgPointer, "\n");
	}// end page
	

	fclose(engPointer);
	
	//fclose(corrPointer);
	fclose(magPointer);
	fclose(corrAvgPointer);
	//getchar();
	return 0;
}// end program