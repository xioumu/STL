void gcd(lint a, lint b, lint &d, lint &x, lint &y) {
    if (!b) {d = a; x = 1; y = 0;}
    else { gcd(b, a % b, d, y, x); y -= x * (a / b);}
}

lint inv(lint a, lint n) {
    lint d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}

lint mulMod(lint a, lint b, lint m = mod) { // a * b % m;
    return a * b % m;
}

lint powMod(lint a, lint b, lint m = mod) { // a ^ b % m;
    lint res = 1;
    while (b != 0) {
        if (b & 1) {
            res = (res * a) % m;
        } 
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}


lint logMod(lint a, lint b, lint n = mod) { //a ^ x = b (mod n)
    lint m, v, e = 1, i;
    m = (int)sqrt(n + 0.5);
    v = inv(powMod(a, m, n), n);
    map <lint, lint > x;
    x.clear();
    x[1] = 0;
    for (lint i = 1; i < m; i++) {
        e = mulMod(e, a, n);
        if (!x.count(e)) x[e] = i;
    }
    for (lint i = 0; i < m; i++) {
        if (x.count(b)) return i * m + x[b];
        b = mulMod(b, v, n);
    }
    return -1;
}
