#include <cstdio>
#include <set>
#include <algorithm>

const int oo = 0x3f3f3f3f;
const int Maxn = 200010;
int n, nxt[Maxn][20], cnt = 0;
int x[Maxn], y[Maxn];

struct Node
{
    int l, r;
    Node(int a=0, int b=0):l(a),r(b){}
    bool operator < (const Node& b) const
    { return b.r == r ? l < b.l : r < b.r; }
};

Node a[Maxn], b[Maxn];
int count(int l, int r)
{
    int k = std::lower_bound(x+1, x+1+cnt, l) - x;
    if(y[k] > r || k > cnt) return 0;
    int ret = 1;
    for(int i = 19; i>=0; --i)
    if(nxt[k][i] && y[nxt[k][i]] <= r) ret += (1<<i), k = nxt[k][i];
    return ret;
}

int main()
{
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%d %d", &a[i].l, &a[i].r);
        b[i] = a[i];
    }
    std::sort(a+1, a+1+n);
    for(int i = 1; i <= n; ++i)
    {
        if(!cnt) a[++cnt] = a[i];
        if(a[i].l <= a[cnt].l) continue;
        a[++cnt] = a[i];
    }
    for(int i = 1; i <= cnt; ++i) x[i] = a[i].l, y[i] = a[i].r;
    for(int i = 1, j = 1; i <= cnt; ++i)
    {
        while(a[j].l <= a[i].r && j <= cnt) ++j;
        if(j == cnt+1) nxt[i][0] = 0;
        else nxt[i][0] = j;
    }
    for(int i = 1; i <= 19; ++i)
        for(int j = 1; j <= cnt; ++j)
        {
            int mx = nxt[j][i-1];
            if(!mx) continue;
            nxt[j][i] = nxt[mx][i-1];
        }
    printf("%d\n", count(-oo, oo));
    std::set<Node> s;
    s.insert(Node(-oo, -oo));
    s.insert(Node(oo, oo));
    for(int i = 1; i <= n; ++i)
    {
        std::set<Node>::iterator p = s.lower_bound(b[i]), q;
        q = p; --q;
        int l1 = b[i].l, r1 = b[i].r, l2 = p->l, r2 = q->r;
        if(l1 <= r2 || r1 >= l2) continue;
        if(count(r2+1, l2-1) == count(r2+1, l1-1) + 1 + count(r1+1, l2-1))
            printf("%d ", i), s.insert(b[i]);
    }
    return 0;
}
