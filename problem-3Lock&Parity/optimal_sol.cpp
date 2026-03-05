#include <bits/stdc++.h>
using namespace std;

int main(){

    int N;
    cin>>N;

    vector<int>L(N);

    for(int i=0;i<N;i++)
        cin>>L[i];

    vector<int> even, odd;

    for(int j=0;j<N;j++){
        for(int i=j+1;i<N;i++){

            if(L[j]==L[i]) continue;

            int cost=abs(L[j]-L[i]);

            if(cost%2==0)
                even.push_back(cost);
            else
                odd.push_back(cost);
        }
    }

    sort(even.begin(),even.end());
    sort(odd.begin(),odd.end());

    long long ans=LLONG_MAX;

    if(!even.empty())
        ans=min(ans,(long long)even[0]);

    if(!even.empty() && !odd.empty())
        ans=min(ans,(long long)even[0]+odd[0]);

    int k=min(even.size(),odd.size());

    for(int i=1;i<=k;i++){

        if(i<even.size()){

            long long sum=0;

            for(int j=0;j<i;j++)
                sum+=odd[j];

            for(int j=0;j<i;j++)
                sum+=even[j];

            ans=min(ans,sum);
        }
    }

    if(ans==LLONG_MAX)
        cout<<-1;
    else
        cout<<ans;

}