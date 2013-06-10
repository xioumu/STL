/*
 * Author:  xioumu
 * Created Time:  2013/3/29 18:08:27
 * File Name: maxflow.cpp
 * solve: maxflow.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;
#define sz(v) ((int)(v).size())
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(x) memset(x,0,sizeof(x))
#define clrs( x , y ) memset(x,y,sizeof(x))
#define out(x) printf(#x" %d\n", x)
#define sqr(x) ((x) * (x))
typedef long long lint;

const int maxint = -1u>>1;
const double eps = 1e-8;
const int maxn = 100000;

int sgn(const double &x) {  return (x > eps) - (x < -eps); }
struct Graph1 {
    struct Adj {
        int v, c, b;
        Adj(int _v, int _c, int _b) :
            v(_v), c(_c), b(_b) {}
        Adj(){}
    };
    int n, S, T, h[maxn], cnt[maxn];
    vector<Adj> adj[maxn];
    void clear() {
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        n = 0;
    }
    void insert(int u, int v, int c, int d = 0) {
        n = max(n, max(u, v) + 1);
        adj[u].push_back(Adj(v, c, adj[v].size()));
        adj[v].push_back(Adj(u, c * d, adj[u].size() - 1));
    }
    int maxflow(int _S, int _T) {
        S = _S, T = _T;
        fill(h, h + n, 0);
        fill(cnt, cnt + n, 0);
        int flow = 0;
        while (h[S] < n) {
            flow += dfs(S, maxint);
        }
        return flow;
    }
    int dfs(int u, int flow) {
        if (u == T) {
            return flow;
        }
        int minh = n - 1, ct = 0;
        for (vector<Adj>::iterator it = adj[u].begin(); flow && it != adj[u].end(); ++it) {
            if (it->c) {
                if (h[it->v] + 1 == h[u]) {
                    int k = dfs(it->v, min(it->c, flow));
                    if (k) {
                        it->c -= k;
                        adj[it->v][it->b].c += k;
                        flow -= k;
                        ct += k;
                    }
                    if (h[S] >= n) {
                        return ct;
                    }
                }
                minh = min(minh, h[it->v]);
            }
        }
        if (ct) {
            return ct;
        }
        if (--cnt[h[u]] == 0) {
            h[S] = n;
        }
        h[u] = minh + 1;
        ++cnt[h[u]];
        return 0;
    }
};


int main() {
}
