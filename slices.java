import java.util.Scanner;

public class slices {

	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		
		int t = in.nextInt();
		while (t --> 0) {
			
			int n = in.nextInt();
			int k = in.nextInt();
			
			// number of levels each player has completed
			int kelly = 0;
			int jim = 0;
			
			// whether or not each player hates the other
			boolean kellyhatesjim = false;
			boolean jimhateskelly = false;
			
			// loop through all the events
			for (int q = 0; q < n; q++) {
				String str = in.next();
				
				// Increment player level
				if (str.equals("Kelly")) kelly++;
				if (str.equals("Jim")) jim++;
				
				in.nextInt();
				
				// Check if player hates the other
				if (kelly - jim > k) jimhateskelly = true;
				if (jim - kelly > k) kellyhatesjim = true;
			}
			
			// print answer
			if (jimhateskelly && kellyhatesjim) {
				System.out.println("Their friendship is doomed");
			} else if (jimhateskelly) {
				System.out.println("Jim hates Kelly");
			} else if (kellyhatesjim) {
				System.out.println("Kelly hates Jim");
			} else {
				System.out.println("Everything is good");
			}
		}
		
		in.close();
	}
}
