#include <iostream>
using namespace std;

int main()
{
	int n;	// 1<= n <= 1000
	int tile[1001];
	cin >> n;

	tile[1] = 1;
	tile[2] = 2;

	for (int i = 3; i <= n; i++)
	{
		tile[i] = (tile[i - 1] + tile[i - 2]) % 10007;
	}

	cout << tile[n] << endl;

	return 0;
}