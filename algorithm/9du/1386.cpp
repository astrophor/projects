#include <stdio.h>

int a[1000010];
int n;

int min(int x, int y)
{
	if(x < y)
		return x;
	else
		return y;
}

int find(int left, int right)
{
	int mid;

	if(left == right)
		return a[left];

	while(a[left] >= a[right])
	{
		if(left + 1 == right)
			return min(a[left], a[right]);

		mid = (left + right) / 2;
		if(a[left] == a[mid] && a[mid] == a[right])
			return min(find(left, mid), find(mid, right));

		if(a[mid] >= a[left])
			left = mid;
		else if(a[mid] <= a[right])
			right = mid;
	}
	return a[left];
}

int main(int argc, char const *argv[])
{
	while(scanf("%d", &n) != EOF)
	{
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
		}
		printf("%d\n", find(0, n-1));
	}

	return 0;
}

