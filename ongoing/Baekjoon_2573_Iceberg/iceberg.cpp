#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
    int y;
    int x;
    Coord() {}
    Coord(int _y, int _x) : y(_y), x(_x) {}
};

int N;			                    // row
int M;			                    // column
int sea[300][300];                  // array of sea
int melted[300][300];               // array for saving melted iceberg amount
bool checked[300][300];             // array for checking if iceberg is checked
int ans;                            // answer
const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, -1, 0, 1};


bool isInArea(int y, int x)
{
    if ((y >= 0 && y < N) && (x >= 0 && x < M))
        return true;
    return false;
}

int numOfAdjoinedIceberg(int st_y, int st_x)
{
    int cnt = 1;
    checked[st_y][st_x] = true;
    queue<Coord> q;
    q.push(Coord(st_y, st_x));

    while (!q.empty())
    {
        int y = q.front().y;
        int x = q.front().x;

        for (size_t i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (!checked[ny][nx] && isInArea(ny, nx))
            {
                checked[ny][nx] = true;
                q.push(Coord(ny, nx));
                cnt += 1;
            }
        }
        q.pop();
    }

    return cnt;
}

int meltedAmount(int y, int x)
{
    int n = 0;
    for (size_t i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (sea[ny][nx] == 0)
            n += 1;
    }

    return n;
}

bool areAllMelted()
{
    bool areAllMelted = true;
    int num = 0;
    for (size_t i = 1; i < N - 1; i++)
    {
        for (size_t j = 1; j < M - 1; j++)
        {
            if (sea[i][j] != 0)
            {
                num += 1;
                areAllMelted = false;
            }
        }
    }

    ans = 0;
    if (num == 1)           // If iceberg is only one, time should not be elapsed
        return true;

    return areAllMelted;
}

void timeElapse()
{
    int t = 0;

    while (!areAllMelted())
    {
        int st_y, st_x;
        int iceberg_num = 0;
        // check how much iceberg is being melted
        for (size_t i = 1; i < N - 1; i++)
        {
            for (size_t j = 1; j < M - 1; j++)
            {
                melted[i][j] = meltedAmount(i, j);
            }
        }

        // apply iceberg melting
        for (size_t i = 1; i < N - 1; i++)
        {
            for (size_t j = 1; j < M - 1; j++)
            {
                sea[i][j] = sea[i][j] - melted[i][j] < 0 ? 0 : sea[i][j] - melted[i][j];
                melted[i][j] = 0;

                if (sea[i][j] != 0)
                {
                    checked[i][j] = false;
                    st_y = i;
                    st_x = j;
                    iceberg_num += 1;
                }
                else
                {
                    checked[i][j] = true;
                }
                
            }
        }

        t += 1;
        if (iceberg_num != numOfAdjoinedIceberg(st_y, st_x))
        {
            ans = t;
            break;
        }
    }
    
}

int main()
{
    ifstream cin("input.txt");

    for (int test_case = 1; test_case <= 3; test_case++)
    {
        // input
        cin >> N >> M;

        for (size_t i = 0; i < N; i++)
        {
            for (size_t j = 0; j < M; j++)
            {
                cin >> sea[i][j];
                checked[i][j] = sea[i][j] == 0 ? true : false;
            }
        }

        timeElapse();
        cout << ans << endl;
    }
    
}
