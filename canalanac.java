
import java.util.ArrayList;
import java.util.Scanner;

/*
Solution to Canalanac by David Harmeyer

Intended solution:
DP[totalWaterLevel][indexAt][width] = minNumberOfSectionsNeeded
transition: try all widths
50_000 * 25 * 25 state, transition of about 25/2

Slower solution:
DP[totalWaterLevel][sectionsLeft][indexAt][width] = whether or not it is possible
transition: try all widths
50_000 * 25 * 25 * 25 state, transition O(1), can use bitsets to divide space usage by 64 

it might be possible to remove a factor of 25 from the transition with a data structure
but this would be annoying to code and only save a factor of like 10 even if it could be
done in constant time.
 
 */


/*
3
5 3
4 4 1 1 2

5 1
4 4 1 1 2

10 1
1 1 1 1 1 1 1 1 1 1

1
21 21
8 6 7 5 3 1 9 8 6 7 5 3 1 9 8 6 7 5 3 1 9

1
9 4
67 77 83 45 79 9 9 87 61

1
11 3
100 100 100 100 100 100 100 100 100 100 100 
 */
public class canalanac {
	final static int MAX_ANS=52025 + 1;
	static boolean[] isPal;
	static ArrayList<Integer> allPalindromes=new ArrayList<>();
	static int tt=1;

	public static void main(String[] args) {
		Scanner fs=new Scanner(System.in);
		int T=fs.nextInt();
//		long time=System.currentTimeMillis();
		precomp();
		dp=new int[26][26][MAX_ANS];
		version=new int[26][26][MAX_ANS];
		for (; tt<=T; tt++) {
			n=fs.nextInt();
			int k=fs.nextInt();
			int[] a=new int[n];
			for (int i=0; i<n; i++) a[i]=fs.nextInt()+1;
			for (int i=0; i<n; i++) a[i]=Math.max(a[i], a[n-1-i]);
			int ans=solve(n, k, a);
			System.out.println("Canal #"+tt+": "+(ans==-1?"Impossible":""+ans));
		}
//		System.err.println("Took "+(System.currentTimeMillis()-time)+" ms");
	}
	
	static int solve(int n, int nSections, int[] heights) {
		if (nSections<3 && n%10==0) {
			//then everything has to be the same height,
			// but that height will be a multiple of 10, so not possible
			return -1;
		}
		minHeight=new int[n][n];
		for (int i=0; i<n; i++)
			for (int j=i; j<n; j++) {
				int max=heights[i];
				for (int k=i; k<=j; k++) max=Math.max(max, heights[k]);
				minHeight[i][j]=max;
			}
		
		for (int pal:allPalindromes) {
			if (go(pal, 0, 0)<=nSections) return pal;
		}
		throw null;
	}
	
	
	static int[][] minHeight;
	static int[][][] dp;
	static int[][][] version;
	static int n;
	static final int oo=1_000_000_00;
	
	//returns the minSectionsAllowed, or 1e8 if impossible
	static int go(int waterLevelLeft, int index, int width) {
		if (waterLevelLeft<0) return oo;
		if (version[index][width][waterLevelLeft]==tt) return dp[index][width][waterLevelLeft];
		
		//if width==0: 
		//	transition 1: take the whole thing and return 1
		//	transition 2: brute force how many to take
		//otherwise the width is already decided:
		//	transition 1: waterLevelLeft-=width, try again with same index and width
		//		(we might want to waste some water in order to reach a palindromic total)
		//	transition 2: take this width, move on to a new index and waterLevelLeft, and undecided width
		int best=oo;
		if (width==0) {
			//try taking the whole thing
			int end=n-1-index, w=end-index+1;
			if (waterLevelLeft>=minHeight[index][end]*w && (waterLevelLeft-minHeight[index][end]*w)%w==0) {
				return 1;
			}
			
			//otherwise brute force which width to take
			//we only get here in 1/25th of the states, so the O(25) can be ignored
			for (int widthToTake=1; (index+widthToTake)*2<n; widthToTake++) {
				best=Math.min(best, go(waterLevelLeft, index, widthToTake));
			}
		}
		else {
			//our width is fixed, so try wasting some water
			best=Math.min(best, go(waterLevelLeft-width*2, index, width));
			
			//alternatively, we could just use this width
			best=Math.min(best, 2+go(waterLevelLeft-width*2*minHeight[index][index+width-1], index+width, 0));
		}
		version[index][width][waterLevelLeft]=tt;
		return dp[index][width][waterLevelLeft]=best;
	}
	
	static void precomp() {
		isPal=new boolean[1_000_000];
		for (int i=0; i<1_000_000; i++) {
			isPal[i]=isPalindrome(i);
			if (isPal[i]) allPalindromes.add(i);
		}
	}
	
	static boolean isPalindrome(int n) {
		String s=""+n;
		for (int i=0; i<s.length(); i++)
			if (s.charAt(i)!=s.charAt(s.length()-1-i)) return false;
		return true;
	}

}
