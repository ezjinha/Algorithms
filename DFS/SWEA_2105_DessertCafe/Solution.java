import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Solution {

	final int dy[] = { 1, 1 };
	final int dx[] = { -1, 1 };

	Scanner sc = new Scanner(System.in);
	int N;
	int area[][];
	ArrayList<Integer> cafe_list;
	int route_num;
	int max_num;

	boolean isDuplicate(ArrayList<Integer> list, int cafe_num) {
		for (Integer cafe : list) {
			if (cafe == cafe_num)
				return true;
		}
		return false;
	}

	boolean isReturnable(int y, int ws_num, int x, int es_num) {
		int ny, nx;
		ArrayList<Integer> return_cafe_list = new ArrayList<>();

		while (ws_num != 0) {
			ny = y - dy[0];
			nx = x - dx[0];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				return false;
			} else if (isDuplicate(cafe_list, area[ny][nx]) || isDuplicate(return_cafe_list, area[ny][nx])) {
				return false;
			} else {
				return_cafe_list.add(area[ny][nx]);
				y = ny;
				x = nx;
				ws_num--;
			}
		}

		while (es_num != 0) {
			ny = y - dy[1];
			nx = x - dx[1];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				return false;
			} else if (isDuplicate(cafe_list, area[ny][nx]) || isDuplicate(return_cafe_list, area[ny][nx])) {
				return false;
			} else {
				return_cafe_list.add(area[ny][nx]);
				y = ny;
				x = nx;
				es_num--;
			}
		}

		return true;
	}

	void findRoute(int y, int ws_num, int x, int es_num, boolean is_changed) {
		if (ws_num != 0 && es_num != 0 && ws_num + es_num == route_num) {
			if (isReturnable(y, ws_num, x, es_num)) {
				int total_route_num = (ws_num + es_num) * 2;
				max_num = max_num < total_route_num ? total_route_num : max_num;
			}
			return;
		}

		for (int i = 0; i < 2; i++) {
			if (i == 0 && is_changed)
				continue;
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (ny >= 0 && ny < N && nx >= 0 && nx < N) {
				if (!isDuplicate(cafe_list, area[ny][nx])) {
					cafe_list.add(area[ny][nx]);

					int n_ws_num = i == 0 ? ws_num + 1 : ws_num;
					int n_es_num = i == 1 ? es_num + 1 : es_num;
					is_changed = i == 1 ? true : is_changed;
					findRoute(ny, n_ws_num, nx, n_es_num, is_changed);

					cafe_list.remove(Integer.valueOf(area[ny][nx]));
				}
			}
		}
	}

	public Solution() {
		int T = sc.nextInt();

		for (int test_case = 1; test_case <= T; test_case++) {
//		for (int test_case = 1; test_case <= 3; test_case++) {
			N = sc.nextInt();
			area = new int[N][N];
			cafe_list = new ArrayList<>();
			max_num = -1;

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					area[i][j] = sc.nextInt();
				}
			}

			for (int i = 0; i < N - 2; i++) {
				for (int j = 1; j < N - 1; j++) {
					for (int k = 2; k < N; k++) {
						route_num = k;
						findRoute(i, 0, j, 0, false);
					}
				}
			}

			System.out.println("#" + test_case + " " + max_num);
		}
	}

	public static void main(String[] args) throws FileNotFoundException {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
