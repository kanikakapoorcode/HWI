#include <bits/stdc++.h>
using namespace std;

int kadane(vector<int>& a){
    int best = INT_MIN, cur = 0;
    for(int x : a){
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

int main(){
    int n,k;
    cin>>n;
    cin>>k;

    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    int ans = kadane(a);

    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){

            vector<int>b = a;

            vector<int> inside, outside;

            for(int x=i;x<=j;x++) inside.push_back(b[x]);
            for(int x=0;x<i;x++) outside.push_back(b[x]);
            for(int x=j+1;x<n;x++) outside.push_back(b[x]);

            sort(inside.begin(),inside.end());
            sort(outside.begin(),outside.end(),greater<int>());

            int swaps = min(k,(int)min(inside.size(),outside.size()));

            for(int s=0;s<swaps;s++){
                if(outside[s] > inside[s])
                    swap(inside[s],outside[s]);
            }

            int sum=0;
            for(int x:inside) sum+=x;

            ans=max(ans,sum);
        }
    }

    cout<<ans;
}