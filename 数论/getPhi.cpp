void getPhi() {
    clr(phi);
    phi[1] = 1;
    for (lint i = 2; i < maxn; i++) {
        if (phi[i] == 0) {
            for (lint j = i; j < maxn; j += i) {
                if (phi[j] == 0)
                    phi[j] = j;
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
}
