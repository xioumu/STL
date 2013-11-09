const int zx[] = {0, 1, 0, -1}; 
const int zy[] = {1, 0, -1, 0}; 

int sgn(double x) { return (x > eps) - (x < -eps); } 
void get_min(double& x, double y) { x = min(x, y); }
void get_max(double& x, double y) { x = max(x, y); }
struct P {
    double x, y;
    P() {}
    P(double _x, double _y): x(_x), y(_y) {}
    P operator + (const P &a) const { return P(x + a.x, y + a.y); }
    P operator - (const P &a) const { return P(x - a.x, y - a.y); }
    P operator * (const double &m) const { return P(x * m, y * m); }
    P operator / (const double &m) const { return P(x / m, y / m); }
    P set(const double &m) const {
        double len = length();
        return P(x * m / len, y * m / len);
    }
    P turn(const double &m) const {
        double c = cos(m), s = sin(m);
        return P(x * c - y * s, x * s + y * c);
    }
    bool operator == (const P &p) const { return sgn(x - p.x) == 0 && sgn(y - p.y) == 0;
    }
    double length() const {
        return sqrt(x * x + y * y);
    }
    double dist(const P &a) const {
        return sqrt(SQR(x - a.x) + SQR(y - a.y));
    }
    double cross(const P &a, const P &b) const { return (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x); }
    double cross(const P &a) const { return x * a.y - y * a.x; }
    double dot(const P &a, const P &b) { return (a.x - x) * (b.x - x) + (a.y - y) * (b.y - y); }
    void input() { scanf("%lf%lf", &x, &y); }
    void output() const { printf("(%lf, %lf)\n", x, y); }
    P trunc(double l) const {
        double r = l / length();
        return P(x * r, y * r);
    }
    P turn_left() const { return P(-y, x); }
    P rotate_left(double ang) const {
        double c = cos(ang), s = sin(ang);
        return P(x * c - y * s, y * c + x * s);
    }
    P turn_right() const { return P(y, -x); }
    P rotate_right(double ang) const {
        double c = cos(ang), s = sin(ang);
        return P(x * c + y * s, y * c - x * s);
    }
};

double dist2(const P &a, const P &b) { 
    return SQR(a.x - b.x) + SQR(a.y - b.y); 
} 
double dist(const P &a, const P &b) { 
    return sqrt(SQR(a.x - b.x) + SQR(a.y - b.y)); 
} 
double cross(const P &a, const P &b, const P &c) { 
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); 
} 
double dmul(const P &a, const P &b, const P &c) { 
    return (b.x - a.x) * (c.x - a.x) + (b.y - a.y) * (c.y - a.y); 
} 

int NEXT(int x, int n) {
    return x % n;
}

struct C { 
    P mid; 
    double r; 
    C(const P &_mid, const double &_r) 
        :mid(_mid), r(_r) {} 
    C() {} 
    bool operator == (const C &a) const { 
        return mid == a.mid && sgn(r - a.r) == 0; 
    } 
    bool in(const C &a) const { 
        return sgn(r + dist(mid, a.mid) - a.r) <= 0; 
    } 
    const C &input() { 
        mid.input(); 
        scanf("%lf", &r); 
        return *this;
    } 
    const C &output() const { 
        printf("P: %.12lf %.12lf R: %.12lf\n", mid.x, mid.y, r); 
    } 
}; 
double cal_angle(const C &c, const P &a, const P &b) { 
    double k = dmul(c.mid, a, b) / SQR(c.r); 
    get_min(k, 1.0); 
    get_max(k, -1.0); 
    return acos(k); 
} 
double cal_area(const C &c, const P &a, const P &b) { 
    return SQR(c.r) * cal_angle(c, a, b) / 2 - cross(c.mid, a, b) / 2; 
} 
struct cmp { 
    P mid; 
    cmp(const P &_mid) 
        :mid(_mid) {} 
    bool operator () (const P &a, const P &b) { 
        return atan2(a.y - mid.y, a.x - mid.x) < atan2(b.y - mid.y, b.x - mid.x); 
    } 
}; 
bool circles_intersection(const C &a, const C &b, P &c1, P &c2) { 
    double dd = dist(a.mid, b.mid); 
    if (sgn(dd - (a.r + b.r)) >= 0) { 
        return false; 
    } 
    double l = (dd + (SQR(a.r) - SQR(b.r)) / dd) / 2; 
    double h = sqrt(SQR(a.r) - SQR(l)); 
     c1  =  a.mid  +  (b.mid  -  a.mid).trunc(l)  +  (b.mid  - a.mid).turn_left().trunc(h); 
     c2  =  a.mid  +  (b.mid  -  a.mid).trunc(l)  +  (b.mid  - a.mid).turn_right().trunc(h); 
    return true; 
} 
bool cover(const C &c, const P &a, const P &b, const vector<C> &cir) { 
    P p = c.mid + ((a + b) / 2 - c.mid).trunc(c.r); 
    for (vector<C>::const_iterator it = cir.begin(); it != cir.end(); ++it) { 
        if (sgn(dist2(p, it->mid) - SQR(it->r)) < 0) { 
            return true; 
        } 
    } 
    return false; 
} 
double cal_area(const vector<C> &in) { 
    vector<C> cir; 
    for (int i = 0; i < SZ(in); ++i) { 
        if (sgn(in[i].r) == 0) { 
            continue; 
        } 
        bool flag = false; 
        for (int j = i + 1; j < SZ(in); ++j) { 
            if (in[i] == in[j]) { 
                flag = true; 
                break; 
            } 
        } 
        if (flag) { 
            continue; 
        } 
        for (int j = 0; j < SZ(in); ++j) { 
            if (!(in[i] == in[j]) && in[i].in(in[j])) { 
                flag = true; 
                break; 
            } 
        } 
        if (flag) { 
            continue; 
        } 
        cir.push_back(in[i]); 
    } 
    vector<vector<P> > point_on_circle(SZ(cir)); 
    for (int i = 0; i < SZ(cir); ++i) { 
        for (int z = 0; z < 4; ++z) { 
             point_on_circle[i].push_back(cir[i].mid  +  P(zx[z], zy[z]).trunc(cir[i].r)); 
        } 
    } 
    for (int i = 0; i < SZ(cir); ++i) { 
        for (int j = i + 1; j < SZ(cir); ++j) { 
            P a, b; 
            if (circles_intersection(cir[i], cir[j], a, b)) { 
                point_on_circle[i].push_back(a); 
                point_on_circle[i].push_back(b); 
                point_on_circle[j].push_back(a); 
                point_on_circle[j].push_back(b); 
            } 
        } 
    } 
    for (int i = 0; i < SZ(cir); ++i) { 
         sort(point_on_circle[i].begin(),  point_on_circle[i].end(), cmp(cir[i].mid)); 
         point_on_circle[i].erase(unique(point_on_circle[i].begin(), point_on_circle[i].end()), point_on_circle[i].end()); 
    } 
    double ans = 0; 
    for (int i = 0; i < SZ(cir); ++i) { 
        for (int j = 0; j < SZ(point_on_circle[i]); ++j) { 
            const P &a = point_on_circle[i][j]; 
             const P  &b  =  point_on_circle[i][NEXT(j  +  1, SZ(point_on_circle[i]))]; 
            if (!cover(cir[i], a, b, cir)) { 
                ans += cross(P(0, 0), a, b) / 2; 
                ans += cal_area(cir[i], a, b); 
            } 
        } 
    } 
    return ans; 
} 

