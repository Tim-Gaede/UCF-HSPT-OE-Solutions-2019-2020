#include <bits/stdc++.h>

typedef int ll;

const ll MAX_HEALTH = 5e4 + 7;

ll ord[MAX_HEALTH];

struct bg_cmp {
	bool operator()(const ll& a, const ll& b) {
		return ord[a] > ord[b];
	};
};

ll simulate(const std::vector<ll>& items) {
	std::priority_queue<ll, std::vector<ll>, bg_cmp> pq;

	ll current_cost = 0, ret = 0;

	for (const auto& e : items) {
		current_cost += e;
		pq.push(e);
	}

	while (pq.size()) {
		const ll cur = pq.top(); pq.pop();
		ret += (current_cost -= cur % 2);
		if (cur / 2) {
			pq.push(cur / 2);
			pq.push(cur / 2);
		}
	}

	return ret;
}

ll pc(const std::vector<ll>& placed) {
	const ll sz = placed.size();
	for (ll i = 0; i < sz; ++i)
		ord[placed[i]] = i;
	return 0;
}

ll go(const ll& h) {
	std::vector<ll> vals;
	for (ll v = h; v; v /= 2)
		vals.push_back(v);
	std::reverse(vals.begin(), vals.end());

	std::vector<ll> placed, save_odds, save_evens;
	for (const auto& e : vals) {
		if (e % 2) {
			save_odds.push_back(e);
			continue;
		}

		save_evens.push_back(e);

		placed = save_odds;
		placed.insert(placed.end(), save_evens.begin(), save_evens.end());

		ll min = pc(placed) + simulate(placed);

		const ll save_odds_sz = save_odds.size();
		const ll save_evens_sz = save_evens.size();
		for (ll i = save_evens_sz-2 + save_odds_sz; i >= save_odds_sz; --i) {
			std::swap(placed[i], placed[i+1]);
			const ll tmp = pc(placed) + simulate(placed);
			if (min > tmp) {
				min = tmp;
				save_evens.assign(std::prev(placed.end(), save_evens_sz), placed.end());
			}
		}
	}

	placed = save_odds;
	placed.insert(placed.end(), save_evens.begin(), save_evens.end());

	// for (const auto& e : placed)
	// 	std::cerr << e << " ";
	// std::cerr << "\n";

	return pc(placed) + simulate(std::vector<ll>(1, h));
}

int main(void) {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);

	ll t; std::cin >> t;
	for (ll tt = 1, h; tt <= t; ++tt) {
		std::cin >> h;
		std::cout << "Fight #" << tt << ": " << go(h) << "\n";
	}

	return 0;
}
