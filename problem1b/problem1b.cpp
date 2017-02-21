#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

double prob1(int x1, int x2, int x3);
double prob2(int x1, int x2, int x3);
double prob3(int x1, int x2, int x3);

#define NUM_STEPS		5
#define X_1				6
#define X_2				6
#define X_3				6
#define NUM_TRIALS		100000


int main()
{
	srand(time(0));
	double p1, p2, p3; //probabilities of each reaction firing at a given step
	int x1, x2, x3; //amounts of x1, x2, and x3
	double temp;
	int lastReaction = 0;
	int trialCount;

	int x1Final[X_1 + X_2 + X_3 + 1];
	int x2Final[X_1 + X_2 + X_3 + 1];
	int x3Final[X_1 + X_2 + X_3 + 1];

	for (int i = 0; i < (X_1 + X_2 + X_3 + 1); i++)
	{
		x1Final[i] = 0;
		x2Final[i] = 0;
		x3Final[i] = 0;
	}


	//std::cout << "x1\tx2\tx3\n";

	for (trialCount = 0; trialCount < NUM_TRIALS; trialCount++)
	{
		x1 = X_1;
		x2 = X_2;
		x3 = X_3;

		for (int i = 0; i < NUM_STEPS; i++)
		{
			p1 = prob1(x1, x2, x3);
			p2 = prob2(x1, x2, x3);
			p3 = prob3(x1, x2, x3);

			temp = (double)rand() / (double)RAND_MAX;
			//cout << temp << "\t" << p1 << "\t" << p2 << "\t" << p3 << endl;

			if ((temp < p1) && (x1 > 1) && (x2 > 1)) //p1 fires
			{
				x1 -= 2;
				x2 -= 2; //channged to 2 so quantities don't blow up
				x3 += 4;
				lastReaction = 1;
			}
			else if ((temp < (p1 + p2)) && (x1 > 0) && (x3 > 1)) //p2 fires
			{
				x1 -= 1;
				x2 += 3;
				x3 -= 2;
				lastReaction = 2;
			}
			else if ((temp > (p1 + p2)) && (x2 > 0) && (x3 > 0))  //p3 fires
			{
				x1 += 2;
				x2 -= 1;
				x3 -= 1;
				lastReaction = 3;
			}

			/*if (x1 < 0 || x2 < 0 || x3 < 0)
				std::cout << "NEGATIVE\t" << x1 << "\t" << x2 << "\t" << x3 << endl;

			if (i == NUM_STEPS - 1)
				std::cout << x1 << "\t" << x2 << "\t" << x3 << endl;*/
		}

		x1Final[x1]++;
		x2Final[x2]++;
		x3Final[x3]++;
	}

	double prx1[X_1 + X_2 + X_3 + 1];
	double prx2[X_1 + X_2 + X_3 + 1];
	double prx3[X_1 + X_2 + X_3 + 1];

	for (int i = 0; i < X_1 + X_2 + X_3 + 1; i++)
	{
		prx1[i] = (double)x1Final[i] / NUM_TRIALS;
		prx2[i] = (double)x2Final[i] / NUM_TRIALS;
		prx3[i] = (double)x3Final[i] / NUM_TRIALS;
	}

	cout << "X1\n___________________________\n";
	for (int i = 0; i < X_1 + X_2 + X_3 + 1; i++)
	{
		cout << "\tPr[x1 = " << i << "] = " << prx1[i] << endl;
	}

	cout << "\nX2\n___________________________\n";
	for (int i = 0; i < X_1 + X_2 + X_3 + 1; i++)
	{
		cout << "\tPr[x2 = " << i << "] = " << prx2[i] << endl;
	}

	cout << "\nX3\n___________________________\n";
	for (int i = 0; i < X_1 + X_2 + X_3 + 1; i++)
	{
		cout << "\tPr[x3 = " << i << "] = " << prx3[i] << endl;
	}



	double x1mean = 0, x2mean = 0, x3mean = 0;
	double x1var = 0, x2var = 0, x3var = 0;
	double x1sd, x2sd, x3sd;

	for (int i = 0; i < X_1 + X_2 + X_3 + 1; i++)
	{
		x1mean += x1Final[i] * i;
		x2mean += x2Final[i] * i;
		x3mean += x3Final[i] * i;
	}

	x1mean /= NUM_TRIALS;
	x2mean /= NUM_TRIALS;
	x3mean /= NUM_TRIALS;

	for (int i = 0; i < X_1 + X_2 + X_3 + 1; i++)
	{
		x1var += x1Final[i] * pow(i, 2);
		x2var += x2Final[i] * pow(i, 2);
		x3var += x3Final[i] * pow(i, 2);
	}

	x1var /= NUM_TRIALS;
	x2var /= NUM_TRIALS;
	x3var /= NUM_TRIALS;

	x1sd = sqrt(x1var);
	x2sd = sqrt(x2var);
	x3sd = sqrt(x3var);


	cout << endl << endl;
	cout << "x1 Mean = " << x1mean << endl;
	cout << "x2 Mean = " << x2mean << endl;
	cout << "x3 Mean = " << x3mean << endl;

	cout << endl << endl;
	cout << "x1 Variance = " << x1var << endl;
	cout << "x2 Variance = " << x2var << endl;
	cout << "x3 Variance = " << x3var << endl;

	cout << endl << endl;
	cout << "x1 Std. Dev = " << x1sd << endl;
	cout << "x2 Std. Dev = " << x2sd << endl;
	cout << "x3 Std. Dev = " << x3sd << endl;
	return 0;
}



double prob1(int x1, int x2, int x3)
{
	double tempTop = .5*x1*(x1 - 1)*x2;
	double tempBot = (.5*x1*(x1 - 1)*x2) + (x1*x3*(x3 - 1)) + (3 * x2*x3);
	return tempTop / tempBot;
}



double prob2(int x1, int x2, int x3)
{
	double tempTop = (x1*x3*(x3 - 1));
	double tempBot = (.5*x1*(x1 - 1)*x2) + (x1*x3*(x3 - 1)) + (3 * x2*x3);
	return tempTop / tempBot;
}



double prob3(int x1, int x2, int x3)
{
	double tempTop = 3 * x2 * x3;
	double tempBot = (.5*x1*(x1 - 1)*x2) + (x1*x3*(x3 - 1)) + (3 * x2*x3);
	return tempTop / tempBot;
}