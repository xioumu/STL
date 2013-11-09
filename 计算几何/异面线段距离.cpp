//返回直线距离的平方,返回一个分数。 node是分数类
node gao3(point p, point a, point b) { //点到线段的距离
    if (p == a || p == b) return node(0);
    if (a == b) return node((p - a) ^ (p - a));
    point v1 = b - a, v2 = p - a, v3 = p - b;
    if ((v1 ^ v2) < 0) {
        return node(v2 ^ v2);
    }
    else if ((v1 ^ v3) > 0) {
        return node(v3 ^ v3);
    }
    else {
        return node((v1 * v2) ^ (v1 * v2)) / node(v1 ^ v1);
    }
}
node gao2(point a, point b, point c, point d) { //当线段之间没有垂线的距离
    node res = gao3(c, a, b);
    res = min(res, gao3(d, a, b)); 
    res = min(res, gao3(a, c, d));
    res = min(res, gao3(b, c, d));
    return res;
}

bool ok(node x) {
    if (x.zi * x.mu < 0) return false;
    if (x.zi < 0) 
        x.zi *= -1, x.mu *= -1;
    return x.zi <= x.mu;
}

node gao(point a, point b, point l, point r) { //线段与线段之间的距离
    lint x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3;
    x0 = a.x, y0 = a.y, z0 = a.z;
    x1 = b.x, y1 = b.y, z1 = b.z;
    x2 = l.x, y2 = l.y, z2 = l.z;
    x3 = r.x, y3 = r.y, z3 = r.z; 
    lint a1 = x1 - x0, a2 = x2 - x3, a3 = x0 - x2,
         a4 = y1 - y0, a5 = y2 - y3, a6 = y0 - y2,
         a7 = z1 - z0, a8 = z2 - z3, a9 = z0 - z2;
    lint  A = a1 * a1 + a4 * a4 + a7 * a7,
         B = a2 * a2 + a5 * a5 + a8 * a8,
         C = 2 * (a1 * a2 + a4 * a5 + a7 * a8),
         D = 2 * (a1 * a3 + a4 * a6 + a7 * a9),
         E = 2 * (a2 * a3 + a5 * a6 + a8 * a9),
         F = a3 * a3 + a6 * a6 + a9 * a9; 
    if ((a1 * a5 == a2 * a4 && a1 * a8 == a2 * a7 && a4 * a8 == a5 * a7)) 
        return gao2(a, b, l, r);
    
    lint Y = C * D - 2 * A * E, 
         X = C * E - 2 * B * D;
    if (!ok(node(Y, 4 * A * B - C * C)) || !ok(node(X, 4 * A * B - C * C)))
        return gao2(a, b, l, r);
    lint S = A * X * X + B * Y * Y + C * X * Y + D * X * (4 * A * B - C * C) + E * Y * (4 * A * B - C * C) + F * (4 * A * B - C * C) * (4 * A * B - C * C);
    return node(S, (4 * A * B - C * C) * (4 * A * B - C * C));
}

