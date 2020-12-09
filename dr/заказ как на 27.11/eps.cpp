#include<iostream>
#include<cmath>

using namespace std;

void calculate(double x)
{
	int n;
	int m;
	double fun;
	double eps;
	n = 2;
	fun = 1 / pow(1 - x, 2);
	eps = fun - 1;
	for(m = -2; m > -7; m--)
	{
		while (abs(eps) >= pow(10, m))
		{
			eps = eps - n * pow(x, n - 1);
			n++;
		}
		cout << "Precision:" << pow(10, m) << " Iterations:" << n << endl;
	}
}

int main()
{
	double x;
	cin >> x;

	if (x >= 1 || x <= -1)
	{
		cout << "|x| must be < 1";
		return 1;
	}

	calculate(x);
	cout << "Number of iterations increases with precision.";

	return 0;
}