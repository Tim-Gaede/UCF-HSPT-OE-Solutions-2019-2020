import java.util.Scanner;

/*
Solution to Pangramic Judges by David Harmeyer

Since there are only 16 judges, we can check all 2^16 possible
subsets of judges, and, among all that use every letter,
find the one that includes the fewest elements.
 */
public class judges {

	public static void main(String[] args) {
		Scanner fs=new Scanner(System.in);
		int T=fs.nextInt();
		for (int tt=1; tt<=T; tt++) {
			int n=fs.nextInt(); fs.nextLine();
			int[] names=new int[n];
			for (int i=0; i<n; i++)
				for (char c:fs.nextLine().toLowerCase().toCharArray())
					if (c!=' ')
						names[i]|=1<<(c-'a');
			int fewestPeople=n+1;
			for (int mask=0; mask<1<<n; mask++) {
				int letters=0;
				for (int i=0; i<n; i++)
					if ((mask&(1<<i))!=0)
						letters|=names[i];
				if (letters+1==1<<26)
					fewestPeople=Math.min(fewestPeople, Integer.bitCount(mask));
			}
			System.out.printf("Judge List #%d: %d\n", tt, fewestPeople==n+1?-1:fewestPeople);
		}
	}

}
