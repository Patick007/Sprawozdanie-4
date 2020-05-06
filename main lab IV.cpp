#include <math.h>
#include <stdio.h>
#include "winbgi2.h"
#include <stdlib.h>
#include "rk4.h"

#define lambda 3.5
#define y0 5.6
#define t0 3.9

double meulera(double t, double y, double h, double (*fun)(double, double));
double analityczne(double t);
double funkcja(double t, double y);

void main()
{
	double przedzial,t,N,h,tk,epse,epsrk,wynike,wynikrk;
	printf("Wprowadz tk:\n"); //tk musi byc wieksze od t0
	scanf("%lf", &tk);
	przedzial = tk - t0;
	wynike = y0;
	wynikrk = y0;
	t = t0;
	FILE* f;
	f = fopen("wyniki.txt", "w");
	for(int i = 0; i<7; i++)
	{
		N = pow(2.0, i);
		printf("N = %lf\n", N);
		h = przedzial/N;
		for(int j = 0; j<N; j++)
		{
			t=t+h;
			wynike = meulera(t, wynike, h, funkcja);
			wynikrk = rk4(t, wynikrk, h, funkcja);
			epse = abs((wynike - analityczne(t))/analityczne(t));
			epsrk = abs((wynikrk - analityczne(t))/analityczne(t));
			printf("t = %.4lf\twynik metody Eulera = %.4lf\tblad metody Eulera = %.4lf\twynik metody RK = %.4lf\tblad metody RK = %.4lf\n", t, wynike, epse, wynikrk, epsrk);
			if(j == N-1)
			{
				fprintf(f,"N = %lf\th = %.4lf\tblad metody Eulera = %.4lf\tblad metody RK = %.4lf\n", N, h, epse, epsrk);
			}
		}
		printf("\n");
		wynike = y0;
		wynikrk = y0;
		t = t0;
	}
	fclose(f);
}







double meulera(double t, double y, double h, double (*fun)(double, double))
{
	y = y + h * fun(t,y);
	return y;
}
double analityczne(double t)
{
	return y0*exp(lambda*(t-t0));
}
double funkcja(double t, double y)
{
	return lambda*y;
}


