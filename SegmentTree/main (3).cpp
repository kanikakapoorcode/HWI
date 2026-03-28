/*You’re given an array A of n integers and q queries.
Each query can be one of the following two types:
• Type 1 Query: (1, l, r) - Replace A[i] with
(i-l+1)*A[l] for each index i, where l <= i <= r.
• Type 2 Query: (2, l, r) - Calculate the sum of the
elements in A from index l to index r.
Find the sum of answers to all type 2 queries. Since
answer can be large, return it modulo 109+7.*/

/*
Testcases :
Sample Input 1
7
1
4
5
1
6
7
8
5
1 1 6
1 1 5
2 5 5
2 3 4
2 3 3
Sample Output 1
60
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
const ll MOD = 1e9 + 7;

vector<ll> seg;
vector<pair<ll,ll>> lazy; // {base, L}
int n;

ll modMul(ll a, ll b) {
    return (a % MOD * b % MOD) % MOD;
}

// sum of AP: start + (start+1) + ... + (start+len-1)
ll getAPSum(ll start, ll len) {
    ll total = (len * ((2 * start % MOD + len - 1) % MOD)) % MOD;
    total = (total * ((MOD + 1) / 2)) % MOD; // divide by 2
    return total;
}

void build(int idx, int l, int r, vector<ll>& A) {
    if (l == r) {
        seg[idx] = A[l] % MOD;
        return;
    }
    int mid = (l + r) / 2;
    build(2*idx, l, mid, A);
    build(2*idx+1, mid+1, r, A);
    seg[idx] = (seg[2*idx] + seg[2*idx+1]) % MOD;
}

void apply(int idx, int l, int r, ll base, ll L) {
    ll len = r - l + 1;
    ll start = (l - L + 1) % MOD;
    if (start < 0) start += MOD;

    ll total = getAPSum(start, len);
    seg[idx] = modMul(base, total);

    lazy[idx] = {base, L};
}

void push(int idx, int l, int r) {
    if (lazy[idx].first == -1) return;

    int mid = (l + r) / 2;

    apply(2*idx, l, mid, lazy[idx].first, lazy[idx].second);
    apply(2*idx+1, mid+1, r, lazy[idx].first, lazy[idx].second);

    lazy[idx] = {-1, -1};
}

void update(int idx, int l, int r, int ql, int qr, ll base, ll L) {
    if (r < ql || l > qr) return;

    if (ql <= l && r <= qr) {
        apply(idx, l, r, base, L);
        return;
    }

    push(idx, l, r);

    int mid = (l + r) / 2;
    update(2*idx, l, mid, ql, qr, base, L);
    update(2*idx+1, mid+1, r, ql, qr, base, L);

    seg[idx] = (seg[2*idx] + seg[2*idx+1]) % MOD;
}

ll query(int idx, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return 0;

    if (ql <= l && r <= qr) return seg[idx];

    push(idx, l, r);

    int mid = (l + r) / 2;
    return (query(2*idx, l, mid, ql, qr) +
            query(2*idx+1, mid+1, r, ql, qr)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    vector<ll> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    seg.resize(4*n);
    lazy.assign(4*n, {-1, -1});

    build(1, 0, n-1, A);

    int q;
    cin >> q;

    ll ans = 0;

    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;

        if (t == 1) {
            ll base = query(1, 0, n-1, l, l); // IMPORTANT
            update(1, 0, n-1, l, r, base, l);
        } else {
            ans = (ans + query(1, 0, n-1, l, r)) % MOD;
        }
    }

    cout << ans << "\n";
}