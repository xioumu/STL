void gcd(lint a, lint b, lint& d, lint& x, lint& y)  {
    if (!b) { d = a; x = 1; y = 0; }
    else {gcd(b, a % b, d, y, x); y -= x * (a / b); }
}

lint inv(lint a, lint n) {
    lint d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}
