#include <stdio.h>

void swap_sla(int *x, int *y)
{
	// *x =  *x + *y;
	// *y = *x - *y;
	// *x = *x - *y;
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}
int main()
{
	int a = 1;
	int b = 2;
	printf("ANTES a: %i b: %i\n", a, b);
	swap_sla(&a, &b);
	printf("DEPOIS a: %i b: %i\n", a, b);

}