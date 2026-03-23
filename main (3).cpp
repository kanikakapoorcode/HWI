#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll mod = 1e9 + 7;

struct SegTree {

    struct Node{
        ll sum = 0;
        bool lazy = false;
        ll base = 0;
        ll offset = 0;
    };

    int n;
    vector<Node> seg;

    SegTree(int n){
        this->n = n;
        seg.resize(4*n);
    }

    ll getSum(ll first, ll d, ll n) {
        return (n * (2*first + (n-1)*d) / 2) % mod;
    }

    void build(int ind , int l , int r , vector<ll>& arr){
        if(l == r){
            seg[ind].sum = arr[l];
            seg[ind].lazy = false;
            seg[ind].base = 0;
            seg[ind].offset = 0;
            return;
        }

        int mid = (l+r)/2;
        build(2*ind, l, mid, arr);
        build(2*ind+1, mid+1, r, arr);

        seg[ind].sum = (seg[2*ind].sum + seg[2*ind+1].sum) % mod;
    }

    void apply(int ind, int l, int r, ll base, ll offset) {
        ll len = r - l + 1;

        ll first = (offset + 1) * base % mod;
        ll d = base;

        seg[ind].sum = getSum(first, d, len);

        seg[ind].lazy = true;
        seg[ind].base = base;
        seg[ind].offset = offset;
    }

    void push(int ind, int l , int r){
        if(!seg[ind].lazy) return;

        int mid = (l+r)/2;

        ll base = seg[ind].base;
        ll offset = seg[ind].offset;

        // left
        apply(2*ind, l, mid, base, offset);

        // right
        ll new_offset = offset + (mid - l + 1);
        apply(2*ind+1, mid+1, r, base, new_offset);

        seg[ind].lazy = false;
    }

    void update(int ind, int l, int r, int ql, int qr, ll base) {

        if(r < ql || l > qr) return;

        if(ql <= l && r <= qr) {
            ll offset = l - ql;
            apply(ind, l, r, base, offset);
            return;
        }

        push(ind, l, r);

        int mid = (l+r)/2;

        update(2*ind, l, mid, ql, qr, base);
        update(2*ind+1, mid+1, r, ql, qr, base);

        seg[ind].sum = (seg[2*ind].sum + seg[2*ind+1].sum) % mod;
    }

    ll query(int ind, int l, int r, int ql, int qr) {

        if(r < ql || l > qr) return 0;

        if(ql <= l && r <= qr)
            return seg[ind].sum;

        push(ind, l, r);

        int mid = (l+r)/2;

        return (query(2*ind, l, mid, ql, qr) +
                query(2*ind+1, mid+1, r, ql, qr)) % mod;
    }
};
int main() {
    int n;
    cin >> n;

    vector<ll> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];

    SegTree st(n);
    st.build(1, 0, n-1, arr);

    int q;
    cin >> q;

    ll ans = 0;

    while(q--) {
        int type, l, r;
        cin >> type >> l >> r;

        if(type == 1) {
            ll base = st.query(1,0,n-1,l,l); 
            st.update(1, 0, n-1, l, r, base);
        }
        else {
            ans = (ans + st.query(1, 0, n-1, l, r)) % mod;
        }
    }

    cout << ans << endl;
}