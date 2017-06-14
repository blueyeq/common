int mod = (int)1e9 + 7;

int64_t extGcd(int64_t a, int64_t b, int64_t& x, int64_t& y) { 
  if (!a) {
    x = 0;
    y = 1;
    return b;
  }
  int64_t x1, y1;
  int64_t d = extGcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

inline int addMod(int a, int b, int m = mod) {
  return ((int64_t)a + b) % m;
}

inline int mulMod(int a, int b, int m = mod) {
  return ((int64_t)a * b) % m;
}

inline int divMod(int a, int b, int m = mod) {
  int64_t x, y;
  int64_t g = extGcd(b, m, x, y);
  if (g != 1) {
    cerr << "Bad gcd!" << endl;
    for (;;);
  }
  x = (x % m + m) % m;
  return mulMod(a, x, m);
}

inline int C(int k, int n) {
  return divMod(F(n), mulMod(F(n-k), F(k)));
}


/* sw=2;ts=2;sts=2;expandtab */
