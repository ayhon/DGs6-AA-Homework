#include <bits/stdc++.h>
using namespace std;

int32_t n, t, b;
uint32_t R;
uint32_t B;

vector<uint32_t> hashes;
vector<uint32_t> signs;

uint32_t myhash(uint32_t seed, uint32_t val) {
	// https://github.com/skeeto/hash-prospector
	val++;
	val ^= val >> 17;
	// seed ^= val;
	val *= 0xed5ad4bb;
	val ^= seed;
	val ^= val >> 11;
	// seed ^= val;
	val *= 0xac4c1b51;
	val ^= val >> 15;
	// seed ^= val;
	val *= 0x31848bab;
	val ^= val >> 14;
	seed ^= val;

	return seed;
}
int mysign(uint32_t seed, uint32_t val) {
	// use parity of the number of 1 bits in the hash
	uint32_t h = myhash(seed, val);
	int cnt = __builtin_popcount(h);
	return cnt % 2 == 0 ? -1 : 1;
}

void proc1() {
	// Create bins {{{
	int32_t bins[R][B];
	for (uint32_t i = 0; i < R; i++) {
		for (uint32_t j = 0; j < B; j++) {
			bins[i][j] = 0;
		}
	}
	// }}}

	for (uint32_t i = 0; i < n; i++) {
		uint32_t id, val;
		cin >> id >> val;

		map<uint32_t, int> myhashes;
		for (uint32_t j = 0; j < R; j++) {
			uint32_t h = myhash(hashes[j], id) % B;
			int s = mysign(signs[j], id);
			// cerr << id << " " << val << " " << h << " " << s << endl;
			// good deeds: use opposite sign
			bins[j][h] -= s * val;
		}
	}

	cout << (R * B) << endl;
	for (uint32_t i = 0; i < R; i++) {
		for (uint32_t j = 0; j < B; j++) {
			cout << bins[i][j] << " ";
		}
	}
	cout << endl << flush;
}

void proc2() {
	int32_t bins[R][B];
	uint32_t m;

	cin >> m;
	assert(m == R * B);
	for (uint32_t i = 0; i < R; i++) {
		for (uint32_t j = 0; j < B; j++) {
			cin >> bins[i][j];
		}
	}

	for (uint32_t i = 0; i < n; i++) {
		uint32_t id, val;
		cin >> id >> val;
		for (uint32_t j = 0; j < R; j++) {
			uint32_t h = myhash(hashes[j], id) % B;
			int s = mysign(signs[j], id);
			// bad deeds: use sign directly
			bins[j][h] += s * val;
		}
	}

	uint32_t k;
	cin >> k;
	int32_t vals[R];
	for (uint32_t i = 0; i < k; i++) {
		uint32_t q;
		cin >> q;

		for (uint32_t j = 0; j < R; j++) {
			uint32_t h = myhash(hashes[j], q) % B;
			int s = mysign(signs[j], q);
			vals[j] = s * bins[j][h];
		}
		sort(vals, vals + R);

		int32_t estim =
			R % 2 == 0 ? (vals[R / 2 - 1] + vals[R / 2]) / 2 : vals[R / 2];

		// cerr << q << ": " << estim << endl;
		// flush to be safe
		cout << (estim >= t ? "Yes" : "No") << endl << flush;
	}
}

int main() {
	uint32_t p;
	cin >> p >> n >> t >> b;

	// chosen after trial and error basically
	// make sure the two factors aren't over 300
	R = 27;
	B = 11 * (b + 1);

	mt19937 gen;
	for (int i = 0; i < R; i++) {
		hashes.push_back(gen());
		signs.push_back(gen());
	}

	if (p == 1) {
	proc1();
} else {
	proc2();
	}
	return 0;
}
