#include <cstdio>

const int Maxn = 1510;
int lu[Maxn][Maxn], ld[Maxn][Maxn],
    ru[Maxn][Maxn], rd[Maxn][Maxn],
    s[Maxn][Maxn], mp[Maxn][Maxn],
    a[Maxn][Maxn];
int n, m, k, ans = 0;

int max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    freopen("oil.in", "r", stdin);
    freopen("oil.out", "w", stdout);
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= m; ++j)
            s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
    for(int i = k; i <= n; ++i)
        for(int j = k; j <= m; ++j)
            mp[i][j] = s[i][j] - s[i-k][j] - s[i][j-k] + s[i-k][j-k];
    for(int i = k; i <= n; ++i)
        for(int j = k; j <= m; ++j)
            lu[i][j] = max(mp[i][j], max(lu[i-1][j], lu[i][j-1]));
    for(int i = k; i <= n; ++i)
        for(int j = m-k+1; j; --j)
            ru[i][j] = max(mp[i][j+k-1], max(ru[i-1][j], ru[i][j+1]));
    for(int i = n-k+1; i; --i)
        for(int j = k; j <= m; ++j)
            ld[i][j] = max(mp[i+k-1][j], max(ld[i+1][j], ld[i][j-1]));
    for(int i = n-k+1; i; --i)
        for(int j = m-k+1; j; --j)
            rd[i][j] = max(mp[i+k-1][j+k-1], max(rd[i+1][j], rd[i][j+1]));
    for(int j = k; j + 2*k <= m; ++j)
        for(int i = k; i <= n; ++i)
        {
            int d = lu[n][j] + ru[n][j+k+1] + mp[i][j+k];
            ans = max(ans, d);
        }
    for(int i = k; i + 2*k <= n; ++i)
        for(int j = k; j <= m; ++j)
        {
            int d = lu[i][m] + ld[i+k+1][m] + mp[i+k][j];
            ans = max(ans, d);
        }
    for(int i = k; i + k <= n; ++i)
        for(int j = k; j+k <= m; ++j)
        {
            int d = lu[i][j] + ld[i+1][j] + rd[1][j+1];
            ans = max(ans, d);
        }
    for(int i = k; i + k <= n; ++i)
        for(int j = k; j+k <= m; ++j)
        {
            int d = ru[i][j+1] + rd[i+1][j+1] + lu[n][j];
            ans = max(ans, d);
        }
    for(int i = k; i + k <= n; ++i)
        for(int j = k; j+k <= m; ++j)
        {
            int d = lu[i][j] + ru[i][j+1] + rd[i+1][1];
            ans = max(ans, d);
        }
    for(int i = k; i + k <= n; ++i)
        for(int j = k; j+k <= m; ++j)
        {
            int d = lu[i][m] + ld[i+1][j] + rd[i+1][j+1];
            ans = max(ans, d);
        }
    printf("%d\n", ans);
    return 0;
}
