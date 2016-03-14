#include <cstdio>
#include <memory.h>
const int oo = 0x3f3f3f3f;
const int Maxn = 5 * (int)1e5 + 10;
int n, m, s, p, ans = 0;

namespace Go
{
    int fir[Maxn], nxt[Maxn], to[Maxn], cnt = 0, k = 0, num[Maxn];
    bool vis[Maxn];
    void add(int a, int b)
    {
        nxt[++cnt] = fir[a]; fir[a] = cnt; to[cnt] = b;
        return;
    }
    void dfs(int now)
    {
        vis[now] = true;
        for(int i = fir[now]; i; i = nxt[i])
            if(!vis[to[i]]) dfs(to[i]);
        num[++k] = now;
        return;
    }
}

namespace Back
{
    int fir[Maxn], nxt[Maxn], to[Maxn], cnt = 0, bel[Maxn], k = 0, val[Maxn];
    int v[Maxn];
    bool vis[Maxn];
    void add(int a, int b)
    {
        nxt[++cnt] = fir[a]; fir[a] = cnt; to[cnt] = b;
        return;
    }
    void dfs(int now)
    {
        bel[now] = k;
        v[k] += val[now];
        vis[now] = true;
        for(int i = fir[now]; i; i = nxt[i])
            if(!vis[to[i]]) dfs(to[i]);
        return;
    }
}

namespace s_r
{
    int fir[Maxn], nxt[Maxn], to[Maxn], cnt = 0;
    int val[Maxn], q[Maxn], l = 1, r = 0, dist[Maxn];
    bool inq[Maxn];
    void add(int a, int b, int c)
    {
        nxt[++cnt] = fir[a]; fir[a] = cnt; to[cnt] = b;
        val[cnt] = c; return ;
    }
    void SPFA()
    {
        memset(dist, 0x3f, sizeof(dist));
        dist[0] = 0; q[++r] = 0;
        inq[0] = true;
        while(l <= r)
        {
            int now = q[l++];
            inq[now] = false;
            for(int i = fir[now]; i; i = nxt[i])
                if(dist[to[i]] > dist[now] + val[i])
                {
                    dist[to[i]] = dist[now] + val[i];
                    if(!inq[to[i]])
                    { q[++r] = to[i]; inq[to[i]] = true; }
                }
        }
        return ;
    }
}

int main()
{
    freopen("atm.in", "r", stdin);
    freopen("atm.out", "w", stdout);
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= m; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        Go::add(a, b); Back::add(b, a);
    }
    for(int i = 1; i <= n; ++i)
        scanf("%d", &Back::val[i]);
    for(int i = 1; i <= n; ++i)
        if(!Go::vis[i]) Go::dfs(i);
    for(int i = n; i; --i)
        if(!Back::vis[Go::num[i]]) { ++Back::k; Back::dfs(Go::num[i]); }
    // for(int i = 1; i <= n; ++i) printf("%d ", Back::bel[i]);
    using namespace s_r;
    for(int i = 1; i <= n; ++i)
        for(int j = Go::fir[i]; j; j = Go::nxt[j])
        if(Back::bel[i] != Back::bel[Go::to[j]])
        {
            add(Back::bel[i], Back::bel[Go::to[j]], -Back::v[Back::bel[Go::to[j]]]);
            // printf("%d - %d\n", Back::bel[i], Back::bel[Go::to[j]]);
        }
    scanf("%d %d", &s, &p);
    add(0, Back::bel[s], -Back::v[Back::bel[s]]);
    SPFA();
    for(int i = 1; i <= p; ++i)
    {
        int cap;
        scanf("%d", &cap);
        if(-dist[Back::bel[cap]] > ans) ans = -dist[Back::bel[cap]];
    }
    // for(int i = 1; i <= Back::k; ++i) printf("%d ", dist[i]);
    printf("%d\n", ans);
    return 0;
}
