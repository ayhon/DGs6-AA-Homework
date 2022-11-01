//Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

mt19937 rnd(time(nullptr));

using Score = int;
using Id = int;

void handle_queries(***){
	int k; cin >> k;
}

void process_good_deeds() {
	int n, t, b;
	cin >> n >> t >> b;

	unordered_map<Id, Score> good_deeds;
	for(int i = 0; i <n; i++){
		int id, score; cin >> id >> score;
		good_deeds[id] = score;
	}

	// TODO //

}

void process_bad_deeds() {
	int n, t, b;
	cin >> n >> t >> b;

	int m; cin >> m;
	vector<int> prev_values(m);
	for(auto & e : prev_values) cin >> e;

	unordered_map<Id, Score> bad_deeds;
	for(int i = 0; i <n; i++){
		int id, score; cin >> id >> score;
		bad_deeds[id] = score;
	}

	// TODO //

	handle_queries(***);
}

int main() {
	int s; cin >> s;
	if (s == 1) 
		process_good_deeds();
	else 
		process_bad_deeds();
	return 0;
}

