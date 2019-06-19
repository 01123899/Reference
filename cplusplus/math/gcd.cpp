#include <bits/stdc++.h>
using namespace std;

typedef long long lli;

inline lli sgn(lli x){
  return ((x<0)?(-1LL):(1LL));
}


lli gcd(lli a,lli b){
  lli c = abs(a);
  lli d = abs(b);
  while(d!=0){
    lli r = c%d;
    c = d;
    d = r;
  }
  return abs(c);
}

lli lcm(lli a, lli b){
  return a * (b/gcd(a,b));
}



/**All solutions

    X = x0 + (b/d)*t
    Y = y0 - (a/d)*t

*/
lli gcd_ext(lli a,lli b,lli &s,lli &t){
  lli c = abs(a);
  lli d = abs(b);
  lli c1 = 1LL,c2 = 0LL;
  lli d1 = 0LL,d2 = 1LL;
  while(d!=0){
    lli q = c/d, r = c-d*q;
    lli r1 = c1 - d1*q,r2 = c2 - d2*q;
    c = d, d = r;
    c1 = d1, c2 = d2;
    d1 = r1, d2 = r2;
  }

  s = c1*sgn(a)*sgn(c);
  t = c2*sgn(b)*sgn(c);
  return abs(c);
}




int main(){
  lli a,b;
  cin >> a >> b;
  cout << gcd(a,b) << "\n";
  lli s,t;
  lli g = gcd_ext(a,b,s,t);
  cout << a << "*" << s << " + ";
  cout << b << "*" << t << " = ";
  cout << g << "\n";
}
