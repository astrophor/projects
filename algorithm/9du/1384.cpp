#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <limits.h>
#include <stdio.h>
using namespace std;
 
int a[1010][1010];
int n = 0;
int m = 0;
int num = 0;


bool find(int left, int top, int right, int down)
{
    while(top < m && right >= 0)
    {
        if(a[top][right] == num)
            return true;
        else if(a[top][right] < num)
            ++ top;
        else
            -- right;
    }
    return false;
}
 
int main()
{
    int i = 0;
    int j = 0;
 
    while(scanf("%d %d", &m, &n) != EOF)
    {
        scanf("%d", &num);
        for (i = 0; i < m; ++i)
            for (j = 0; j < n; ++j)
                scanf("%d", &a[i][j]);
        if (find(0, 0, n-1, m-1))
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
 
    return 0;
}