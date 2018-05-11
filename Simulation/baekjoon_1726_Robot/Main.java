import java.io.FileInputStream;
import java.util.*;


public class Main {
	
	Scanner sc = new Scanner(System.in);
	
	public static final int VISITED = -1;
	public static final int UNVISITED = 0;
	
	int dy[] = { 0, 0, 1, -1 };
	int dx[] = { 1, -1, 0, 0 };
	
	int M;						// vertical line
	int N;						// horizontal line
	int map[][];				
	int ans;
	
	Robot start, finish;
	
	class Robot {
		int y;
		int x;
		int dir;
		int move_cnt;
		int cmd_cnt;
		
		Robot(int _y, int _x, int _dir, int _move_cnt, int _cmd_cnt) {
			y = _y;
			x = _x;
			dir = _dir;
			move_cnt = _move_cnt;
			cmd_cnt = _cmd_cnt;
		}
	}
	
	public Main() {
		input();
		findRoute();
		
		System.out.println(ans);
	}
	
	void input() {
		M = sc.nextInt();
		N = sc.nextInt();
		
		map = new int[M][];
		for (int i = 0; i < M; i++)
			map[i] = new int[N];
		
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				map[i][j] = sc.nextInt();
		start = new Robot(sc.nextInt() - 1, sc.nextInt() - 1, sc.nextInt(), 0, 0);
		finish = new Robot(sc.nextInt() - 1, sc.nextInt() - 1, sc.nextInt(), 0, 0);
	}
	
	void findRoute() {
		Queue<Robot> q = new LinkedList<>();		// queue for BFS
		
		q.add(start);
		map[start.y][start.x] = VISITED;
		
		while (!isFinished(q.peek())) {
			Robot head = q.poll();
			int y = head.y;
			int x = head.x;
			int dir = head.dir;
			int move_cnt = head.move_cnt;
			int cmd_cnt = head.cmd_cnt;
			
			for (int i = 0; i < 4; i++) {
				int ny = y + dy[i];
				int nx = x + dx[i];
				int nDir = i + 1;
				int nMove_cnt = move_cnt;
				int nCmd_cnt = cmd_cnt;
				
				if ((ny >= 0 && ny < M) &&
					(nx >= 0 && nx < N) &&
					(map[ny][nx] == UNVISITED)) {
					map[ny][nx] = VISITED;
					
					if (dir == nDir) {
						if (move_cnt == 0 || move_cnt == 4) {	// start
							nMove_cnt = 1;
							nCmd_cnt += 1;
						} else {
							nMove_cnt += 1;
						}
					} else {
						nMove_cnt = 1;
						nCmd_cnt += 2;
					}
					
					q.add(new Robot(ny, nx, nDir, nMove_cnt, nCmd_cnt));
				}
			}
		}
		
		if (q.peek().dir != finish.dir)
			ans = q.peek().cmd_cnt + 1;
		else
			ans = q.peek().cmd_cnt;
	}
	
	boolean isFinished(Robot rb) {
		if ((rb.y == finish.y) && (rb.x == finish.x))
			return true;
		return false;
	}
	
	
	public static void main(String[] args) throws Exception {
		// TODO Auto-generated method stub
		System.setIn(new FileInputStream("input.txt"));
		
		new Main();
	}

}
