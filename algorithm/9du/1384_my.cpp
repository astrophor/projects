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

bool find_row(int row, int left, int right)
{
    int mid = 0;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(a[row][mid] == num)
            return true;
        else if(a[row][mid] < num)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

bool find_column(int column, int top, int down)
{
    int mid = 0;
    while(top <= down)
    {
        mid = (top + down) / 2;
        if(a[mid][column] == num)
            return true;
        else if(a[mid][column] < num)
            top = mid + 1;
        else
            down = mid - 1;
    }
    return false;
}

bool find_row_right(int row, int left, int right, int& pos)
{
    int mid = 0;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(a[row][mid] == num)
            return true;
        else if(a[row][mid] < num)
            left = mid + 1;
        else
            right = mid - 1;
    }
    pos = right;
    return false;
}

bool find_row_left(int row, int left, int right, int& pos)
{
    int mid = 0;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(a[row][mid] == num)
            return true;
        else if(a[row][mid] < num)
            left = mid + 1;
        else
            right = mid - 1;
    }
    pos = left;
    return false;
}

bool find_column_top(int column, int top, int down, int& pos)
{
    int mid = 0;
    while(top <= down)
    {
        mid = (top + down) / 2;
        if(a[mid][column] == num)
            return true;
        else if(a[mid][column] < num)
            top = mid + 1;
        else
            down = mid - 1;
    }
    pos = top;
    return false;
}

bool find_column_down(int column, int top, int down, int& pos)
{
    int mid = 0;
    while(top <= down)
    {
        mid = (top + down) / 2;
        if(a[mid][column] == num)
            return true;
        else if(a[mid][column] < num)
            top = mid + 1;
        else
            down = mid - 1;
    }
    pos = down;
    return false;
}

bool find(int left, int top, int right, int down)
{
    if(top == down)
    {
        return find_row(top, left, right);
    }

    if(left == right)
    {
        return find_column(left, top, down);
    }

    int pos;
    if(find_row_right(top, left, right, pos))
        return true;
    else
    {
        if(pos < left)
            return false;
        else
            right = pos;
    }

    if(find_row_left(down, left, right, pos))
        return true;
    else
    {
        if(pos > right)
            return false;
        else
            left = pos;
    }

    if(find_column_top(right, top, down, pos))
        return true;
    else
    {
        if(pos > down)
            return false;
        else
            top = pos;
    }

    if(find_column_down(left, top, down, pos))
        return true;
    else
    {
        if(pos < left)
            return false;
        else
            down = pos;
    }

    return find(left, top, right, down);
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