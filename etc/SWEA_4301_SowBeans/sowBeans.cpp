#include <iostream>
#include <fstream>

using namespace std;

int add1[4][4] = { { 1,2,2,2 },{ 1,2,2,2 },{ 0,0,1,2 },{ 0,0,1,2 } };
int add2[4][4] = { { 1,2,2,2 },{ 0,1,2,2 },{ 0,0,1,2 },{ 1,1,1,2 } };

int main()
{
	ifstream cin("input.txt");
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; test_case++)
	{
		int N, M;
		cin >> N >> M;
		int ans1 = 0, ans2 = 0;
		for (int i = 0; i < M; i++)
		{
			ans1 += ((N - 1) / 4) * 2 + add1[i % 4][(N - 1) % 4];
			ans2 += ((N - 1) / 4) * 2 + add2[i % 4][(N - 1) % 4];
		}
		int ans = ans1 > ans2 ? ans1 : ans2;
		cout << '#' << test_case << ' ' << ans << endl;
	}
	return 0;
}