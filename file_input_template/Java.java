import java.io.FileInputStream;
import java.util.Scanner;

/* Name of Class */
// Baekjoon: Main
// SWEA: Solution
public class Java {
    Scanner sc = new Scanner(System.in);

    public Java() {
    }

    public static void main(String[] args) throws Exception {
        System.setIn(new FileInputStream("input.txt"));
        new Java();
    }
}