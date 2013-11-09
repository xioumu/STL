/*
 * Author:  xioumu
 * Created Time:  2013/10/17 13:49:12
 * File Name: hdu3662.cpp
 * solve: hdu3662.cpp
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
const int maxn = 300 + 10;

int sgn(const double &x) {  return (x > eps) - (x < -eps); }
struct Point3{
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0):x(x), y(y), z(z) { }
    void input() { scanf("%lf%lf%lf", &x, &y, &z); }
    void output() { printf("%f %f %f\n", x, y, z); }
    bool operator < (Point3 p) const {
        if (sgn(x - p.x) != 0) return x < p.x;
        else if (sgn(y - p.y) != 0) return y < p.y;
        else return z < p.z;
    }
    bool operator == (Point3 p) const {
        return sgn(x - p.x) == 0 && sgn(y - p.y) == 0 && sgn(z - p.z) == 0;
    }
};
typedef Point3 Vector3;

Point3 operator + (Vector3 A, Vector3 B) {
    return Vector3(A.x + B.x, A.y + B.y, A.z + B.z);
}
Point3 operator - (Point3 A, Point3 B) {
    return Vector3(A.x - B.x, A.y - B.y, A.z - B.z);
}
double Dot(Vector3 A, Vector3 B) {return A.x * B.x + A.y * B.y + A.z * B.z;}
double Length(Vector3 A) { return sqrt(Dot(A, A)); }
double Angle(Vector3 A, Vector3 B) {return acos(Dot(A, B) / Length(A) / Length(B));}
Vector3 Cross(Vector3 A, Vector3 B) {
    return Vector3(A.y * B.z - A.z * B.y, A.z * B.x - A.x * B.z, A.x * B.y - A.y * B.x);
}

struct Face {
    int v[3];
    Vector3 normal(Point3 *P) const {
        return Cross(P[v[1]] - P[v[0]], P[v[2]] - P[v[0]]);
    }
    int cansee(Point3 *P, int i) const {
        return Dot(P[i] - P[v[0]], normal(P)) > 0 ? 1 : 0;
    }
};

int vis[maxn][maxn];

vector<Face> CH3D(Point3 *P, int n) {
    vector<Face> cur;
    cur.push_back((Face){{0, 1, 2}});
    cur.push_back((Face){{2, 1, 0}});
    for (int i = 3; i < n; i++) {
        vector<Face> next;
        for (int j = 0; j < cur.size(); j++) {
            Face &f = cur[j];
            int res = f.cansee(P, i);
            if (!res) next.push_back(f);
            for (int k = 0; k < 3; k++)
                vis[f.v[k]][f.v[(k + 1) % 3]] = res;
        }
        for (int j = 0; j < cur.size(); j++) 
            for (int k = 0; k < 3; k++) {
                int a = cur[j].v[k], b = cur[j].v[(k + 1) % 3];
                if (vis[a][b] != vis[b][a] && vis[a][b])
                    next.push_back((Face){{a, b, i}});
            }
        cur = next;
    }
    return cur;
}

double rand01() { return rand() / (double)RAND_MAX;}
double randeps() {return (rand01() - 0.5) * 1e-5;}
Point3 addNoise(Point3 p) {
    return Point3(p.x + randeps(), p.y + randeps(), p.z + randeps());
}

int n;
Point3 pp[maxn], p2[maxn], p0[maxn];
vector<Face> ff;
int can[1000000 + 10];

bool inFace(Point3 &p, Face &a) {
    Point3 vp[4];
    rep (i, 3) {
        vp[i] = p0[a.v[i]] - p;
    }
    return sgn(Dot(Cross(vp[0], vp[1]), vp[2])) == 0;
}

bool sameFace(Face &a, Face &b) {
    if (inFace(p0[a.v[0]], b) && inFace(p0[a.v[1]], b) && inFace(p0[a.v[2]], b)) return true;
    else return false;
}

int main() {
    while (scanf("%d", &n) == 1) {
        int m = 0; 
        rep (i, n) {
            pp[i].input();
        }
        sort(pp, pp + n);
        rep (i, n) {
            if (i == 0 || !(pp[i] == pp[i - 1]))
                p0[m++] = pp[i];
        }
        n = m;
        rep (i, n) p2[i] = addNoise(p0[i]);
        ff = CH3D(p2, n); 
        int ans = sz(ff);
        clr(can);
        rep (i, sz(ff)) {
            rep (j, i) if (!can[j]){
                if (sameFace(ff[i], ff[j])) {
                    can[i] = 1;
                    ans--;
                    break;
                }
            } 
        }
        printf("%d\n", ans); 
    }
    return 0;
}
