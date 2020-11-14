//https://codeforces.com/group/FLVn1Sc504/contest/274493/problem/E
#include <bits/stdc++.h>
#define fi first
#define se second

typedef long long ll;

const ll N = 100005;
const ll INF = (ll)1e18;

using namespace std;

typedef pair<ll, ll> Line;

struct operation {
    ll pos, top;
    Line overwrite;
};
vector<operation> undoList;
Line lines[N];
ll n, top = 0;

vector<Line> G[100111];
ll s[100111], v[100111];
ll dp[100111], d[100111];

ll fx(ll x, Line a) {
    return 1LL * a.fi * x + a.se;
}

ll get(ll x) {
    ll l = 0, r = top - 1;
    ll ans = fx(x, lines[l]);

    /////////////////////////////
    while(l <= r) {
        ll mid = l + r >> 1;
        if (fx(x, lines[mid]) < fx(x, lines[mid + 1])) 
            r = mid - 1;
        else l = mid + 1;

        ans = min(ans, min(fx(x, lines[mid]), fx(x, lines[mid + 1])));
    }

    return ans;
}

bool bad(Line a, Line b, Line c) {
    return double(a.se - b.se) / double(b.fi - a.fi) >= double(a.se - c.se) / double(c.fi - a.fi);
}

void add(Line newline) {
    ll l = 0, r = top - 1, k = top;
    while(l <= r) {
        ll mid = l + r >> 1;
        if (bad(lines[mid - 1], lines[mid], newline))
            k = mid, r = mid - 1;
        else l = mid + 1;
    }

    undoList.push_back({k, top, lines[k]});
    top = k + 1;
    lines[k] = newline;

    // for (ll i = 0; i < top; i++) {
    //     cout << lines[i].fi << " " << lines[i].se << endl;
    // }
}

void undo() {
    operation opec = undoList.back(); undoList.pop_back();
    top = opec.top; lines[opec.pos] = opec.overwrite;
}

void dfs(ll u, ll par) {
    // cout << u << " " << d[u] << endl;
    if (u > 1) {
        dp[u] = get(v[u]) + d[u] * v[u] + s[u];
    }
    add({-d[u], dp[u]});

    for (auto edge : G[u]) {
        if (edge.fi == par) continue;
        d[edge.fi] = d[u] + edge.se;
        dfs(edge.fi, u);
    }
    undo();
}

int main() {
    cin >> n;
    for (ll i = 1; i < n; i++) {
        ll x, y, z; cin >> x >> y >> z;
        G[x].push_back({y, z});
        G[y].push_back({x, z});
    }
    for (ll i = 2; i <= n; i++) {
        cin >> s[i] >> v[i];
    }

    dfs(1, 0);

    for (ll i = 2; i <= n; i++) {
        cout << dp[i] << " ";
    }
}
