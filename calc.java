import java.util.*;
import java.math.*;
import java.io.*;

public class calc {
	static class Button {
		char op;  int x, y;
		public Button(char op, int x, int y) {
			this.op = op;
			this.x = x;
			this.y = y;
		}
		boolean inbounds(long v) {
			return LOWER_BOUND <= v && v <= UPPER_BOUND; 
		}
		long press(long v) {
			long result = 0;
			if(op == 'A') result = v + x;
			else if(op == 'S') result = v - x;
			else if(op == 'M') result = v * x;
			else if(op == 'D') {
				if(v % x == 0) result = v / x;
				else return INVALID;
			} else if(op == 'T') {
				String num = "" + v;
				char X = (char) (x + '0');
				char Y = (char) (y + '0');
				num = num.replace(X, ' ');
				num = num.replace(' ', Y);
				result = Integer.parseInt(num);
			} else if(op == 'P') {
	     		        if (v >= 0) {
   			                result = (v * 10) + x;
				} else {
				        result = -((-v) * 10 + x);
				}
			}
			if(inbounds(result)) return result;
			else return INVALID;
		}
	}
	static final long LOWER_BOUND = -99_999_999;
	static final long UPPER_BOUND = 99_999_999;
	static final long INVALID = 1_000_000_000_000_000L;
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int v = scan.nextInt();
		for(int vv = 1 ; vv <= v ; vv++) {
			long s = scan.nextLong(), t = scan.nextLong();
			int b = scan.nextInt(), n = scan.nextInt();
			Button[] btn = new Button[n];
			for(int i = 0 ; i < n ; i++) {
				char op = scan.next().charAt(0);
				int x = scan.nextInt(), y = -1;
				if(op == 'T') y = scan.nextInt();
				btn[i] = new Button(op, x, y);
			}
			Set<Long>[] visited = new HashSet[b + 1];
			for(int i = 0 ; i < b + 1 ; i++) visited[i] = new HashSet<>();
			visited[0].add(s);
			for(int i = 0 ; i < b ; i++) {
				for(long val : visited[i]) {
					for(int j = 0 ; j < n ; j++) {
						long result = btn[j].press(val);
						if(result == INVALID) continue;
						visited[i + 1].add(result);
					}
				}
			}
			if(visited[b].contains(t)) System.out.printf("Level #%d: It can be done%n", vv);
			else System.out.printf("Level #%d: You should give up%n", vv);
		}
	}
}