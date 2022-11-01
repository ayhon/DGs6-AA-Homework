// Author: Ayhon
#include <bits/stdc++.h>
using namespace std;

void first() {
	int a, b;
	cin >> a >> b;
	cout << a * b << endl;
}

void second() {
	int d, c; cin >> d >> c;
	cout << d + c << endl;
}

int main() {
	int t;
	cin >> t;
	if (t == 1)
		first();
	else
		second();
	return 0;
}
