const int maxint = -1u>>1;
const double esp = 1e-8;
const int maxn = 9 + 10;
class Graph {
    public:
        static const int maxn = 1000 + 7;
        static const int maxm = 1000 + 7;
        static const int Max = maxn * maxm + 10;
        int adj[maxn][maxm];
        int ans;
        void init() {
            n = m = 0;
            memset(adj, 0, sizeof(adj));
        }
        void insert(int u, int v) {
            n = max(n, u);
            m = max(m, v);
            adj[u][v] = 1;
        }
        int find_ans() {
            build_dlx();
            ans = -1;
            if (dfs(0) ) {
                return ans;
            }
            return -1;
        }
        void work(int n) {
            if(n == -1) {
                printf("NO\n");
                return ;
            }
            printf("%d", n);
            repf (i, 0, n - 1)
                printf(" %d", O[i]);
            printf("\n");
        }
    private:
        int head;
        int R[Max], L[Max], U[Max], D[Max], C[Max], H[Max];
        int S[maxn], O[maxn];
        int n, m, cnt, nm;

        void add(int head, int tmp, int x) {
            H[cnt] = head;
            R[cnt] = tmp; L[cnt] = L[tmp];
            L[tmp] = cnt; R[L[cnt]] = cnt;
            U[cnt] = U[x]; D[cnt] = x;
            D[U[x]] = cnt; U[x] = cnt;
            C[cnt] = x; ++S[x];
            ++cnt;
        }
        void build_dlx() {
            L[0] = R[0] = U[0] = D[0] = C[0] = H[0] = 0;
            for (int i = 1; i <= m; i++) {
                H[i] = 0;
                L[i] = i - 1; R[i] = 0;
                R[i - 1] = i; L[0] = i;
                U[i] = D[i] = C[i] = i;
                S[i] = 0;
            }
            cnt = m + 1;
            for (int i = 1; i <= n; i++) {
                int tmp = Max - 1;
                L[tmp] = R[tmp] = U[tmp] = D[tmp] = C[tmp] = tmp;
                for (int j = 1; j <= m; j++) 
                    if(adj[i][j])   {
                        add(i, tmp, j);
                    }
                L[R[tmp]] = L[tmp]; 
                R[L[tmp]] = R[tmp];
            }
        }
        void remove(const int &c) {
            R[L[c]] = R[c];
            L[R[c]] = L[c];
            for (int i = D[c]; i != c; i = D[i]) {
                for (int j = R[i]; j != i; j = R[j]) {
                    U[D[j]] = U[j];
                    D[U[j]] = D[j];
                    --S[C[j]];
                }
            }
        }

        void resume(const int &c) {
            for (int i = D[c]; i != c; i = D[i]) {
                for (int j = R[i]; j != i; j = R[j]) {
                    U[D[j]] = j;
                    D[U[j]] = j;
                    ++S[C[j]];
                }
            }
            R[L[c]] = c;
            L[R[c]] = c;
        }

        bool dfs(const int &k) {
            if (R[0] == 0){
                ans = k;
                return true;
            }
            int s(maxint), c;
            for (int i = R[0]; i != 0; i = R[i]) {
                if (S[i] < s) {
                    c = i;
                    s = S[i];
                }
            }
            remove(c);
            for (int i = D[c]; i != c; i = D[i]) {
                O[k] = H[i];
                for (int j = R[i]; j != i; j = R[j]) remove(C[j]);
                if (dfs(k + 1)) return true;
                for (int j = L[i]; j != i; j = L[j]) resume(C[j]);
            }
            resume(c);
            return false;
        }
}G;
int n, m;
int v[maxn][maxn];
int main(){
    while (scanf("%d%d", &n, &m) == 2) {
        G.init();
        rep (i, n) {
            int k, y;
            scanf("%d", &k);
            rep (j, k) {
                scanf("%d", &y);
                G.insert(i + 1, y);
            }
        }
        int ans = G.find_ans();
        G.work(ans);
    }
    return 0;
}

