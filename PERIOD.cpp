// Problem link: http://www.spoj.com/problems/PERIOD/
#include <iostream>

using namespace std;

long int lps[1000005] = {0};

void compute_lps (string pattern) {
	for (int i = 1, j = 0; i < pattern.size(); i++) {
		if (pattern [i] == pattern [j]) {
			lps [i] = j + 1;
			j++;
		} else if ( j != 0 ) {
			j = lps [ j - 1];
			i--;
		} else {
			lps [i] = 0;
		}
	}
}

int main() {
	int test, length, ca = 1;
	string str;
	cin >> test;
	while (test--) {
		cin >> length;
		cin >> str;
		compute_lps (str);
		cout<< "Test case #" << ca++;
		for (long int i = 1; i < str.size(); i++) {
			if (lps[i] != 0 && (i + 1) % ((i + 1) - lps[i]) == 0)
				cout << (i + 1)<< " " << (i + 1) / ((i + 1) - lps[i]) << endl;
		}
		cout << endl;
	}
}