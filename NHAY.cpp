// Problem link http://www.spoj.com/problems/NHAY/
#include <iostream>
#include <vector>

using namespace std;

void constructlps (vector <long int> &lps, string &pattern) {
	// precomputation of pattern
	for (long int i = 1, j = 0; i < pattern.size(); i++) {
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
	long int length;
	string pattern;
	char c, tmp;
	while (true) {
		cin >> length >> pattern;
		vector <long int> lps (length, 0);
		constructlps (lps, pattern);
		if (getchar() == EOF)
			return 0;
		c = getchar();
		long int index = 0, i =0;
		long int chrs_matched = 0;
		while (c != '\n' && c != '\0') {
	        if (pattern[chrs_matched] == c) {
	            chrs_matched++;
	            c = getchar();
	            i++;
	        }
	        if (chrs_matched == pattern.size()) {
	            cout << i - chrs_matched << endl;
	            chrs_matched = lps[chrs_matched - 1];
	        } else if (pattern[chrs_matched] != c) {
	            if (chrs_matched != 0)
	                chrs_matched = lps[chrs_matched-1];
	            else {
	            	i++;
	                c = getchar();
	            }
	        }
	    }
	    cout << endl;
	}
}