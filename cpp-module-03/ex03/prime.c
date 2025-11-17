
#include <math.h>
#include <stdio.h>
#define PI 3.14

int fract(int n)
{
	int fr = 1;
	while (n) {
		fr *= n;
		n--;
	}
	return n;
}

double sub(int i)
{
	double tmp, r = 0;
	for (int j = 1; j < i; j++) {
		tmp = cos(PI) * fract(j -1) + 1;
		tmp = tmp / j;
		tmp *= tmp;
		r += tmp;
	}
	return 4.0 / r;
}

long double nthPrime(int n) {

	long double prime = 0;
	
	int f = pow(n, 2);
	for (int i = 1; i < f; i++) {
	
		prime += sub(i);
	}
	prime = pow(prime, 1.0/n);
	return prime;

}

int main()
{
	int n;
	scanf("%d", &n);
	printf("n: %Lf\n", nthPrime(n));
}
