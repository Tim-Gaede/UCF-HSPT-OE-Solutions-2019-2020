#include <bits/stdc++.h>

typedef long long ll;

const ll MAX_N = 1007;

struct DSU {
    std::vector<ll> s;
    DSU (const ll& _n) {
        s.assign(_n, -1);
    }
    ll find(const ll& i) {
        return s[i] < 0 ? i : (s[i] = find(s[i]));
    }
    bool join(ll a, ll b) {
        if ((a=find(a)) == (b=find(b))) return false;
        if (s[a] == s[b]) s[a]--;
        if (s[a] <= s[b]) s[b] = a; else s[a] = b;
        return true;
    }
};

ll n, m, k, cmp_sz[MAX_N];

int main(void) {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout << std::setprecision(3) << std::fixed;

	ll t; std::cin >> t;
	for (ll tt = 1; tt <= t; ++tt) {
		memset(cmp_sz, 0, sizeof(cmp_sz));

		std::cin >> n >> m >> k;
		DSU sets(n);

		/* take in edges and immediately union the corgos */
		for (ll i = 0, a, b; i < m; ++i) {
			std::cin >> a >> b;
			sets.join(a-1, b-1);
		}

		/* get component sizes by freq of parent */
		for (ll i = 0; i < n; ++i)
			cmp_sz[sets.find(i)]++;
		/* i love corgis because they are floofy and do speedy zoomies */

		double ans = 0;
		std::sort(cmp_sz, cmp_sz + n);
		for (ll i = n-1; i >= 0 && cmp_sz[i]; --i) {
			/*
			    For each component, calculate the probability that
			    no corgi from that component is ever picked.
			    The probability that a component is picked at some point
				is simply the complement (1 - x) of that probability.
			*/
			double prob = 1;
			for (ll phase = 0; phase < k; ++phase)
				prob *= (0.0 + n - cmp_sz[i] - phase) / (n - phase);

			/* Each component contributes some scalar times its size to the answer. */
			ans += cmp_sz[i] * (1 - prob);
		}

		std::cout << "Pond #" << tt << ": " << ans << "\n";
	}

	return 0;
}
