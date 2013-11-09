struct line {
    point p, v;
    double ang;
    line() {}
    line(point p, point v) : p(p), v(v) { ang = atan2(v.y, v.x); }
    bool operator < (const line &l) const { return ang < l.ang; }
};

//点p在有向直线l的左边（线上不算）
bool onLeft(line l, point p) { 
    return sgn(l.v * (p - l.p)) > 0;
}

 //二直线交点，假设交点唯一存在
point getIntersection(line a, line b) {
    point u = a.p - b.p; 
    double t = (b.v * u) / (a.v * b.v);
    return a.p + a.v * t;
} 

point p[maxn];
line q[maxn];
int halfPlane(vector<line> l, vector<point> &poly) { //l:anti-clockwise
    int n = sz(l);
    sort(l.begin(), l.end());
    int first, last;
    q[first = last = 0] = l[0];
    for (int i = 1; i < n; i++) {
        while (first < last && !onLeft(l[i], p[last - 1])) last--;
        while (first < last && !onLeft(l[i], p[first])) first++;
        q[++last] = l[i];
        if (sgn(q[last].v * q[last - 1].v) == 0) {
            last--;
            if (onLeft(q[last], l[i].p)) q[last] = l[i];
        }
        if (first < last) p[last - 1] = getIntersection(q[last - 1], q[last]);
    } 
    while (first < last && !onLeft(q[first], p[last - 1])) last--;
    
    poly.clear();
    if (last - first <= 1) return 0;
    p[last] = getIntersection(q[last], q[first]);
    int m = 0; 
    for (int i = first; i <= last; i++) {
        poly.push_back(p[i]);
        m++;
    }
    return m;
}
