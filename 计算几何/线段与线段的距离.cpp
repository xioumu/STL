double get_dis(point a, point sb, point eb) {
    return min( (a - sb).len(), (a - eb).len());
}
double dis(point a, point b, point c) {
    double mul = ( (a - b) ^ (c - b) ) / (c - b).len();
    point dir = (c - b).set();
    point mid = dir * mul + b;
    if( sgn((mid - b) ^ (c - b) ) >= 0 && sgn((mid - c) ^ (b - c)) >= 0) {
        return fabs((a - b) * (c - b) / (c - b).len());
    }
    else return get_dis(a, b, c);
}
double dis(int a, int b) { //Ïß¶Îtp[a]sp[a], tp[b]sp[b]
    double res =  min( dis(tp[a], tp[b], sp[b]), dis(sp[a], tp[b], sp[b]));
    res = min(res, min(dis(tp[b], tp[a], sp[a]), dis(sp[b], tp[a], sp[a])));
    return res;
}

