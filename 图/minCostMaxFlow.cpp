struct Graph {
    struct Adj {
        int v, c, w, b;
        Adj(int _v, int _c, int _w, int _b)
            :v(_v), c(_c), w(_w), b(_b) {}
    }*st[maxn];
    vector<Adj> adj[maxn];
    int n;
    int NEXT(int s, int n) {
        return s % n;
    }
    void clear() {
        for (int i = 0; i < n ; i++) {
            adj[i].clear();
        }
        n = 0;
    }
    void insert(int u, int v, int c, int w, int d = 0) {
        n = max(n, max(u, v) + 1);
        adj[u].push_back(Adj(v, c, w, adj[v].size()));
        adj[v].push_back(Adj(u, 0, -w, adj[u].size() - 1));
        if (d) {
            adj[v].push_back(Adj(u, c, w, adj[u].size()));
            adj[u].push_back(Adj(v, 0, -w, adj[v].size() - 1));
        }
    }
    pair<int, int> mcmf(int S, int T) {
        int d;
        int flow = 0, cost = 0;
        while ((d = bell(S, T))) {
            flow += d;
            for (int v = T; v != S; v = adj[st[v]->v][st[v]->b].v) {
                cost += st[v]->w * d;
                st[v]->c -= d;
                adj[st[v]->v][st[v]->b].c += d;
            }
        }
        return make_pair(flow, cost);
    }
    int bell(int S, int T) {
        int d[maxn], bfs[maxn], hash[maxn];
        fill(hash, hash + n, 0);
        fill(d, d + n, maxint);
        hash[S] = 1; 
        d[S] = 0;
        bfs[0] = S;
        for (int s = 0, t = 1; s != t; hash[bfs[s]] = 0, s = NEXT(s + 1, n)) {
            int v = bfs[s];
            for (vector<Adj>::iterator it = adj[v].begin(); it != adj[v].end(); it++) {
                if (it->c > 0 && d[v] + it->w < d[it->v]) {
                    d[it->v] = d[v] + it->w;
                    st[it->v] = &(*it);
                    if (hash[it->v] == 0) {
                        hash[it->v] = 1;
                        bfs[t] = it->v;
                        t = NEXT(t + 1, n);
                    }
                }
            }
        }
        if (d[T] == maxint) {
            return 0;
        }
        int ans = maxint;
        for (int v = T; v != S; v = adj[st[v]->v][st[v]->b].v) {
            ans = min(ans, st[v]->c);
        }
        return ans;
    }
}G;

