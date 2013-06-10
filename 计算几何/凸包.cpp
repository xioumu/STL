bool operator < (const point &p) const{
    if(sgn(x - p.x) != 0) return x < p.x;
    else return y < p.y;
}
void convex(vector <point> a, vector <point> &tu){ //À≥ ±’Î
    point hu[maxn], hd[maxn];
    int n = a.size(), un, dn;
    sort(a.begin(), a.end());
    hu[0] = hd[0] = a[0];
    hu[1] = hd[1] = a[1];
    un = dn = 1;
    for(int i = 2; i < n; i++){
        for(; un > 0 && sgn( (hu[un] - hu[un - 1]) * (a[i] - hu[un] )) >= 0; un--);
        for(; dn > 0 && sgn( (hd[dn] - hd[dn - 1]) * (a[i] - hd[dn] )) <= 0; dn--);
        hu[++un] = a[i];
        hd[++dn] = a[i];
    }
    tu.clear();
    for(int i = 0; i <= un - 1; i++) tu.push_back(hu[i]);
    for(int i = dn; i >= 1; i--) tu.push_back(hd[i]);
}


