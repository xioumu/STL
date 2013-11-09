double trim(double d, double l = 1.0) {
    return d > l ? l : (d < -l ? -l : d);
}
int get_position(const point& p, const point* pol, int n) {
    double ang = 0;
    for (int i = 0; i < n; ++i) {
        if (pol[i] == p) return 0; //ÔÚµãÉÏ
        point p1 = pol[i] - p, p2 = pol[(i + 1) % n] - p;
        double c = (p1 ^ p2) / (p1.len() * p2.len());
        c = trim(c);
        ang += sgn(p1 * p2) * acos(c);
    }
    ang = abs(ang);
    return ang < 0.5 * pi ? -1 : (ang < 1.5 * pi ? 0 : 1);
}
