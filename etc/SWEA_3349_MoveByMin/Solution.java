import java.io.FileInputStream;
import java.util.Scanner;

public class Solution {

	Scanner sc = new Scanner(System.in);
	int W;							// width
	int H;							// height
	int N;							// count of intersection
	int x1, y1, x2, y2;					// coordination value
	int ans;						// answer
	
	public Solution() {
		int T = sc.nextInt();				// count of testcase
		
		for (int test_case = 1; test_case <= T; test_case++) {
			ans = 0;
			W = sc.nextInt();
			H = sc.nextInt();
			N = sc.nextInt();
			
			for (int i = 0; i < N - 1; i++)
	        {
	            if (i == 0) {
	            	x1 = sc.nextInt();
	            	y1 = sc.nextInt();
	            	x2 = sc.nextInt();
	            	y2 = sc.nextInt();
	            } else {
	                y1 = y2;
	                x1 = x2;
	                x2 = sc.nextInt();
	                y2 = sc.nextInt();
	            }
	            moveByMin();
	        }
			System.out.println("#" + test_case + " " + ans);
		}
		
	}
	
	void moveByMin()
	{
	    if ((y1 > y2) && (x1 < x2))			// Quadrant 1
	        ans += (y1 - y2) + (x2 - x1);
	    else if ((y1 > y2) && (x1 > x2))		// Quadrant 2
	        ans += ((y1 - y2) > (x1 - x2) ? y1 - y2 : x1 - x2);
	    else if ((y1 < y2) && (x1 > x2))		// Quadrant 3
	        ans += (y2 - y1) + (x1 - x2);
	    else if ((y1 < y2) && (x1 < x2))		// Quadrant 4
	        ans += ((y2 - y1) > (x2 - x1) ? y2 - y1 : x2 - x1);
	    else if (y1 == y2)                    	// X-axis
	        ans += (x1 > x2 ? x1 - x2 : x2 - x1);
	    else if (x1 == x2)                   	// Y-axis
	        ans += (y1 > y2 ? y1 - y2 : y2 - y1);
	}
	
	public static void main(String[] args) throws Exception {
		System.setIn(new FileInputStream("input.txt"));
		new Solution();
	}

}
