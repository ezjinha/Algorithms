import java.io.FileInputStream;
import java.util.*;

public class Main {

	class Coord {
		public Coord(int y, int x) {
			this.y = y;
			this.x = x;
		}
		
		int y;
		int x;
	}
	
//	final int NORTH = 0;
//	final int EAST  = 1;
//	final int SOUTH = 2;
//	final int WEST  = 3;
	final int dy[] = {-1, 0, 1, 0};
	final int dx[] = {0, 1, 0, -1};
	
	int A[][];					// array for area
	ArrayList<Coord> openedA;			// arrayList for opened area
	boolean isChecked[][];				// array to check if population is checked
	boolean isFinished;				// flag to check if movement is finished
	int N;						// length of area
	int L;						// minimum population
	int R;						// maximum population
	int pop_sum;					// population sum
	int ans;					// number of movement
	
	Scanner sc = new Scanner(System.in);
	
	void initIsChecked() {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				isChecked[i][j] = false;
			}
		}
	}
	
	void calPop() {
		int pop_num = pop_sum / openedA.size();
		for (Coord coord : openedA) {
			A[coord.y][coord.x] = pop_num;
		}
	}
	
	boolean isMet(int y, int x, int ny, int nx) {
		int diff = A[y][x] > A[ny][nx] ? A[y][x] - A[ny][nx] : A[ny][nx] - A[y][x];
		
		return (diff >= L) && (diff <= R);
	}
	
	void movePop(Coord cod) {
		int y = cod.y;
		int x = cod.x;
		pop_sum += A[y][x];
		
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			
			if ((ny >= 0 && ny < N) &&
				(nx >= 0 && nx < N) &&
				!isChecked[ny][nx] &&
				isMet(y, x, ny, nx)) {
				isFinished = false;
				isChecked[ny][nx] = true;
			
				Coord nCod = new Coord(ny, nx);
				openedA.add(nCod);
				movePop(nCod);
			}
		}
	}
	
	void findMovableArea() {
		while (!isFinished) {
			isFinished = true;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (!isChecked[i][j]) {
						pop_sum = 0;
						isChecked[i][j] = true;
						openedA.add(new Coord(i, j));
						movePop(openedA.get(0));
						
						if (openedA.size() > 1) {
							calPop();
						}
						
						openedA.clear();
					}
				}
			}
			
			ans += 1;
			initIsChecked();
		}
		
	}
	
	void input() {
		N = sc.nextInt();
		L = sc.nextInt();
		R = sc.nextInt();
		ans = -1;
		
		A = new int[N][N];
		isChecked = new boolean[N][N];
		isFinished = false;
		openedA = new ArrayList<Coord>();
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				A[i][j] = sc.nextInt();
			}
		}
	}
	
	public Main() {
		int T = sc.nextInt();		// number of testcase
		
		for (int test_case = 1; test_case <= T; test_case++) {
			input();
			findMovableArea();
			System.out.println(ans);
		}
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Main();
	}

}
