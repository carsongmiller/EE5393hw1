#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

#define NUM_SPEEDS			4
#define SLOW				10
#define MEDIUM				100
#define FAST				1000
#define FASTER				10000

#define NUM_STEPS			1000000
#define NUM_REACTIONS		6

double rand(int a, int b);
double rand(double a, double b);
double rand(double a, int b);
double rand(int a, double b);


int main()
{
	srand(time(0));
	ofstream ostream;
	ostream.open("logReaction.csv");
	ostream << "step,a,b,c,x,xprime,y\n";

	//Reactants:
	int a, b, c, x, xprime, y;

	int aLast, bLast, cLast, xLast, xprimeLast, yLast;
	
	//Initial Concentrations:
	a = 0;
	b = 1;
	c = 0;
	x = 10000;
	xprime = 0;
	y = 0;

	aLast = a;
	bLast = b;
	cLast = c;
	xLast = x;
	xprimeLast = xprime;
	yLast = y;

	int step = 0;

	//for (int i = 0; i < NUM_STEPS; i++)
	while(1)
	{
		step++;
		int temp = rand() % 6;

		switch (temp)
		{
		case 0:
			if (rand(0, pow(10, NUM_SPEEDS + 1)) < (SLOW*NUM_REACTIONS) && b >= 1)
			{
				a += 1;
			}
			break;

		case 1:
			if (rand(0, pow(10, NUM_SPEEDS + 1)) < (FASTER*NUM_REACTIONS) && a >= 1 && x >= 2)
			{
				x -= 2;
				c += 1;
				xprime += 1;
			}
			break;

		case 2:
			if (rand(0, pow(10, NUM_SPEEDS + 1)) < (FASTER*NUM_REACTIONS) && c >= 2)
			{
				c /= 2;
			}
			break;

		case 3:
			if (rand(0, pow(10, NUM_SPEEDS + 1)) < (FAST*NUM_REACTIONS) && a >= 1)
			{
				a -= 1;
			}
			break;

		case 4:
			if (rand(0, pow(10, NUM_SPEEDS + 1)) < (MEDIUM*NUM_REACTIONS) && xprime >= 1)
			{
				xprime -= 1;
				x += 1;
			}
			break;

		case 5:
			if (rand(0, pow(10, NUM_SPEEDS + 1)) < (MEDIUM*NUM_REACTIONS) && c >= 1)
			{
				y += 1;
				c -= 1;
			}
			break;
		}

		if(aLast != a || bLast != b || cLast != c || xLast != x || xprimeLast != xprime || yLast != y)
			ostream << step << "," << a << "," << b << "," << c << "," << x << "," << xprime << "," << y << "\n";

		aLast = a;
		bLast = b;
		cLast = c;
		xLast = x;
		xprimeLast = xprime;
		yLast = y;

		/*ostream <<i << "," << a << "," << b << "," << c << "," << x << "," << xprime << "," << y << "\n";
		if (a > 0)
			cout << a << "," << b << "," << c << "," << x << "," << xprime << "," << y << "\n";*/

		if (x <= 0 && c <= 0) break;
	}

	cout << a << "," << b << "," << c << "," << x << "," << xprime << "," << y << "\n";

    return 0;
}



double rand(double a, double b)
{
	return (((double)rand() / (double)RAND_MAX) * (b - a)) + a;
}

double rand(int a, int b)
{
	return (((double)rand() / (double)RAND_MAX) * (b - a)) + a;
}

double rand(double a, int b)
{
	return (((double)rand() / (double)RAND_MAX) * (b - a)) + a;
}

double rand(int a, double b)
{
	return (((double)rand() / (double)RAND_MAX) * (b - a)) + a;
}