#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

double prob1(int x1, int x2, int x3);
double prob2(int x1, int x2, int x3);
double prob3(int x1, int x2, int x3);

#define NUM_STEPS		1000
#define X_1				5
#define X_2				5
#define X_3				5
#define NUM_TRIALS		1000


int main()
{
	srand(time(0));
	double p1, p2, p3; //probabilities of each reaction firing at a given step
	int x1, x2, x3; //amounts of x1, x2, and x3
	double temp;
	int lastReaction = 0;
	double c1 = 0, c2 = 0, c3 = 0;
	int trialCount;

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

			if(x1 < 0 || x2 < 0 || x3 < 0)
				std::cout << "NEGATIVE\t" << x1 << "\t" << x2 << "\t" << x3 << endl;

			if (i == NUM_STEPS-1)
				std::cout << x1 << "\t" << x2 << "\t" << x3 << endl;
		}

		if (x1 > 7)		c1++;
		if (x2 >= 0)	c2++;
		if (x3 < 3)		c3++;
	}

	double prc1 = c1 / NUM_TRIALS;
	double prc2 = c2 / NUM_TRIALS;
	double prc3 = c3 / NUM_TRIALS;

	cout << "Pr(c1)\tPr(c2)\tPr(c3)\n";
	cout << prc1 << "\t" << prc2 << "\t" << prc3 << endl;
	cout << c1 << "\t" << c2 << "\t" << c3 << endl;

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