#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

#define NUM_SPEEDS			4
#define SLOWEST				10
#define SLOW				100
#define FAST				1000
#define FASTEST				10000

#define NUM_STEPS			10000

#define X_INIT				12
#define Y_INIT				9

double rand(int a, int b);
double rand(double a, double b);
double rand(double a, int b);
double rand(int a, double b);


int main()
{
	srand(time(0));
	ofstream ostream;
	ostream.open("multiplication.csv");
	ostream << "step,a,x,y,yprime,z\n";

	//Reactants:
	int a, b, x, y, z;


	//Initial Concentrations:
	a = 0;
	b = 0;
	x = X_INIT;
	y = Y_INIT;
	z = 0;

	bool aAb, bAb, yAb;

	int step = 0;
	double temp;

	std::cout << "a\tb\tx\ty\tz\n";
	ostream << "step,a,b,x,y,z\n";

	for (int i = 0; i < NUM_STEPS; i++)
	{
		step++;
		if (a <= 0) aAb = true;
		else aAb = false;

		if (b <= 0) bAb = true;
		else bAb = false;

		if (y <= 0) yAb = true;
		else yAb = false;

		temp = rand(0, 4);

		if (temp <= 1 && bAb && x >= 1 && aAb) // b' + x -> a
		{
			x -= 1;
			a += 1;
		}
		else if (temp > 1 && temp <= 2 && a >= 1 && y >= 1) //a + y -> b + a
		{
			y -= 1;
			b += 1;
		}
		else if (temp > 2 && temp <= 3 && yAb && a >= 1) //y' + a -> not
		{
			a -= 1;
		}
		else if (temp > 3 && aAb && b >= 1) //a' + b -> z + y
		{
			b -= 1;
			z += 1;
			y += 1;
		}

		std::cout << a << "\t" << b << "\t" << x << "\t" << y << "\t" << z << endl;
		ostream << step << "," << a << "," << b << "," << x << "," << y << "," << z << endl;
	}

	std::cout << a << "\t" << b << "\t" << x << "\t" << y << "\t" << z << endl;
	ostream << step << "," << a << "," << b << "," << x << "," << y << "," << z << endl;

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