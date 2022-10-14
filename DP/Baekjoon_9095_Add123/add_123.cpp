#include <iostream>
using namespace std;

int dp[12];

int main()
{
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; test_case++)
	{
		int n;
		cin >> n;
		dp[1] = 1;
		dp[2] = 2;
		dp[3] = 4;

		for (int i = 4; i <= n; i++)
		{
			dp[i] = dp[i - 3] + dp[i - 2] + dp[i - 1];
		}

		cout << dp[n] << endl;
	}

	return 0;
}
