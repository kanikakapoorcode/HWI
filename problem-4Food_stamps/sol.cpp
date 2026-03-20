#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n ;
    long long m ;
    cin >> n >> m ;
    vector<long long> v(n), d(n);
    for(int i = 0 ; i < n ; i++) cin >> v[i];
    for(int i = 0 ; i < n ; i++) cin >> d[i];
    //binary search
    long long low  = 0 , high = INT_MAX , T = 0 ;
    while(low <= high){
        long long mid = (low + high)/2;
        long long count = 0 ;
        for(int i = 0 ; i< n ; i++){
            if(v[i] >= mid){
                count += (v[i]-mid)/d[i]+1;
                if(count >= m) break;
            }
        }
        if( count >= m) {
            T = mid;
            low = mid + 1;
        }
        else {
            high = mid-1;
        }
    }
    long long total = 0 , cnt = 0 ;
    for(int i = 0 ; i < n ; i++){
        if(v[i] >= T){
            long long k = (v[i]-T)/d[i]+1;
            long long last = v[i]-(k-1)*d[i];
            total += k*(v[i]+last)/2;
            cnt += k;
        }
    }
    if(cnt > m){
        total -= (cnt - m)*T;
    }
    cout << total << endl;
    return 0 ;
}