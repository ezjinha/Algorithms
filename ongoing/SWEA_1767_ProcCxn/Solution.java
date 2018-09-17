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
	Coord[] core = new Coord[12];				// array of core coordination
	boolean[] visited = new boolean[12];		// check if visited
	int[][] cell;								// array of cell
	int N;										// size of cell	
	int K;										// size of core
	int core_cnt;								// count of core
	int len_sum;								// length sum
	int max_cnt;								// maximum count of core
	int min_len;								// minimum length of line
	
	
	void connectLine() {
		
	}
	
	void findShortestLine() {
		for (int i = 0; i < core_cnt; i++) {
			int y = core[i].y;
			int x = core[i].x;
			int min_dir = -1;
			int min_len = N;
			
			for (int j = 0; j < 4; j++) {
				int ny = y + dy[j];
				int nx = x + dx[j];
				int len = 0;
				
				while (true) {
					if (ny == 0 || ny == N - 1 || nx == 0 || nx == N - 1) {
						if (min_len > len) {
							min_dir = j;
							min_len = len;
						}
						break;
					}
					if (cell[ny][nx] == 1 || cell[ny][nx] == 2)
						break;
					
					ny += dy[j];
					nx += dx[j];
					len++;
				}
			}
			System.out.println(min_dir + " " + min_len);
		}
	}
	
	void input() {
		N = sc.nextInt();
		cell = new int[N][N];
		core_cnt = -1;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cell[i][j] = sc.nextInt();
				if ((i != 0 && i != N - 1) &&
					(j != 0 && j != N - 1) &&
					cell[i][j] == 1) {
					core[++core_cnt] = new Coord(i, j);
				}
			}
		}
	}
	
	public Solution() {
		int T = sc.nextInt();		// number of testcase
		
//		for (int test_case = 1; test_case <= T; test_case++) {
		for (int test_case = 1; test_case <= 1; test_case++) {
			input();
			findShortestLine();
		}
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
