#include <cstdio>

const int mod = 1000000007;
int n, k, l, r;
int f[110000];

int read()
{
    int x = 0, k = 1; char c = getchar();
    while(c < '0' || c > '9')
    { c == '-' ? k = -1 : k; c = getchar(); }
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * k;
}

int q_pow(int x, int k)
{
    if(!k) return 1;
    int p = q_pow(x, k/2);
    return ((k&1) ? (long long)p*p*x % mod : (long long)p*p % mod);
}

int main()
{
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    n = read(); k = read();
    l = read(); r = read();
    for(int i = 100000; i; --i)
    {
        int L = (l+1ll*k*i-1) / (1ll*k*i), R = r / (1ll*k*i);
        if(l/k <= r/k)
        {
            f[i] = (q_pow(R-L+1, n) - (R-L+1) + mod) % mod;
            for(int j = 2*i; j <= 100000; j+=i) f[i] = (f[i] - f[j] + mod) % mod;
        }
    }
    if(l <= k && k <= r) ++f[1];
    printf("%d\n", f[1]);
    return 0;
}
