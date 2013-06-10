lint v[maxn];
lint mob[maxP];
void getMobius() {
    memset(mob, 0, sizeof(mob));
    memset(v, 0, sizeof(v));
    mob[1] = 1;
    for (lint i = 2; i < maxn; i++) {
        if (v[i] == 0) {
            for (lint j = i + i; j < maxn; j += i) {
                v[j] = 1;
                mob[j] = mob[j / i] * -1;
            }
            mob[i] = -1;
        }
    }
}
