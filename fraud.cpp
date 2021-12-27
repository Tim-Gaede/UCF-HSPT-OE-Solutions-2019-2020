#include <bits/stdc++.h>

typedef int ll;

const ll MAX_N = 77;
const ll MAX_D = 1007;
const ll INF = 0x3f3f3f3f;

ll n, d, c[2][MAX_N], pc[MAX_N][MAX_D], ord[MAX_N];
ll memo[MAX_N][200][MAX_D];

ll go(const ll& cur, const ll& score, const ll& money_left) {
	if (cur >= n)
		return score > 0 ? -INF : 0;

	ll& ret = memo[cur][score + 100][money_left];
	if (ret != -1) return ret;
	ret = -INF;

	// me take
	if (money_left >= c[0][ord[cur]])
		ret = std::max(ret, go(cur+1, score+1, money_left - c[0][ord[cur]]));

	// does opponent need to take
	if (score + pc[cur][money_left] > 0) {
		ret = std::max(ret, c[1][ord[cur]] + go(cur+1, score - 1, money_left));
	} else {
		ret = std::max(ret, go(cur+1, score, money_left));
	}

	return ret;
}

int main(void) {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	ll t; std::cin >> t;
	for (ll tt = 1; tt <= t; ++tt) {
		memset(memo, 0xff, sizeof(memo));

		// std::cout << "TEST CASE " << tt << ": \n";

		std::cin >> n >> d;
		for (ll i = 0; i < n; ++i)
			std::cin >> c[0][i] >> c[1][ord[i] = i];

		std::sort(ord, ord + n, [&](const ll& a, const ll& b){
			return c[1][a] < c[1][b];
		});

		// std::cout << "n = " << n << " and d = " << d << "\n";
		// for (ll i = 0; i < n; ++i)
		// 	std::cout << c[0][ord[i]] << " " << c[1][ord[i]] << "\n";

		memset(pc, 0, sizeof(pc));
		std::multiset<ll> set;
		for (ll i = n-1; i >= 0; --i) {
			set.insert(c[0][ord[i]]);
			auto it = set.begin();
			for (ll mon = 0, spent = 0, ans = 0; mon <= d; ++mon) {
				if (it != set.end() && spent + *it <= mon) {
					spent += *it; ++it;
					++ans;
				}
				pc[i][mon] = ans;
				// std::cerr << pc[i][mon] << " ";
			}
			// std::cerr << "\n";
		}

		// std::cout << "pc[0][d] = " << pc[0][d] << "\n";

		ll ans;
		if (pc[0][d] > n / 2) {
			ans = -1;
		} else {
			ans = std::max(go(0, 0, d), -1);
		}

		std::cout << "Election #" << tt << ": " << ans << std::endl;
	}

	return 0;
}
