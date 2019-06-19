#include <bits/stdc++.h>
using namespace std;

typedef long long lli;
const lli mod = 1e9 + 7;

lli to_power(lli a, lli e,lli mod){
  lli ans = 1LL;
  while(e){
    if(e&1){
      ans = (ans*a)%mod;
    }
    a = (a*a)%mod;
    e>>=1LL;
  }
  return ans;
}


vector<lli> compute_factorials(int n,lli mod){
  vector<lli> factorial(n+1,0);
  factorial[0] = 1LL;
  for(lli i=1;i<=n;i++){
    factorial[i] = (factorial[i-1]*i)%mod;
  }
  return factorial;
}

vector<lli> compute_inverses(int n,lli fn,lli mod){
  vector<lli> inverse(n+1,0);
  inverse[n] = to_power(fn,mod-2,mod);
  for(lli i=n-1;i>=0;i--){
    inverse[i] = inverse[i+1]*(i+1LL)%mod;
  }
  return inverse;
}


/*
  n!/ k! (n-k)!
  check if k<=n first
*/
lli nck(lli fn,lli invk,lli invn_k,lli mod){
  lli ans = (fn * invk)%mod;
  ans = (ans*invn_k)%mod;
  return ans;
}



vector<vector<lli>> compute_pascal(lli n,lli mod ){
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
  vector< vector<lli> > pascal = compute_pascal(N,mod);
  vector<lli> factorial = compute_factorials(N,mod);
  vector<lli> inverse = compute_inverses(N,factorial[N],mod);
  while(true){
    int n,k;
    cin >> n >> k;
    cout <<  pascal[n][k] << "\n";
    cout << nck(factorial[n],inverse[k],inverse[n-k],mod) << "\n";
  }
}
