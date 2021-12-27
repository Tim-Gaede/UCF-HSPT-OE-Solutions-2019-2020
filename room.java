import java.math.BigInteger;
import java.util.Scanner;

public class room {

	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		
		// read in num cases
		int T = in.nextInt();
		for (int t = 1; t <= T; t++) {
			
			// read in g and d
			int g = in.nextInt();
			BigInteger d = in.nextBigInteger();
			
			// split number into array of digits
			int[] digits = new int[7];
			for (int q = 6; q >= 0; q--) {
				digits[q] = g % 10;
				g /= 10;
			}
			
			// bin search to find answer
			long low = 10, high = Long.MAX_VALUE / 3;
			while (true) {
				
				long base = (low + high) / 2;
				
				// calculate the number
				BigInteger num = new BigInteger("" + digits[0]);
				for (int q = 1; q < 7; q++) {
					num = num.multiply(new BigInteger("" + base)).add(new BigInteger("" + digits[q]));
				}
				
				// if exceeds a long or too big
				if (num.compareTo(d) > 0) {
					high = base;
				}
				
				// if too small
				else if (num.compareTo(d) < 0) {
					low = base;
				}
				
				// if the right answer
				else {
					System.out.println("Hotel Visit #" + t + ": Base " + base);
					break;
				}
			}
		}
		
		in.close();
	}
}