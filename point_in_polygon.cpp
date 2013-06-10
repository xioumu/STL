//判断点在多边形内，多边形上的点也作为多边形内
int find(const P &t) {
    return t.x >= 0 ? (t.y >= 0 ? 0 : 3) : (t.y >= 0 ? 1 : 2);
}

// 0 表示点在多边形外，1 表示点在多边形上, 2 表示点在多边形内
int points_in_polygon(const P &p, const vector<P> &pl) {
    int n = pl.size(), sum = 0;
    int t1 = find(pl.back() - p);
    for (int i = 0; i < n; ++i) {
        double f = p.cross(pl[(i + n - 1) % n], pl[i]);
        if (sgn(f) == 0 && sgn(p.dot(pl[(i + n - 1) % n], pl[i])) <= 0) return 1;
        int t2 = find(pl[i] - p);
        if (t2 == (t1 + 1) % 4) ++sum;
        else if (t2 == (t1 + 3) % 4) --sum;
        else if (t2 == (t1 + 2) % 4) {
            if (f > 0) sum += 2;
            else sum -= 2;
        }
        t1 = t2;
    }
    if (sum) return 2;
    return 0;
}
