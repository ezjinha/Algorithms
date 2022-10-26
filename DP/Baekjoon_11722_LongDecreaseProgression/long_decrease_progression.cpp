#include <iostream>
using namespace std;

int main()
{
	int n;
	int a[1001];
	int dp[1001];

	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	for (int i = 0; i < n; i++)
	{
		dp[i] = 1;
		for (int j = 0; j < i; j++)
		{
			if (a[j] > a[i] && dp[j] + 1 > dp[i])
			{
				dp[i] = dp[j] + 1;
			}
		}
	}

	int max_len = 0;
	for (int i = 0; i < n; i++)
	{
		max_len = dp[i] > max_len ? dp[i] : max_len;
	}

	cout << max_len << '\n';

	return 0;
}