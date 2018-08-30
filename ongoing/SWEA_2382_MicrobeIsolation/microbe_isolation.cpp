#include <iostream>
#include <vector>
using namespace std;
 
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;
 
class Microbe
{
public:
    int y;
    int x;
    int num;
    int dir;
 
    Microbe() {}
    Microbe(int _y, int _x, int _num, int _dir) : y(_y), x(_x), num(_num), dir(_dir) {}
};
 
vector<Microbe> gp;            // vector of microbe
vector<bool> coincided;        // vector of merged
int N;                         // number of cell
int M;                         // isolation time
int K;                         // number of group
int ans;                       // answer
 
void calculate()
{
    for (size_t i = 0; i < gp.size(); i++)
    {
        ans += gp[i].num;
    }
}
 
void merge()
{
    for (size_t i = 0; i < gp.size() - 1; i++)
    {
        int max_num = gp[i].num;
        int num = gp[i].num;
        int dir = gp[i].dir;
        for (size_t j = i + 1; j < gp.size(); j++)
        {
            if (!coincided[j] && gp[i].y == gp[j].y && gp[i].x == gp[j].x)
            {
                coincided[j] = true;
                if (max_num < gp[j].num)
                {
                    max_num = gp[j].num;
                    dir = gp[j].dir;
                }
                num += gp[j].num;
            }
        }
        gp[i].num = num;
        gp[i].dir = dir;
    }
 
    int i = 0;
    while (i != gp.size())
    {
        if (coincided[i])
		      {
			          gp.erase(gp.begin() + i);
			          coincided.erase(coincided.begin() + i);
		      }
        else
            i++;
}
 
void move()
{
    for (size_t i = 0; i < gp.size(); i++)
    {
        switch (gp[i].dir)
        {
        case UP:
            gp[i].y -= 1;
            break;
        case DOWN:
            gp[i].y += 1;
            break;
        case LEFT:
            gp[i].x -= 1;
            break;
        case RIGHT:
            gp[i].x += 1;
            break;
        }
 
        if (gp[i].y == 0 || gp[i].y == N - 1 || gp[i].x == 0 || gp[i].x == N - 1)
        {
            gp[i].num /= 2;
 
            switch (gp[i].dir)
            {
            case UP:
                gp[i].dir = DOWN;
                break;
            case DOWN:
                gp[i].dir = UP;
                break;
            case LEFT:
                gp[i].dir = RIGHT;
                break;
            case RIGHT:
                gp[i].dir = LEFT;
                break;
            }
        }
    }
}
 
int main()
{
    int T;              // count of testcase
    cin >> T;
 
    for (int test_case = 1; test_case <= T; test_case++)
    {
        ans = 0;
        gp.clear();
        coincided.clear();
        int y, x, num, dir;
        cin >> N >> M >> K;
 
        // input
        for (int i = 0; i < K; i++)
        {
            cin >> y >> x >> num >> dir;
            gp.push_back(Microbe(y, x, num, dir));
            coincided.push_back(false);
        }
 
        for (int i = 0; i < M; i++)
        {
            move();
            merge();
        }
 
        calculate();
        cout << '#' << test_case << ' ' << ans << endl;
    }
 
    return 0;
}
