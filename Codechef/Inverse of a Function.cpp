#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
#define pii pair<int,int>
#define pll pair<ll,ll>
#define eb emplace_back
#define ll long long
#define nl '\n'
#define deb(x) cerr<<#x" = "<<x<<nl
#define in() ( { int a ; scanf("%d",&a); a; } )
 
const int N = 3e5 + 9;
const int mod = 998244353;
 
int qpow(int a, int b, int m)
{
    int ans = 1 % m;
    while(b){
        if(b & 1LL) ans = 1LL * ans * a % m;
        a = 1LL * a * a % m;
        b >>= 1;
    }
    return ans;
}
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
//baby step - giant step
//find minimum integer x such that a^x = b (mod m)
//where a and m are co-prime
const int inf = 2e9;
unordered_map<int, int, chash> vals;
int DiscreteLog(int a, int b, int m)
{
    int n = (int) sqrt (m + .0) + 1;
    int an = 1;
    for (int i = 0; i < n; ++i) an = (1LL * an * a) % m;
    vals.clear();
    for (int p = 1, cur = an; p <= n; ++p)
    {
        if (!vals[cur]) vals[cur] = p;
        cur = (1LL*cur * an) % m;
    }
    int res = inf;
    for (int q = 0, cur = b; q <= n; ++q)
    {
        if (vals.find(cur) != vals.end())
        {
            ll ans = 1LL * vals[cur] * n - q;
            if(ans < res) res = ans;
        }
        cur = (1LL * cur * a) % m;
    }
    if(res == inf) res = -1;
    return res;
}
pair<ll, ll> ext_euclid(int a, int b)   // returns x, y | ax + by = gcd(a,b)
{
    if(b == 0) return pair<ll, ll>(a >= 0? 1LL : -1LL, 0LL);
    else{
        pair<ll, ll> d = ext_euclid(b, a % b);
        return pair<ll, ll>(d.second, d.first - d.second * (a / b));
    }
}
int inverse(int a, int n)  //a and n is coprime
{
    pair<ll, ll> ret = ext_euclid(a, n);
    return ((ret.first % n) + n) % n;
}
int brute(int a, int b, int m)
{
    int nw = 1 % m;
    if(nw == b) return 0;
    for(int i = 1; i < m; i++){
        nw = 1LL * nw * a % m;
        if(nw == b) return i;
    }
    return -1;
}
//Discrete Log but a and m may not be co-prime
int DLOG(int a, int b, int m)
{
    if(m == 1) return 0;
    if(b == 1) return 0;
    if(__gcd(a, m) == 1) return DiscreteLog(a, b, m);
    int g = __gcd(a, m);
    if(b % g != 0)  return -1;
    int p = inverse(a/g, m/g);
    int nw = DLOG(a , 1LL * b / g * p % (m/g), m/g);
    if(nw == -1) return -1;
    return nw + 1;
}
string mx = "1" + string(10000, '0');
int pw[10];
int32_t main()
{
    ios_base::sync_with_stdio(0);
    int invof2 = qpow(2, mod - 2, mod);
    pw[0] = 1;
    for(int i = 1; i < 10; i++) pw[i] = pw[i - 1] * 2;
    int t; cin >> t;
    assert( 1 <= t && t <= 100);
    vals.reserve(1 << 15);
    vals.max_load_factor(0.25);
    while(t--){
        string s; cin >> s;
        assert(s[0] != '0');
        assert(((int)s.size() < (int)mx.size() || ((int)s.size() == (int)mx.size() && s <= mx)));
        int x, m; cin >> x >> m;
        assert(x < m && x >= 0 && m >= 1 && m <= 1000000000);
        if(m == 1){
            cout << 0 << nl;
            continue;
        }
        if((int)s.size() == 1 && s[0] == '1'){
            if(x == 1) cout << 0 << nl;
            else cout << -1 << nl;
            continue;
        }
        if(x == 0){
            cout << 1 << nl;
            continue;
        }
        int base = 1 % m, pwof2 = 1 % mod;
        for(auto &c: s){
            base = qpow(base, 10, m);
            base = 1LL * base * pw[c - '0'] % m;
            pwof2 = qpow(pwof2, 10, mod);
            pwof2 = 1LL * pwof2 * pw[c - '0'] % mod;
        }
        base = (base - 1 + m) % m;
        int on = DLOG(base, x, m);
        if(on == -1) cout << -1 << nl;
        else{
            int ans = (qpow(2, on, mod) - 1 + mod) % mod;
            int tmp = 1LL * pwof2 * invof2 % mod;
            ans = 1LL * ans * tmp % mod;
            cout << ans << nl;
        }
    }
    return 0;
}
