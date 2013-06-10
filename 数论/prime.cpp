int prime[664588], cnt = 0;
void makePrime() { // maxn=10^7 consume 400MS
    for (int i = 2; i < maxn; ++i) {
        if (!f[i]) {
            prime[cnt++] = i;
        }
        for (int j = 0; (int64)i * prime[j] < maxn; ++j) {
            f[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
