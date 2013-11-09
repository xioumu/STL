class Trie { 
public: 
    const static int st = 'A', en = 'z'; 
    const static int m = en - st + 1; 
    const static int maxn = 10002; 
    int d[maxn][m];     //graph 
    int t[maxn];        //state 
    int p[maxn];        //suffix 
    int n, len; 
    void init() { 
        len = 1; 
        n = 0; 
        t[0] = 0; 
        memset(d[0], -1, sizeof(d[0])); 
    } 
    void insert(char *s, int id) { 
        int i; 
        for(i = 0; *s; ++s) { 
            int &k = d[i][*s - st]; 
            if(k == -1) { 
                k = len++; 
                memset(d[k], -1, sizeof(d[k])); 
                t[k] = 0; 
            } 
            i = k; 
        } 
        t[i] |= 1<<id; 
    } 
    void bfs() { 
        int i; 
        queue<int> q; 
        q.push(0); 
        p[0] = 0; 
        while(!q.empty()) { 
            int k = q.front(); 
            q.pop(); 
            for(i = 0; i < m; i++) { 
                int &j = d[k][i]; 
                if(-1 == j) { 
                    j = d[p[k]][i]; 
                    if(j == -1)j=0; 
                } 
                else { 
                    if (k) p[j] = d[p[k]][i]; 
                    else  p[j] = 0; 
                    t[j] |= t[p[j]]; 
                    q.push(j); 
                } 
            } 
        } 
    } 
}; 

