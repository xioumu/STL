const int maxn = 9 + 10;
int n = 9, m = 9, tn = 9;
class Graph {
    public:
        static const int maxn = 9 * 9 * 9 + 7;
        static const int maxm = 1000 + 7;
        static const int Max = maxn * maxm + 10;
        static const int sn = 9, sm = 9, stn = 9;
        int adj[maxn][maxm], O[maxn]; //O[] is answer
        int ans, sudoku[20][20];
        
        void init() {
            n = m = 0;
            memset(adj, 0, sizeof(adj));
        }
        void insert(int u, int v) {
            u++, v++;
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
        void out_ans(int ans) {
            if(ans == -1) {
                printf("NO\n");
                return ;
            }
            //printf("%d", n);
            repf (i, 0, ans - 1) {
                int x, y, ty;
                O[i]--;
                x = O[i] / (sm * stn);
                y = (O[i] % (sm * stn) ) / stn;
                ty = (O[i] % (stn));
                //printf("%d %d %d\n", x, y, ty);
                sudoku[x][y] = ty + 1;
            }
            rep (i, sn)
                rep (j, sm)
                    printf("%d",sudoku[i][j]);  
            printf("\n");
        }
    private:
        int head;
        int R[Max], L[Max], U[Max], D[Max], C[Max], H[Max];
        int S[maxn];
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
                O[k] = H[i]; //
                for (int j = R[i]; j != i; j = R[j]) remove(C[j]);
                if (dfs(k + 1)) return true;
                for (int j = L[i]; j != i; j = L[j]) resume(C[j]);
            }
            resume(c);
            return false;
        }
}G;
char in[maxn * maxn];
int a[maxn][maxn];

void add(int x, int y, int ty) {
    int l_id = x * m * tn + y * tn + ty;
    //printf("%d %d %d %d\n", x, y, ty, l_id);
    int bn =  ((x / 3) * 3 + y / 3);
    G.insert(l_id, x * m + y);
    G.insert(l_id, x * tn + ty + n * m);         //row
    G.insert(l_id, n * tn + y * tn + ty + n * m);   //vertical
    G.insert(l_id, n * tn + m * tn + bn * tn + ty + n * m);  //block
}
int main(){
    while (scanf("%s", in) == 1) {
        if (in[0] == 'e')    break;
        rep (i, n)
            rep (j, m)
                if (in[i * m + j] == '.')   a[i][j] = 0;
                else  a[i][j] = in[i * m + j] - '0';
        
        G.init();
        rep (i, n) 
            rep (j, m) {
                if(a[i][j] == 0) {
                    repf (k, 1, 9)
                        add(i, j, k - 1);
                }
                else add(i, j, a[i][j] - 1);
            }
        int ans = G.find_ans();
        G.out_ans(ans);
    }
    return 0;
}

