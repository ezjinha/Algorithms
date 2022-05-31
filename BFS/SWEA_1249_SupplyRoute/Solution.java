import java.io.FileInputStream;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class Solution {

	class Node {
		int y;
		int x;
		int time;

		public Node(int y, int x, int time) {
			this.y = y;
			this.x = x;
			this.time = time;
		}
	}

	final int dy[] = { 0, -1, 1, 0 };
	final int dx[] = { -1, 0, 0, 1 };

	Scanner sc = new Scanner(System.in);
	int N;
	int map[][];
	int dp[][];
	int min_time;

	void findRoute() {
		Queue<Node> q = new LinkedList<>();
		q.add(new Node(0, 0, 0));

		while (!q.isEmpty()) {
			Node node = q.poll();
			int y = node.y;
			int x = node.x;
			int time = node.time;

			if (y == N - 1 && x == N - 1) {
				min_time = min_time > time ? time : min_time;
			}

			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];

				if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
					int nTime = time + map[ny][nx];
					if (nTime < dp[ny][nx]) {
						dp[ny][nx] = nTime;
						q.add(new Node(ny, nx, nTime));
					}
				}
			}
		}
	}

	void input() {
		N = sc.nextInt();
		map = new int[N][N];
		dp = new int[N][N];
		min_time = Integer.MAX_VALUE;

		for (int i = 0; i < N; i++) {
			String str = sc.next();
			for (int j = 0; j < N; j++) {
				map[i][j] = Character.getNumericValue(str.charAt(j));
				dp[i][j] = Integer.MAX_VALUE;
			}
		}
	}

	public Solution() {
		int T = sc.nextInt();

//		for (int test_case = 1; test_case <= 6; test_case++) {
		for (int test_case = 1; test_case <= T; test_case++) {
			input();
			findRoute();
			System.out.println("#" + test_case + " " + min_time);
		}
	}

	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
