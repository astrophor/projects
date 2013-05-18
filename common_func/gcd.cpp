#include <stdio.h>

int gcd(int a, int b)
{
	int temp = b % a;
	while (temp != 0)
	{
		b = a;
		a = temp;
		temp = b % a;
	}
	return a;
}

int main()
{
	if (1 != gcd(2, 3)
	||  2 != gcd(2, 4)
	||  10 != gcd(100, 130)
	||  13 != gcd(13, 169)
	||  13 != gcd(156, 169)
	||	3 != gcd(6, 9))
		printf("failed\n");
	else
		printf("pass\n");

	return 0;
}
