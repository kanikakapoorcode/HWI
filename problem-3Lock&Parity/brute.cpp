#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int key;
    int lock;
    int cost;
};

int main(){

    int N;
    cin >> N;

    vector<int> L(N);

    for(int i=0;i<N;i++)
        cin >> L[i];

    vector<Edge> edges;

    // generate all possible assignments
    for(int j=0;j<N;j++){
        for(int i=j+1;i<N;i++){

            if(L[j] == L[i]) continue;

            Edge e;
            e.key = j;
            e.lock = i;
            e.cost = abs(L[j] - L[i]);

            edges.push_back(e);
        }
    }

    int E = edges.size();
    long long ans = LLONG_MAX;

    // try every subset of edges
    for(int mask = 1; mask < (1<<E); mask++){

        vector<bool> usedKey(N,false);
        vector<bool> usedLock(N,false);

        int even = 0;
        int odd = 0;
        long long cost = 0;

        bool valid = true;

        for(int i=0;i<E;i++){

            if(mask & (1<<i)){

                Edge e = edges[i];

                if(usedKey[e.key] || usedLock[e.lock]){
                    valid = false;
                    break;
                }

                usedKey[e.key] = true;
                usedLock[e.lock] = true;

                cost += e.cost;

                if(e.cost % 2 == 0)
                    even++;
                else
                    odd++;
            }
        }

        if(!valid) continue;

        if(even >= odd)
            ans = min(ans, cost);
    }

    if(ans == LLONG_MAX)
        cout << -1;
    else
        cout << ans;
}