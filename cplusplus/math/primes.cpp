#include <bits/stdc++.h>
using namespace std;

typedef long long lli;

inline lli to_power(lli a, lli e){
  lli ans = 1LL;
  while(e){
    if(e&1){
      ans = (ans * a);
    }
    a = a * a;
    e>>=1;
  }
  return ans;
}


/*  Find max k : a^k | n! */
lli find_max_k(lli a,lli n){
  lli ans = 0, base = a;
  while(base<=n){
    ans += (n/base);
    base = (base*a);
  }
  return ans;
}


// <= 10^7
vector<int> compute_cribe(int n){
  vector<int> cribe(n+1,0);
  for(int i=4;i<=n;i+=2)
    cribe[i] = 2;
  for(int i=3;i*i<=n;i+=2){
    if(cribe[i] == 0){
      for(int j= i*i;j<=n;j+=i*2){
        if(cribe[j]==0)
          cribe[j] = i;
      }
    }
  }
  return cribe;
}

// <= 10^7
vector<int> compute_primes(vector<int> &cribe,int n){
  vector<int> primes;
  primes.push_back(2);
  for(int i=3;i<=n;i+=2){
    if(cribe[i] == 0)
      primes.push_back(i);
  }
  return primes;
}

// <= 10^14
vector<pair<lli,int>> compute_prime_factors(vector<int> &primes, vector<int> &cribe, lli n){
  vector< pair<lli,int> > prime_factors;
  int index_prime = 0;
  while(index_prime < primes.size() && n>10000000){
    lli pi = primes[index_prime];
    int power = 0;
    while(n%pi == 0){
      power++;
      n/=pi;
    }
    if(power){
      prime_factors.push_back({pi,power});
    }
    index_prime++;
  }

  if(n>10000000){
    prime_factors.push_back({n,1});
    return prime_factors;
  }

  while(cribe[n]){
    int first_prime = cribe[n];
    int power = 0;
    while(n%first_prime == 0){
      n/=first_prime;
      power++;
    }
    prime_factors.push_back({first_prime,power});
  }

  if(n != 1)
    prime_factors.push_back({n,1});

  return prime_factors;
}





void compute_divisors(vector<lli> &divisors,vector<pair<lli,int>> &prime_factors,lli number = 1LL,int index = 0){
  if(index == prime_factors.size()){
    divisors.push_back(number);
    return;
  }
  lli next_number = number;
  for(int i=0;i<=prime_factors[index].second;i++){
    compute_divisors(divisors,prime_factors,next_number,index + 1);
    next_number = next_number * prime_factors[index].first;
  }
}

lli number_of_divisors( vector<pair<lli,int>> &prime_factors){
  lli ans = 1LL;
  for(auto &x: prime_factors){
    ans = (ans*(1LL + x.second));
  }
  return ans;
}


lli sum_of_divisors(vector<pair<lli,int>> &prime_factors){
  lli ans = 1LL;
  for(auto &x: prime_factors){
    lli temp = to_power(x.first,x.second+1) - 1LL;
    temp /= (x.first - 1LL);
    ans = (ans * temp);
  }
  return ans;
}



lli phi(vector<pair<lli,int>> &prime_factors){
  lli ans = 1LL;
  for(auto &x: prime_factors){
    ans = ans * to_power(x.first,x.second-1LL);
    ans = ans * (x.first-1LL);
  }
  return ans;
}



int main(){
  int N = 10000000;
  vector<int> cribe = compute_cribe(N);
  vector<int> primes = compute_primes(cribe,N);
  lli M;
  cin >> M;
  vector< pair<lli,int> > prime_factors = compute_prime_factors(primes,cribe,M);
  vector<lli> divisors;
  compute_divisors(divisors,prime_factors);

  cout << "number of divisors:\n";
  cout << number_of_divisors(prime_factors) << "\n";
  for(auto x: divisors){
    cout << x << " ";
  }cout << "\n";

  cout << "sum of divisors:\n";
  cout << sum_of_divisors(prime_factors) << "\n";

  cout << "phi:\n";
  cout << phi(prime_factors) << "\n";

  return 0;
}
