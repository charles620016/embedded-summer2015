int findGCD_v1(int a, int b) {
    while (1) {
        if (a > b) a -= b;
        else if (a < b) b -= a;
        else return a;
    }
}

int findGCD_v2(int a, int b) {
    while (1) {
        a %= b;
        if (a == 0) return b;
        if (a == 1) return 1;
        b %= a;
        if (b == 0) return a;
        if (b == 1) return 1;
    }
}

int findGCD_v3(int a, int b) {
    while (1) {
        if (a > (b * 4)) {
            a %= b;
            if (a == 0) return b;
            if (a == 1) return 1;
        } else if (a >= b) {
            a -= b;
            if (a == 0) return b;
            if (a == 1) return 1;
        }
        if (b > (a * 4)) {
            b %= a;
            if (b == 0) return a;
            if (b == 1) return 1;
        } else if (b >= a) {
            b -= a;
            if (b == 0) return a;
            if (b == 1) return 1;
        }
    }
}