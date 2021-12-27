// hanukkah.c
// Note: the output for the given hanukkah.in does NOT match hanukkah.out, but does match hanukkahJosh.out

#include <stdlib.h>
#include <stdio.h>

// min value of 2 numbers
long long int min(long long int a, long long int b) {
	return a < b ? a : b;
}

// abs value of 2 nums
long long int habs(long long int n) {
	return n > 0 ? n : -n;
}

// calculate number of moves to get from a to b, on an n-sized hanukkah graph
long long int calc(long long int n, long long int a, long long int b) {
	
	// even graph
	if (n % 2 == 0) {
		
		// a and b have the same parity
		if (a % 2 == b % 2) {
			long long int ans = habs(b - a);
			ans = min(ans, habs(ans - n)) / 2;
			return ans;
		}
		
		// a and b have different parity
		else {
			return -1;
		}
	}
	
	// odd graph
	else {
		
		// same parity
		if (a % 2 == b % 2) {
			return habs(b - a) / 2;
		}
		
		// different parity: a is even
		else if (a % 2 == 0) {
			return min(calc(n, a, 2) + calc(n, b, n), calc(n, a, n - 1) + calc(n, b, 1)) + 1;
		}
		
		// different parity: a is odd
		else {
			return min(calc(n, b, 2) + calc(n, a, n), calc(n, b, n - 1) + calc(n, a, 1)) + 1;
		}
	}

}

int main(void) {
	
	int t, T;
	long long int n, a, b;
	
	// input number of cases
	scanf("%d", &T);
	for (t = 1; t <= T; ++t) {
		
		// input n, a, b
		scanf("%lld %lld %lld", &n, &a, &b);
		
		// calculate answer
		long long int ans = calc(n, a, b);
		
		// header
		if (ans == -1LL) {
			printf("Graph #%d: Impossible\n", t);
		} else {
			printf("Graph #%d: %lld\n", t, ans);
		}
	}
	
	return EXIT_SUCCESS;
}

