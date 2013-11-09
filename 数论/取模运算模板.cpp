#include<cstdio>
#include<iostream>
#include<cstring>
#include<cmath>
#include<algorithm>

using namespace std;

typedef long long LL;
LL mod = 1000000007;

struct ll {
    LL v;
    ll() {}
    ll(LL v): v(v) {}
    int getit() {
        return (cin >> v) != 0;
    }
};

void gcd(LL a, LL b, LL &d, LL &x, LL &y) {
    if(!b) {d = a; x = 1; y = 0;}
    else {gcd(b, a % b, d, y, x); y -= x * (a / b); }
}

LL inv(LL a) {
    LL d, x, y;
    gcd(a, mod, d, x, y);
    return d == 1 ? (x + mod) % mod : -1;
}

ll operator + (ll a, ll b) {return ll((a.v % mod + b.v % mod) % mod); }
ll operator - (ll a, ll b) {return ll((a.v % mod - b.v % mod + mod) % mod); }
ll operator * (ll a, ll b) {return ll(a.v % mod * b.v % mod); }
ll operator / (ll a, ll b) {return ll(a.v % mod * inv(b.v % mod) % mod); }

ll operator + (ll a, LL b) {return ll((a.v % mod + b % mod) % mod); }
ll operator - (ll a, LL b) {return ll((a.v % mod - b % mod + mod) % mod); }
ll operator * (ll a, LL b) {return ll(a.v % mod * b % mod); }
ll operator / (ll a, LL b) {return ll(a.v % mod * inv(b % mod) % mod); }

ll quickpow(ll a, ll n) {
    ll ans = 1;
    while(n.v) {
        if(n.v & 1) {
            ans = ans * a;
        }
        a = a * a;
        n.v >>= 1;
    }
    return ans;
}

ll f(ll a, ll k) {
    if(k.v == 0) return 0;
    ll ans = (quickpow(a, k) - 1) / (a - 1);
    return ans;
}

ll g(ll a, ll k) {
    if(k.v == 0) return 0;
    ll ans = ((k - 1) * quickpow(a, k) - f(a, k) + 1) / (a - 1);
    return ans;
}


ll n, a0, xa, ya, b0, xb, yb;

int main()
{
    while ( n.getit() ) {
        a0.getit(); xa.getit(); ya.getit();
        b0.getit(); xb.getit(); yb.getit();

        if(n.v == 0) {
            printf("0\n");
            continue;
        }

        if(xa.v > xb.v) {
            swap(a0, b0); swap(xa, xb); swap(ya, yb);
        }

        ll ans = 0;
        ll ta = a0 * (xa - 1) + ya;
        ll tb = b0 * (xb - 1) + yb;
        ll nn = n * (n - 1) / 2;
        ll nnn = n * (n - 1) * (2 * n - 1) / 6;

        if(xa.v == 0 && xb.v == 0) {
            ans = a0 * b0 + (n-1) * ya * yb;
            cout << ans.v << endl;
        } else if(xa.v == 0 && xb.v == 1) {
            ans = (a0 * b0 + (n - 1) * ya * b0 + nn * ya * yb);
            cout << ans.v << endl;
        } else if(xa.v == 0 && xb.v > 1) {
            ans = (ya * tb * (f(xb, n) - 1) - (n - 1) * ya * yb) / (xb - 1) + a0 * b0;
            cout << ans.v << endl;
        } else if(xa.v == 1 && xb.v == 1) {
            ans = (n * a0 * b0 + nn * (a0 * yb + b0 * ya) + ya * yb * nnn);
            cout << ans.v << endl;
        } else if(xa.v == 1 && xb.v > 1) {
            ans = (a0 * tb * f(xb, n) - n * a0 * yb + ya * tb * g(xb, n) - ya * yb * nn) / (xb - 1);
            cout << ans.v << endl;
        } else {
            ans = (ta * tb * f(xa*xb, n) - ya * tb * f(xb, n) - yb * ta * f(xa, n) + n * ya * yb) / (xa - 1) / (xb - 1);
            cout << ans.v << endl;
        }
    }

    return 0;
}
