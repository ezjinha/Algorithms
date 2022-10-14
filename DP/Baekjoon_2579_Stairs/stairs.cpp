#include <iostream>
using namespace std;

int n;	// 1 <= n <= 300
int stairs[301];
int dp[301];

int main()
{
	cin >> n;
	
	for (int i = 0; i < n; i++)
	{
		cin >> stairs[i];
	}

	dp[0] = stairs[0];
	dp[1] = stairs[0] + stairs[1];
	dp[2] = max(stairs[0], stairs[1]) + stairs[2];
	
	for (int i = 3; i < n; i++)
	{
		dp[i] = max(dp[i - 3] + stairs[i - 1], dp[i - 2]) + stairs[i];
	}

	cout << dp[n - 1] << endl;

	return 0;
}
