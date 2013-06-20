#include <stdio.h>

int matrix[1010][1010];
int index[1010][1010];
int up[1010];
int down[1010];
int m, n;

void func()
{
	int i, j;
	int cur;
	int max = 0;
	for (i = 0; i < m; ++i)
	{
		cur = 0;
		for(j = 0; j < n; ++j)
		{
			if (matrix[i][j] == 0)
			{
				index[i][j] = cur = 0;
			}
			else
			{
				cur ++;
				index[i][j] = cur;
			}
		}
	}
	for(i = 0; i < n; ++i)
	{
		for(j = 0; j < m; ++j)
		{
			up[j] = j;
			while(up[j] > 0 && index[up[j]-1][i] >= index[j][i])
				up[j] = up[up[j]-1];
		}
		for(j = m-1; j >= 0; --j)
		{
			down[j] = j;
			while(down[j]+1 < m && index[down[j]+1][i] >= index[j][i])
				down[j] = down[down[j]+1];
		}
		for(j = 0; j < m; ++j)
		{
			cur = (down[j] - up[j] + 1) * index[j][i];
			if(cur > max)
				max = cur;
		}
	}
	printf("%d\n", max);
}

int main(int argc, char const *argv[])
{
	while (EOF != scanf("%d %d", &m, &n))
	{
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				scanf("%d", &matrix[i][j]);
		func();
	}
	return 0;
}
