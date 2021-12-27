
import java.util.Arrays;
import java.util.Scanner;

/*
Solution to Corgi 2 by David Harmeyer

Each time Charles picks a corgi, he ends up taking home the entire connected component that it is in.
The chance that a component doesn't get picked is (ways to pick k dogs not in component)/(ways to pick k dogs)
The chance that it does get picked is 1-chanceDoesn't

By linearity of expectations, we can sum the expected chance each component gets picked times its size to 
get the expected total number of corgis taken home

You can either calculate the sizes of each component with several graph traversals (BFS/DFS from each unvisited
node), or you can use disjoint sets to easily handle that for you.
 */
public class corgi {

	public static void main(String[] args) {
		Scanner fs=new Scanner(System.in);
		int T=fs.nextInt();
		for (int tt=1; tt<=T; tt++) {
			int n=fs.nextInt(), m=fs.nextInt(), k=fs.nextInt();
			double expected=0;
			DisjointSet dj=new DisjointSet(n);
			for (int i=0; i<m; i++) {
				int a=fs.nextInt()-1, b=fs.nextInt()-1;
				dj.union(a, b);
			}
			for (int i=0; i<n; i++) {
				if (dj.find(i)!=i) continue;
				int size=dj.size[i];
				double chanceWontTake=nChooseK(n-size, k)/nChooseK(n, k);
				double chanceWillTake=1-chanceWontTake;
				expected+=size*chanceWillTake;
			}
			if (Math.round(expected*100000)%100==50||Math.round(expected*100000)%100==49) {
				System.out.println("Broke on testcase "+tt);
				System.out.println(expected);
			}
			System.out.printf("Pond #%d: %.3f\n", tt, expected);
		}
	}
	
	static double nChooseK(int n, int k) {
		if (k>n)
			return 0;
		double prev=1;
		for (long c=1; c<=k; c++)
			prev=(prev*(n-c+1))/c;
		return prev;
	}
	
	static class DisjointSet {
		int[] s;
		int[] size;
		
		public DisjointSet(int n) {
			Arrays.fill(s = new int[n], -1);
			Arrays.fill(size=new int[n], 1);
		}
		
		public int find(int i) {
			return s[i] < 0 ? i : (s[i] = find(s[i]));
		}
		
		public boolean union(int a, int b) {
			if ((a = find(a)) == (b = find(b))) return false;
			if(s[a] == s[b]) {
				s[a]--;
			}
			if(s[a] <= s[b]) {
				s[b] = a;
				size[a]+=size[b];
			}
			else {
				s[a] = b;
				size[b]+=size[a];
			}
			return true;
		}
	}

	
	
}
