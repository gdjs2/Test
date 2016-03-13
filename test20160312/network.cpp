#include <cstdio>
#include <queue>
#include <memory.h>
#define mem(x, y) memset(x, y, sizeof(x))

typedef long long ll;
const int Maxn = 1100;
const ll oo = 0x3f3f3f3f3f3f3f3f * 1LL;
ll n, m;

ll min(ll a, ll b)
{
    return a < b ? a : b;
}

ll read()
{
    ll x = 0; char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x;
}

namespace Map
{
    ll fir[Maxn], nxt[Maxn*200], to[Maxn*200], cnt = 0, dist[Maxn*200];
    void add(ll a, ll b, ll c)
    {
        nxt[++cnt] = fir[a];
        fir[a] = cnt;
        to[cnt] = b;
        dist[cnt] = c;
    }
    bool inq[Maxn];
    void dijk(ll *d, ll s)
    {
        d[s] = 0;
        std::queue<ll> q;
        q.push(s);
        while(!q.empty())
        {
            ll now = q.front(); q.pop();
            for(ll i = fir[now]; i; i = nxt[i])
            if(d[to[i]] > d[now]+dist[i])
            {
                d[to[i]] = d[now]+dist[i];
                if(!inq[to[i]]) q.push(to[i]);
            }
        }
    }
}

namespace Flow
{
    ll level[Maxn], iter[Maxn];
    ll fir[Maxn], nxt[Maxn*200], to[Maxn*200], cap[Maxn*200], cnt = 0;
    ll find(ll x)
    {
        return x&1 ? x+1 : x-1;
    }
    void add(ll a, ll b, ll c)
    {
        nxt[++cnt] = fir[a];
        fir[a] = cnt;
        to[cnt] = b;
        cap[cnt] = c;
        return;
    }
    void bfs(ll s)
    {
        std::queue<ll> q;
        q.push(s);
        while(!q.empty())
        {
            ll now = q.front(); q.pop();
            for(ll i = fir[now]; i; i = nxt[i])
            if(cap[i] > 0 && level[to[i]] == -1)
            {
                level[to[i]] = level[now]+1;
                q.push(to[i]);
            }
        }
    }
    ll dfs(ll s, ll e, ll f)
    {
        if(s == e) return f;
        for(ll& i = iter[s]; i; i = nxt[i])
        if(cap[i] && level[to[i]] > level[s])
        {
            ll fl = dfs(to[i], e, min(f, cap[i]));
            if(fl)
            {
                cap[i] -= fl;
                cap[find(i)] += fl;
                return fl;
            }
        }
        return 0;
    }
    ll maxflow(ll s, ll e)
    {
        ll flow = 0;
        for(;;)
        {
            mem(level, -1);
            level[0] = 1;
            bfs(0);
            if(level[e] == -1) return flow;
            for(ll i = s; i <= e; ++i) iter[i] = fir[i];
            ll f;
            while(f = dfs(s, e, oo)) flow += f;
        }
        return 0;
    }
}

ll f[Maxn], d[Maxn];
int main()
{
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    n = read(); m = read();
    for(ll i = 1; i <= m; ++i)
    {
        ll a = read(), b = read(), c = read();
        Map::add(a, b, c); Map::add(b, a, c);
    }
    mem(f, 0x3f); mem(d, 0x3f);
    Map::dijk(f, 1); Map::dijk(d, n);
    for(int i = 1; i <= n; ++i)
        for(ll j = Map::fir[i]; j; j = Map::nxt[j])
            if(f[i] + d[Map::to[j]] + Map::dist[j] == f[n]) Flow::add(i+n, Map::to[j], oo), Flow::add(Map::to[j], i+n, 0);// printf("%d %d\n", i, Map::to[j]);
    for(int i = 1; i <= n; ++i)
    {
        ll c = read();
        (i==1||i==n) ? c = oo : 1 ;
        Flow::add(i, i+n, c);
        Flow::add(i+n, i, 0);
    }
    Flow::add(0, 1, oo); Flow::add(1, 0, 0);
    Flow::add(2*n, 2*n+1, oo); Flow::add(2*n+1, 2*n, 0);
    printf("%lld\n", Flow::maxflow(0, 2*n+1));
    return 0;
}
