#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int A[100][100];                 // array
vector<pair<int, int>> v;        // vector to store pairs
vector<size_t> size_v;           // each row or col size vector
int R;                           // size of row
int C;                           // size of col
int r;                           // row location
int c;                           // col location
int k;                           // target value
int t;                           // minimum time

void fillZero(bool isROP, int& max_range)
{
    for (size_t i = 0; i < size_v.size(); i++)
    {
        int n = size_v[i];
        for (size_t j = n; j < max_range; j++)
        {
            int& var = isROP ? A[i][j] : A[j][i];
            var = 0;
        }
    }
}

void assignResult(size_t i, bool isROP)
{
    int idx = 0;
    for (pair<int, int>& p : v)
    {
        int& var_first = isROP ? A[i][idx] : A[idx][i];
        var_first = p.first;
        idx += 1;
        int& var_second = isROP ? A[i][idx] : A[idx][i];
        var_second = p.second;
        idx += 1;
    }
}

void selectionSort(int idx, size_t size)
{
    if (idx == size)
        return;

    int min_p = idx;
    for (size_t i = idx + 1; i < size; i++)
    {
        if (v[min_p].second > v[i].second)
        {
            min_p = i;
        }
        else if (v[min_p].second == v[i].second)
        {
            min_p = v[min_p].first > v[i].first ? i : min_p;
        }
    }
    swap(v[idx], v[min_p]);
    
    selectionSort(idx + 1, size);
}

void countNum()
{
    bool isROP = R >= C ? true : false;
    int& max_range = isROP ? C : R;         // max range
    for (size_t i = 0; i < (isROP ? R : C); i++)
    {
        for (size_t j = 0; j < (isROP ? C : R); j++)
        {
            int& var = isROP ? A[i][j] : A[j][i];
            bool isFoundNum = false;
            if (var == 0) continue;
            for (pair<int, int>& p : v)
            {
                if (p.first == var)
                {
                    p.second += 1;
                    isFoundNum = true;
                    break;
                }
            }
            
            if (!isFoundNum)
            {
                int num = var;
                v.emplace_back(num, 1);
            }
        }

        size_v.push_back(v.size() * 2);
        max_range = max_range < v.size() * 2 ? v.size() * 2 : max_range;
        selectionSort(0, v.size());
        assignResult(i, isROP);
        v.clear();
    }

    fillZero(isROP, max_range);
    size_v.clear();
}

void operate()
{
    t = 0;
    while (A[r][c] != k)
    {
        if (t > 100)
        {
            t = -1;
            break;
        }
        countNum();
        t += 1;
    }

    cout << t << endl;
}

void initArray()
{
    for (size_t i = 0; i < 100; i++)
    {
        for (size_t j = 0; j < 100; j++)
        {
            A[i][j] = 0;
        }
    }
}

int main()
{
    ifstream cin("input.txt");

    for (size_t test_case = 1; test_case <= 6; test_case++)
    {
        initArray();
        R = 3;
        C = 3;
        cin >> r >> c >> k;
        r = r - 1;
        c = c - 1;
        for (size_t i = 0; i < R; i++)
        {
            for (size_t j = 0; j < C; j++)
            {
                cin >> A[i][j];
            }
        }
        operate();
    }
}