// Solution to fraud for HSPT Online 2019
// Author: John Edwards

import java.util.*;
import java.io.*;

public class fraud
{
	int t, tt = 0, n, d;
	int[][] e, from;
	Integer[][][] memo;
	
    fraud(Scanner in, PrintWriter out)
    {
    	t = in.nextInt();
    	while (++tt <= t)
    	{
	    	n = in.nextInt();
	    	d = in.nextInt();
	    	e = new int[n][2];
	    	for (int i = 0; i < n; i++)
	    	{
	    		e[i][0] = in.nextInt();
	    		e[i][1] = in.nextInt();
	    	}
	    	
	    	// sort the voters based by ascending
	    	// cost for the opponent. doing this
	    	// allows us to do a dp on the cost to us
	    	// knowing that the minimal cost to the opp.
	    	// will always be a prefix of what we skipped
	    	Arrays.sort(e, (a, b) -> a[1]-b[1]);
	    	
	    	// calculate how many people we can bribe
	    	// from the ith person on given each amount of money
	    	from = new int[n][d+1];
	    	for (int i = n-1; i >= 0; i--)
	    		for (int j = n-1; j >= i; j--)
	    			for (int m = d; m >= e[j][0]; m--)
	    				from[i][m] = Math.max(from[i][m], 1+from[i][m-e[j][0]]);
	    	
	    	// if from the beginning we could bribe
	    	// half of the voters then the opp. loses
	    	out.print("Election #"+tt+": ");
	    	if (from[0][d] > n/2)
	    		out.println(-1);
	    	
	    	// otherwise run the dp to see how much
	    	// they needed to spend to win
	    	else
	    	{
	    		memo = new Integer[n][2*n+1][d+1];
	    		out.println(dp(0, 0, d));
	    	}
    	}
    }
    
    int dp(int at, int del, int funds)
    {
    	// if we make it to the end return 0
    	// because there is no more spending to do
    	if (at == n) return 0;
    	if (memo[at][del+n][funds] != null)
    		return memo[at][del+n][funds];
    	
    	int buy = 0;
    	// if we can afford this peron try buying them
    	if (funds >= e[at][0])
    		buy = dp(at+1, del+1, funds-e[at][0]);
    	
    	int skip = 0;
    	// if upon not buying opp. loses from here
    	// then try buying this person
    	if (from[at][funds]+del > 0)
    		skip = e[at][1]+dp(at+1, del-1, funds);
    		
    	// otherwise just skip this person entirely
    	else
    		skip = dp(at+1, del, funds);
    	
    	// return the max of the two answers
    	return memo[at][del+n][funds] = Math.max(buy, skip);
    }
	
	public static void main(String[] args)
	{
		Scanner in = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);
		new	fraud(in, out);
		out.close();
	}
}