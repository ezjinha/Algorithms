import java.io.FileInputStream;
import java.util.Scanner;

public class Solution {
	
	public static final String grade[] = {"A+", "A0", "A-", 
										  "B+", "B0", "B-",
										  "C+", "C0", "C-",
										  "D0"};
	
	Scanner sc = new Scanner(System.in);
	int N;			// number of students
	int K;			// Kth student
	double list[];
	String ans;
	
	public Solution() {
		int test_case = sc.nextInt();
		
		for (int i = 1; i <= test_case; i++) {
//		for (int i = 1; i <= 1; i++) {
			input();
			giveGrade();
			
			System.out.println("#" + i + " " + giveGrade());
		}
	}
	
	void input() {
		N = sc.nextInt();
		K = sc.nextInt();
		
		list = new double[N];
		
		for (int i = 0; i < N; i++) {
			int mid_score = sc.nextInt();
			int final_score = sc.nextInt();
			int assign_score = sc.nextInt();
			
			list[i] = mid_score * 0.35 + final_score * 0.45 + assign_score * 0.2;
		}
	}

	String giveGrade() {
		int rank = 0;
		String given_grade = null;
		
		for (int i = 0; i < N; i++) {
			if (list[K - 1] <= list[i])
				rank++;
		}

		for (int i = 1; i <= 10; i++) {
			if (rank <= N / 10 * i) {
				given_grade = grade[i - 1];
				break;
			}
		}
		
		return given_grade;
	}

	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		
		new Solution();
	}

}
