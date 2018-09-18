import java.io.FileInputStream;
import java.util.Scanner;

public class Solution {

	// LEFT, UP, RIGHT, DOWN
	final int LEFT  = 0;
	final int UP    = 1;
	final int RIGHT = 2;
	final int DOWN  = 3;
	final int[] dy  = {0, -1, 0, 1};
	final int[] dx  = {-1, 0, 1, 0};
	
	class Coord {
		int y;
		int x;
		int dir;
		int len;
		
		Coord() {}
		Coord(int _y, int _x) {
			y = _y;
			x = _x;
			dir = -1;
			len = 0;
		}
	}
	
	Scanner sc = new Scanner(System.in);
	Coord[] core = new Coord[12];					// array of core coordination
	boolean[] visited = new boolean[12];				// check if visited
	int[] seq;							// connection sequence
	int[][] cell;							// array of cell
	int N;								// size of cell	
	int K;								// size of core
	int core_cnt;							// count of core
	int max_cnt;							// maximum count of core
	int min_len;							// minimum length of line
	
	void removeLine() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (cell[i][j] == 2)
					cell[i][j] = 0;
			}
		}
	}
	
	void connectLine(Coord cod) {
		int dir = cod.dir;
		
		if (dir == -1)
			return;
		else {
			int y = cod.y;
			int x = cod.x;
			
			while (y != 0 && y != N - 1 && x != 0 && x != N - 1) {
				y += dy[dir];
				x += dx[dir];
				
				cell[y][x] = 2;
			}
		}
	}
	
	void findShortestLine(Coord cod) {
		int y = cod.y;
		int x = cod.x;
		int min_dir = -1;
		int min_l = N;
		
		for (int j = 0; j < 4; j++) {
			int ny = y;
			int nx = x;
			int len = 0;
			
			while (true) {
				ny += dy[j];
				nx += dx[j];
				len++;
				
				if (cell[ny][nx] == 1 || cell[ny][nx] == 2)
					break;
				if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) {
					if (min_l > len) {
						min_dir = j;
						min_l = len;
					}
					break;
				}
			}
		}
		
		cod.dir = min_dir;
		cod.len = min_l;
		
		connectLine(cod);
	}
	
	void dfs(int st, int n) {
		if (n == core_cnt) {
			int cnt = 0;
			int sum = 0;
			for (int i = 0; i < core_cnt; i++) {
				findShortestLine(core[seq[i]]);
				int dir = core[seq[i]].dir;
				int len = core[seq[i]].len;
				
				cnt = dir != -1 ? ++cnt : cnt;
				sum += len;
			}
			
			if (max_cnt <= cnt) {
				max_cnt = cnt;
				min_len = min_len > sum ? sum : min_len;
			}
			removeLine();
			
			return;
		}
		
		for (int i = 0; i < core_cnt; i++) {
			if (!visited[i]) {
				visited[i] = true;
				seq[i] = n;
				dfs(i + 1, n + 1);
				visited[i] = false;
			}
		}
	}
	
	void input() {
		N = sc.nextInt();
		max_cnt = 0;
		min_len = N * N;
		cell = new int[N][N];
		core_cnt = 0;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cell[i][j] = sc.nextInt();
				if ((i != 0 && i != N - 1) &&
					(j != 0 && j != N - 1) &&
					cell[i][j] == 1) {
					core[core_cnt++] = new Coord(i, j);
				}
			}
		}
		
		seq = new int[core_cnt];
	}
	
	public Solution() {
		int T = sc.nextInt();		// number of testcase
		
		for (int test_case = 1; test_case <= T; test_case++) {
//		for (int test_case = 1; test_case <= 1; test_case++) {
			input();
			dfs(0, 0);
			System.out.println("#" + test_case + " " + min_len);
		}
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
