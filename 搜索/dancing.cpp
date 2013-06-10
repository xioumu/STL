/*
 * Author:  xioumu
 * Created Time:  2012/9/22 0:22:59
 * File Name: dancing.cpp
 * solve: dancing.cpp
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
typedef long long lint;
const int maxint = -1u>>1;
const double esp = 1e-8;
class Graph {
    public:
        static const int maxn = 2600 / 2;
        static const int maxm = 51;
        static const int mmax = maxn * maxm + maxn + maxm + 100;
        int n, m;
        int adj[maxn][maxm];
        void init() {
            n = m = 0;
            memset(adj, 0, sizeof(adj));
        }
        void insert(int u, int v) {
            n = max(n, u + 1);
            m = max(m, v + 1);
            adj[u][v] = 1;
        }
        int find_ans() {
            build_dlx();
            for (int ans = 0; ans <= n; ans++) {
                if (dfs(0, ans) ) {
                    return ans;
                }
            }
            return -1;
        }
    private:
        int head;
        int U[mmax], D[mmax], L[mmax], R[mmax], 
            CN[mmax], RN[mmax];
        void addUD(const int &a, const int &h) {
            U[a] = h;
            D[a] = D[h];
            U[D[h]] = a;
            D[h] = a;
            CN[a] = h;
        }
        void addLR(const int &a, const int &h) {
            L[a] = h;
            R[a] = R[h];
            L[R[h]] = a;
            R[h] = a;
            RN[a] = h;
        }
        void add(const int &k, const int &r, const int &c) {
            addUD(k, c);
            addLR(k, r);
        }
        void remove(const int &k) {
            for (int j = R[k]; j != k; j = R[j]) {
                for (int i = D[j]; i != j; i = D[i]) {
                    L[R[i]] = L[i];
                    R[L[i]] = R[i];
                }
                D[U[j]] = D[j];
                U[D[j]] = U[j];
            }
        }
        void unremove(const int &k) {
            for (int j = L[k]; j != k; j = L[j]) {
                D[U[j]] = j;
                U[D[j]] = j;
                for (int i = U[j]; i != j; i = U[i]) {
                    L[R[i]] = i;
                    R[L[i]] = i;
                }
            }
        }
        void build_dlx() {
            head = mmax - 1;
            U[head] = D[head] = L[head] = R[head] = head;
            int cnt = 0;
            for (int i = 0; i < m; i++) {
                U[cnt] = D[cnt] = cnt;
                addLR(cnt++, head);
            }
            for (int i = 0; i < n; i++) {
                L[cnt] = R[cnt] = cnt;
                addUD(cnt++, head);
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (adj[i][j]) {
                        addLR(cnt, m + i);
                        addUD(cnt, j);
                        cnt++;
                    }
                }
            }
        }
        int h() {
            int hash[maxm] = {};
            int ans = 0;
            for (int c = R[head]; c != head; c = R[c]) {
                if(hash[c] == 0) {
                    hash[c] = 1;
                    ans++;
                    for (int j = D[c]; j != c; j = D[j]) {
                        for (int i = R[j]; i != j; i = R[i]) {
                            if(CN[i] != head) {
                                hash[CN[i]] = 1;
                            }
                        }
                    }
                }
            }
            return ans;
        }
        bool dfs(int k, int lim) {
            if (k + h() > lim) {
                return false;
            }
            if( R[head] == head) {
                return true;
            }
            int c;
            c = R[head];
            L[R[c]] = L[c];
            R[L[c]] = R[c];
            for (int i = D[c]; i != c; i = D[i]) {
                L[R[i]] = L[i];
                R[L[i]] = R[i];
            }
            for (int i = D[c]; i != c; i = D[i]) {
                remove(RN[i]);
                if (dfs(k + 1, lim) ) {
                    return true;
                }
                unremove(RN[i]);
            }
            for (int i = U[c]; i != c; i = U[i]) {
                L[R[i]] = i;
                R[L[i]] = i;
            }
            L[R[c]] = c;
            R[L[c]] = c;
            return false;
        }
}G;
int main(){
}
