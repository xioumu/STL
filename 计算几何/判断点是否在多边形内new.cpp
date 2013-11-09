bool onSegment(const point &p, const point &s, const point &e) {
    if (p == s || p == e) return true;
    if (sgn((p - s) * (e - s)) == 0 && sgn((s - p) ^ (e - p)) <= 0)
        return true;
    return false;
}
int get_position(const point &p, point *pol, int n) {
    int wn = 0;
    for (int i = 0; i < n; i++) {
        if (onSegment(p, pol[i], pol[(i + 1) % n])) return 0; //on the segment
        int k = sgn((pol[(i + 1) % n] - pol[i]) * (p - pol[i]));
        int d1 = sgn(pol[i].y - p.y);
        int d2 = sgn(pol[(i + 1) % n].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1; //inner
    else return -1; //outter
}