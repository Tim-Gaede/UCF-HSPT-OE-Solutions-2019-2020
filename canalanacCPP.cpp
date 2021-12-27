#include <bits/stdc++.h>
using namespace std;
const int MAX_ANS=52025+1;
const int oo=100000000;

int tt=1;
bool isPal[100000];
vector<int> allPalindromes;
int minHeight[51][51];
int dp[26][26][MAX_ANS], version[26][26][MAX_ANS];
int n;

bool isPalindrome(int n) {
	vector<int> digits;
	while (n!=0) {
		digits.push_back(n%10);
		n/=10;
	}
	for (int i=0; i<digits.size(); i++)
		if (digits[i]!=digits[digits.size()-1-i]) return false;
	return true;
}

void precomp() {
	for (int i=0; i<100000; i++) {
		isPal[i]=isPalindrome(i);
		if (isPal[i]) allPalindromes.push_back(i);
	}

	//I probably don't need to do this, but I'm paranoid about arrays in C++
	for (int i=0; i<26; i++)
		for (int j=0; j<26; j++)
			for (int k=0; k<MAX_ANS; k++)
				version[i][j][k]=0;
}

int go(int waterLevelLeft, int index, int width) {
	if (waterLevelLeft<0) return oo;
	if (version[index][width][waterLevelLeft]==tt) 
		return dp[index][width][waterLevelLeft];

	int best=oo;
	if (width==0) {
		int end=n-1-index, w=end-index+1;
		if (waterLevelLeft>=minHeight[index][end]*w 
				&& (waterLevelLeft-minHeight[index][end]*w)%w==0) {
			return 1;
		}
		for (int widthToTake=1; (index+widthToTake)*2<n; widthToTake++) {
			best=min(best, go(waterLevelLeft, index, widthToTake));
		}
	}
	else {
		best=min(best, go(waterLevelLeft-width*2, index, width));

		best=min(best, 2+
				go(waterLevelLeft-width*2*minHeight[index][index+width-1], 
					index+width, 0));
	}
	version[index][width][waterLevelLeft]=tt;
	return dp[index][width][waterLevelLeft]=best;
}

int solve(int n, int nSections, vector<int> heights) {
	if (nSections<3 && n%10==0) {
		return -1;
	}
	for (int i=0; i<n; i++)
		for (int j=i; j<n; j++) {
			int maxVal=heights[i];
			for (int k=i; k<=j; k++) maxVal=max(maxVal, heights[k]);
			minHeight[i][j]=maxVal;
		}
	for (int pal:allPalindromes) {
		if (go(pal, 0, 0) <= nSections) return pal;
	}
	assert(false);
	return -1;
}

int main() {
	precomp();

	int T; cin>>T;
	for (; tt<=T; tt++) {
		int k; cin>>n>>k;
		vector<int> a(n, 0);
		for (int i=0; i<n; i++) cin>>a[i];
		for (int i=0; i<n; i++) a[i]++;
		for (int i=0; i<n; i++) a[i]=max(a[i], a[n-1-i]);
		int ans=solve(n, k, a);
		cout<<"Canal #"<<tt<<": ";
		if (ans==-1) cout<<"Impossible\n";
		else cout<<ans<<'\n';
	}
	return 0;
}
