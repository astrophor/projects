#include <iostream>
using namespace std;
#define MAXN 2010
int h[MAXN],r[MAXN],l[MAXN];
int map[MAXN][MAXN];
char str[2];
int n,m;
void all_1_matrix()
{
    int i,j,max = 0;
    memset(h,0,sizeof(h));
    for(i = 0; i < n; i++)
    {
        for(j = 0 ; j < m; j++)
        {
            if(map[i][j] == 1)
                h[j] ++;
            else h[j] = 0;
        }
        // 类类似并查集的路径压缩
        // left 求高度为h〔j〕的矩阵的左边界
        for(j = 0; j < m; j ++)
        {
            l[j] = j;
            while(l[j] > 0 && h[j] <= h[l[j] - 1])
                l[j] = l[l[j] - 1];
        } 
        // right求高度为h〔j〕的矩阵的右边界
        for(j = m-1; j >= 0; j --)
        {
            r[j] = j;
            while(r[j] < m-1 && h[j] <=h[r[j] + 1])
                r[j] = r[r[j] + 1];
        }
        for(j = 0; j < m; j ++)
        {
            if((r[j] - l[j] + 1) * h[j] > max)
                max = (r[j] - l[j] + 1) * h[j];
        }
    }
    printf("%d\n",max);
}
int main()
{
    int t, i , j, k, len ;
    char ch;
// freopen("1964.in","r",stdin);
// scanf("%d",&t);
    while(scanf("%d %d",&n,&m)!=EOF)
    {
      // scanf("%d %d",&n,&m);
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < m; j++)
            {
               scanf("%d",&map[i][j]); 
            }
        }
        all_1_matrix();
    }
}
