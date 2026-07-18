// 14_suffix_array.cpp - Suffix Array: Doubling Algorithm O(T log T)
// Knowledge points: suffix definition, sorting suffixes, pattern matching

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ===== Suffix Array Construction using Doubling Algorithm =====
// Time: O(T log T), Space: O(T)
struct SuffixInfo {
    int rank[2];  // rank for current 2^k chars
    int idx;      // original index in string
};

vector<int> buildSuffixArray(const string& T) {
    int n = T.size();
    vector<int> sa(n);       // suffix array
    vector<int> rankArr(n);  // rank array
    vector<int> temp(n);     // temporary rank

    // Step 1: Sort by 1st character (1-order)
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rankArr[i] = T[i];  // ASCII value as initial rank
    }

    // Step 2: Doubling - sort by 2^k characters
    for (int k = 1; k < n; k *= 2) {
        // Compare suffixes by (rank[i], rank[i+k]) pair
        auto compare = [&](int a, int b) {
            if (rankArr[a] != rankArr[b])
                return rankArr[a] < rankArr[b];
            int ra = (a + k < n) ? rankArr[a + k] : -1;
            int rb = (b + k < n) ? rankArr[b + k] : -1;
            return ra < rb;
        };

        sort(sa.begin(), sa.end(), compare);

        // Assign new ranks
        temp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            temp[sa[i]] = temp[sa[i - 1]] + (compare(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rankArr = temp;

        // Early termination: if all ranks are unique, we're done
        if (rankArr[sa[n - 1]] == n - 1) break;
    }

    return sa;
}

// ===== Pattern Matching using Suffix Array =====
// Find all occurrences of pattern P in text T
// Time: O(|P| * log|T|)
void findPattern(const string& T, const vector<int>& sa, const string& P) {
    int n = T.size(), m = P.size();

    // Find lower bound: first suffix >= P
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        string suffix = T.substr(sa[mid]);
        if (suffix.substr(0, min(m, (int)suffix.size())) < P)
            lo = mid + 1;
        else
            hi = mid;
    }

    // Check if the position actually matches
    bool found = false;
    cout << "  Pattern \"" << P << "\" found at positions: ";
    for (int i = lo; i < n && sa[i] + m <= n; i++) {
        if (T.substr(sa[i], m) == P) {
            cout << sa[i] << " ";
            found = true;
        } else {
            break;
        }
    }
    if (!found) cout << "(not found)";
    cout << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  Suffix Array Demo" << endl;
    cout << "========================================" << endl;

    string T = "mississippi";
    int n = T.size();

    cout << "\nText: \"" << T << "\" (length " << n << ")" << endl;
    cout << "\nAll suffixes:" << endl;
    for (int i = 0; i < n; i++)
        cout << "  S[" << i << "] = \"" << T.substr(i) << "\"" << endl;

    // Build suffix array
    cout << "\n--- Building Suffix Array (Doubling Algorithm) ---" << endl;
    vector<int> sa = buildSuffixArray(T);

    cout << "\nSuffix Array (sorted suffixes):" << endl;
    for (int i = 0; i < n; i++)
        cout << "  SA[" << i << "] = " << sa[i]
             << " -> \"" << T.substr(sa[i]) << "\"" << endl;

    // Pattern matching
    cout << "\n--- Pattern Matching ---" << endl;
    findPattern(T, sa, "ssip");
    findPattern(T, sa, "i");
    findPattern(T, sa, "pi");
    findPattern(T, sa, "mississippi");
    findPattern(T, sa, "xyz");

    // Demo with another string
    cout << "\n========================================" << endl;
    string T2 = "abracadabra";
    cout << "Text: \"" << T2 << "\"" << endl;

    vector<int> sa2 = buildSuffixArray(T2);
    cout << "Suffix Array:" << endl;
    for (int i = 0; i < (int)sa2.size(); i++)
        cout << "  SA[" << i << "] = " << sa2[i]
             << " -> \"" << T2.substr(sa2[i]) << "\"" << endl;

    cout << "\nPattern matching:" << endl;
    findPattern(T2, sa2, "abra");
    findPattern(T2, sa2, "bra");
    findPattern(T2, sa2, "a");

    cout << "\n========================================" << endl;
    cout << "  Suffix Array Properties" << endl;
    cout << "========================================" << endl;
    cout << "Suffix(T, i) = T[i..n-1] (substring from position i to end)" << endl;
    cout << "Suffix Array: sorted indices of all suffixes" << endl;
    cout << "Key insight: any substring of T is a prefix of some suffix" << endl;
    cout << "Pattern matching: binary search on suffix array" << endl;
    cout << "  - Compare pattern with suffix at mid point" << endl;
    cout << "  - O(|P| * log|T|) time" << endl;
    cout << "\nDoubling Algorithm:" << endl;
    cout << "  - Sort by 1st char, then 2nd, then 4th, 8th, ..." << endl;
    cout << "  - L-order to 2L-order: compare (rank[i], rank[i+L]) pairs" << endl;
    cout << "  - O(log T) phases, each O(T) with radix sort" << endl;
    cout << "  - Total: O(T log T)" << endl;
    cout << "\nSuffix Tree:" << endl;
    cout << "  - Compact trie of all suffixes" << endl;
    cout << "  - O(T) nodes, O(T) storage" << endl;
    cout << "  - Pattern matching: O(|P|) time" << endl;

    return 0;
}
