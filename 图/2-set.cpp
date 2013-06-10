int n, m;
vector<int> e[maxn], g[maxn], op[maxn];
void add(vector<int> *e, int x, int y){
    e[x].push_back(y);
}
void get(int &x, int &nx){
    if(x < 0){
        x = -x;
        nx = x + n;
    }
    else {
        nx = x;
        x += n;
    }
}
int sta[maxn], low[maxn], dfn[maxn], v[maxn], fen[maxn], du[maxn], co[maxn];
int top, num, fn;
void tar(vector<int> *e, int w){
    sta[++top] = w;
    low[w] = dfn[w] = ++num;
    v[w] = 1;
    rep (i, sz(e[w]) ) {
        int j = e[w][i];
        if(v[j] == 2) continue;
        if( dfn[j] == -1) tar(e, j);
        low[w] = min(low[w], low[j]);
    }

    if(dfn[w] == low[w]){
        fn++;
        do{
            fen[ sta[top] ] = fn;
            v[ sta[top] ] = 2;
            top--;
        }while( sta[top + 1] != w);
    }
}
bool shrink(vector <int> *e, vector <int> *g){ //1 -- 2 * n 缩点 把边反向 如果ai, aj在一个强连通 return false;
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(v, 0, sizeof(v));
    num = top = fn = 0;
    repf (i, 1, 2 * n)
        if(dfn[i] == -1){
            tar(e, i);
        }
    repf (i, 1, fn) {
        g[i].clear();
        op[i].clear();
    }
    memset(du, 0, sizeof(du));
    repf (i, 1, 2 * n){
        int ni;
        if(i > n) ni = i - n;
        else ni = i + n;
        if(fen[i] == fen[ni]) return false;
        add(op, fen[i], fen[ni]);
        rep (j, sz(e[i])){
            int k = e[i][j];
            if( fen[i] != fen[k] ){
                add(g, fen[k], fen[i]);
                du[ fen[i] ]++;
            }
        }
    }
    return true;
}
void updata(vector<int> *e, int w){
    if(co[w] != 0){
        return ;
    }
    co[w] = 2;
    rep (i, sz(e[w]) ){
        int j = e[w][i];
        du[j]--;
        updata(e, j);
    }
}
void dye(vector<int> *e){
    top = 0;
    repf (i, 1, fn)
        if( du[i] == 0)
            sta[++top] = i;
    memset(co, 0, sizeof(co));
    while(top != 0){
        int k = sta[top--];
        if( co[k] != 0) continue;
        else{
            co[k] = 1;
            rep (i, sz(op[k])){
                updata(e, op[k][i]);
            }
        }
        rep (i, sz(e[k])){
            int j = e[k][i];
            du[j]--;
            if(du[j] == 0) 
                sta[++top] = j;
        }
    }
}
int main(){
    if( !shrink(e, g) ){
        printf("No\n");
    }
    else {
        printf("Yes\n");
        dye(g);
        vector<int> ans;
        repf (i, n + 1, 2 * n)
            if(co[ fen[i] ] == 1){
                ans.push_back(i - n);
            }
        printf("%d", sz(ans));
        rep (i, sz(ans)){
            printf(" %d", ans[i]);
        }
        printf("\n");
    }

    return 0;
}
