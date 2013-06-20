#include <stdio.h>

long long a[100];
int n;

void init()
{
	int i = 0;
	a[1] = 1;
	a[2] = 1;
	for(i = 3; i <= 70; ++i)
		a[i] = a[i-1] + a[i-2];
}

int main(int argc, char const *argv[])
{
	init();
	while(scanf("%d", &n) != EOF)
	{
		printf("%lld\n", a[n]);
	}
	return 0;
}