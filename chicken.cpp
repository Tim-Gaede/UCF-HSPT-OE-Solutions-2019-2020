/*
Atharva and Chicken Solution
Problem Author: Charles Bailey
Solution Author: Atharva Nagarkar

This problem can be solved with simple dynamic programming.
Our state will be dp[day], which represents the expected number of pickles on the "day"th day.
This state relies on two other values:
	1. if we don't get pickles, then we go forward one day like normal
	2. otherwise, we skip "d" days ahead
Thus, one can solve the problem starting from the last day. This way, all states that are needed to solve for a smaller day have already been solved.
*/

#include <bits/stdc++.h>

using namespace std;

const int N = (int) (2e5 + 100);

int t, n, d;
double p;
double dp[N];

int main() {
	cout.precision(16);
	cin >> t;
	while(t-->0) {
		cin >> n >> d >> p;
		fill(dp, dp + n + n, 0);
		for(int day = n - 1; day >= 0; --day) {
			double skip = (1 - p) * dp[day + 1]; //if we don't get pickles, we go to the next day; the probability of this happening is (1 - probability of getting pickles)
			double choose = 0; //otherwise, there is a 1/3 * p probability of getting 1, 2, or 3 pickles, which makes a total of p probability of getting any pickles at all.
			for(int i = 1; i <= 3; ++i) {
				choose += 1.0 / 3.0 * p * (i + dp[day + d]);  //this also takes us to the (day + d)'th day, which we have already computed
			}
			dp[day] = skip + choose; //simply add the two expected values to get the expected value for the current day
		}
		cout << dp[0] << endl;
	}
}