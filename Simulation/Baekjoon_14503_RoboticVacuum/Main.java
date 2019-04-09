import java.io.FileInputStream;
import java.util.Scanner;

public class Main {

	final int NORTH = 0;
	final int EAST  = 1;
	final int SOUTH = 2;
	final int WEST  = 3;
	final int dy[] = {-1, 0, 1, 0};
	final int dx[] = {0, 1, 0, -1};
	
	int area[][];	// array for area | cleaned: 2, wall: 1, uncleaned: 0
	int N;			// vertical line
	int M;			// horizontal line
	int r, c;		// start coordination
	int d;			// direction
	int ans;		// answer
	
	Scanner sc = new Scanner(System.in);
	
	int rotCounterClock(int dir, int idx) {
		dir = dir - idx - 1;
		return dir < 0 ? dir + 4 : dir;
	}
	
	void clean(int y, int x, int dir) {
		if (area[y][x] == 0) {
			area[y][x] = 2;
			ans++;
		}
		
		for (int i = 0; i < 4; i++) {
			int ndir = rotCounterClock(dir, i);
			int ny = y + dy[ndir];
			int nx = x + dx[ndir];
		
			if (area[ny][nx] == 0) {
				clean(ny, nx, ndir);
				return;
			}
				
			if (i == 3) {
				ndir = rotCounterClock(dir, 1);
				ny = y + dy[ndir];
				nx = x + dx[ndir];
				
				if (area[ny][nx] == 1)
					return;
				else {
					clean(ny, nx, dir);
					return;
				}
			}
		}
	}
	
	void input() {
		N = sc.nextInt();
		M = sc.nextInt();
		r = sc.nextInt();
		c = sc.nextInt();
		d = sc.nextInt();
		ans = 0;
		
		area = new int[N][M];
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				area[i][j] = sc.nextInt();
			}
		}
	}
	
	public Main() {
		int T = sc.nextInt();		// number of testcase
		
		for (int test_case = 1; test_case <= T; test_case++) {
//		for (int test_case = 1; test_case <= 1; test_case++) {
			input();
			clean(r, c, d);
			System.out.println(ans);
		}
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Main();
	}

}
