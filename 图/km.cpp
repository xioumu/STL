struct Graph { 
    int w[maxn][maxn], lx[maxn], ly[maxn], matx[maxn], maty[maxn], slk[maxn], n; 
    bool fx[maxn], fy[maxn]; 
    void get_max(int &x, int y) {
        x = max(x, y);
    }
    void get_min(int &x, int y) {
        x = min(x, y);
    }
    void clear() { 
        memset(w, 0, sizeof(w)); 
        n = 0; 
    } 
    void insert(int u, int v, int c) { 
        get_max(n, max(u + 1, v + 1)); 
        w[u][v] = c; 
    } 
    int match() { 
        memset(ly, 0, sizeof(ly)); 
        for (int i = 0; i < n; ++i) { 
            lx[i] = -maxint; 
            for (int j = 0; j < n; ++j) { 
                get_max(lx[i], w[i][j]); 
            } 
        } 
        memset(matx, -1, sizeof(matx)); 
        memset(maty, -1, sizeof(maty)); 
        for (int i = 0; i < n; ++i) { 
            memset(fx, false, sizeof(fx)); 
            memset(fy, false, sizeof(fy)); 
            for (int j = 0; j < n; j++)
                slk[j] = maxint;
            if (!dfs(i)) { 
                --i; 
                int p = maxint; 
                for (int j = 0; j < n; j++)
                    if (fy[j] == false)
                        p = min(p, slk[j]);
                for (int j = 0; j < n; ++j) { 
                    ly[j] += fy[j] * p; 
                } 
                for (int k = 0; k < n; ++k) { 
                    lx[k] -= fx[k] * p; 
                } 
            } 
        } 
        int ans = 0; 
        for (int i = 0; i < n; ++i) { 
            ans += w[maty[i]][i]; 
        } 
        return ans; 
    } 
    bool dfs(int u) { 
        fx[u] = 1; 
        for (int v = 0; v < n; ++v) { 
            if (lx[u] + ly[v] > w[u][v]) {
                if (lx[u] + ly[v] - w[u][v] < slk[v])
                    slk[v] = lx[u] + ly[v] - w[u][v];
            }
            else if (lx[u] + ly[v] == w[u][v] && fy[v] == false) { 
                fy[v] = true; 
                if (maty[v] == -1 || dfs(maty[v])) { 
                    matx[u] = v; 
                    maty[v] = u; 
                    return true; 
                } 
            } 
        } 
        return false; 
    } 
}G; 

