const double pi = acos(-1.0);

int sgn(double x) {
    return (x > eps) - (x < -eps);
}

struct point {
    double x, y;
    point (double _x = 0, double _y = 0) : x(_x), y(_y) { }
    void input() { scanf("%lf%lf", &x, &y); }
    void output() { printf("%.3f %.3f\n", x, y); }
    double len() const { return sqrt(x * x + y * y); }
    point trunc (double l) const {
        double r = l / len();
        return point(x * r, y * r);
    }
    point rotate_left() const { return point(-y, x); }
    point rotate_right() const { return point(y, -x); }
    point rotate_left(double s) const {
        double c = sqrt(1 - s * s);
        return point(x * c - y * s, y * c + x * s);
    }
    point rotate_right(double s) const {
        double c = sqrt(1 - s * s);
        return point(x * c + y * s, y * c - x * s);
    }
    point set() {
        double l = len();
        return point(x / l, y / l);
    }
    bool operator == (const point &p) const { return sgn(x - p.x) == 0 && sgn(y - p.y) == 0; }
    double operator * (const point &p) const { return (x * p.y) - (y * p.x); }
    double operator ^ (const point &p) const { return (x * p.x) + (y * p.y); }
    point operator + (const point &p) const { return point(x + p.x, y + p.y); }
    point operator - (const point &p) const { return point(x - p.x, y - p.y); }
    point operator / (double mul) const { return point(x / mul, y / mul); }
    point operator * (double mul) const { return point(x * mul, y * mul); }
};

double getDis(point s, point e, point p) { //点p与直线(s,e)的距离
    return ((e - s) * (p - s)) / (e - s).len();
}

point verticalPoint(point s, point e, point p) { //点p在直线(s,e)的垂点
    point rvl, rvr, s2l, s2r, e2;
    rvl = v.rotate_left();
    rvr = v.rotate_right();
    s2l = o + rvl.trunc(h);
    s2r = o + rvr.trunc(h);
    if (sgn(getDis(s, e, s2l)) == 0) 
        e2 = s2l;
    else e2 = s2r;
    return e2;
}
