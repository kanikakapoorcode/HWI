/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

int kadane(vector<int>& a){
    int best = INT_MIN;
    int cur = 0;

    for(int x : a){
        cur = max(x, cur + x);
        best = max(best, cur);
    }

    return best;
}

int solve(vector<int>& a, int k){
    int n = a.size();

    if(k == 0){
        return kadane(a);
    }

    int ans = INT_MIN;

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){

            swap(a[i], a[j]);

            ans = max(ans, solve(a, k - 1));

            swap(a[i], a[j]); // backtrack
        }
    }

    return ans;
}

int main(){
    int n, k;
    cin >> n >> k;

    vector<int> a(n);

    for(int i = 0; i < n; i++)
        cin >> a[i];

    cout << solve(a, k) << endl;
}