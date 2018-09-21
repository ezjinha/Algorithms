import java.io.FileInputStream;
import java.util.Scanner;

public class Solution {

	final int LEFT  = 0;
	final int UP    = 1;
	final int RIGHT = 2;
	final int DOWN  = 3;
	// LEFT, UP, RIGHT, DOWN
	final int[] dy  = {0, -1, 0, 1};
	final int[] dx  = {-1, 0, 1, 0};
	
	class Coord {
		int y;
		int x;
		
		Coord() {}
		Coord(int _y, int _x) {
			y = _y;
			x = _x;
		}
	}
	
	Scanner sc = new Scanner(System.in);
	Coord[] core = new Coord[12];				// array of core coordination
	boolean[] visited = new boolean[12];		// check if visited
	int[][] cell;								// array of cell
	int N;										// size of cell	
	int core_cnt;								// count of core
	int max_cnt;								// maximum count of core
	int min_len;								// minimum length of line
	
	
	boolean isConflicted(int y, int x, int dir) {
		while (y != 0 && y != N - 1 && x != 0 && x != N - 1) {
			y += dy[dir];
			x += dx[dir];
			
			if (cell[y][x] != 0)
				return true;
		}
		return false;
	}
	
	int sumLineLength(int y, int x, int dir, boolean connected) {
		int len_sum = 0;
		while (y != 0 && y != N - 1 && x != 0 && x != N - 1) {
			y += dy[dir];
			x += dx[dir];
			len_sum++;
			
			cell[y][x] = connected ? 0 : 2;
		}
		return len_sum;
	}
	
	void findMinLen(int core_idx, int core_num, int len) {
		if (core_idx == core_cnt) {
			if (max_cnt < core_num) {
				max_cnt = core_num;
				min_len = len;
			} else if (max_cnt == core_num) {
				min_len = min_len > len ? len : min_len;
			}
		} else {
			for (int i = 0; i < 4; i++) {
				int y = core[core_idx].y;
				int x = core[core_idx].x;
				if (!isConflicted(y, x, i)) {
					findMinLen(core_idx + 1, core_num + 1, len + sumLineLength(y, x, i, false));
					sumLineLength(y, x, i, true);
				}
			}
			findMinLen(core_idx + 1, core_num, len);
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
	}
	
	public Solution() {
		int T = sc.nextInt();		// number of testcase
		
		for (int test_case = 1; test_case <= T; test_case++) {
//		for (int test_case = 1; test_case <= 1; test_case++) {
			input();
			findMinLen(0, 0, 0);
			System.out.println("#" + test_case + " " + min_len);
		}
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
