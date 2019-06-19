#include <bits/stdc++.h>
using namespace std;

typedef long long lli;
const lli mod = 1e9 + 7;


vector<vector<lli>> compute_pascal(lli n,lli mod = mod){
  vector< vector<lli> > pascal(n+1,vector<lli>());
  for(int i=0;i<=n;i++){
    pascal[i].push_back(1);
    for(int j=1;j<i;j++){
      lli value = (pascal[i-1][j] + pascal[i-1][j-1])%mod;
      pascal[i].push_back(value);
    }
    pascal[i].push_back(1);
  }
  return pascal;
}

int main(){
  int N = 100;
  vector< vector<lli> > pascal = compute_pascal(N);

  while(true){
    int n,k;
    cin >> n >> k;
    cout <<  pascal[n][k] << "\n";
  }
}
