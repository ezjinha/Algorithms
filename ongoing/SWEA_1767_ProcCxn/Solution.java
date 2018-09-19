import java.io.FileInputStream;
import java.util.*;

public class Solution {

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
	Coord[] core = new Coord[12];						// array of core coordination
	ArrayList<Integer> seq;							// array of sequence
	int[][] cell;								// array of cell
	int N;									// size of cell	
	int core_cnt;								// count of core
	int len_sum;								// length sum
	int max_cnt;								// maximum count of core
	int min_len;								// minimum length of line
	
	
	void connectLine() {
		int pcell[][] = new int[N][N];
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				pcell[i][j] = cell[i][j];
			}
		}
		
		int sum = 0, cnt = 0;
		
		for (int i = 0; i < core_cnt; i++) {
			int y = core[i].y, x = core[i].x;
			
			while (true) {
				y += dy[seq.get(i)];
				x += dx[seq.get(i)];
				if (y < 0 || y >= N || x < 0 || x >= N) {
					cnt += 1;
					break;
				}
				
				if (pcell[y][x] == 1)
					return;
				else
					pcell[y][x] = 1;
				sum++;
			}
		}
		if (max_cnt < cnt) {
			max_cnt = cnt;
			min_len = sum;
		}
		else if (max_cnt == cnt && min_len > sum)
			min_len = sum;
	}
	
	void dfs(int n) {
		if (n == core_cnt) {
			connectLine();
			return;
		}
		
		for (int i = 0; i < 4; i++) {
			seq.add(i);
			dfs(n + 1);
			seq.remove(seq.size() - 1);
		}
	}
	
	void input() {
		seq = new ArrayList<>();
		N = sc.nextInt();
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
			dfs(0);
			
			System.out.println("#" + test_case + " " + min_len);
		}
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
