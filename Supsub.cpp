//Problem M Supsub
//The 2020 ICPC Vietnam Northern and Central Provincial
#include<bits/stdc++.h>
using namespace std;

const int inf = 1e9 + 7;

typedef long long ll;
typedef pair<int,int> Line;
typedef pair<long double,Line> Trip;
#define fi first
#define se second

int n, a[100111], res = 0;
int dp[100111], sum[100111];
int step[100111];
map<Line, long double> Map;

long double mx = -1e17;

bool cmpX (Line a, Line b) {
    return a.fi < b.fi;
}

bool cmpLeft(Trip a, Trip b) {
    return a.fi < b.fi;
}

set<Line, decltype(cmpX)*> lines(cmpX);
set<Trip, decltype(cmpLeft)*> query(cmpLeft);

int fx(Line line, int x) {
    return line.fi * x + line.se;
}

bool isBad(Line a, Line b, Line c) {
    return  double(a.se - b.se) /  double(b.fi - a.fi) >=  double(a.se - c.se) /  double(c.fi - a.fi);
}

 double nodes(Line a, Line b) {
    return  double(a.se - b.se) /  double(b.fi - a.fi);
}

void add(Line newLine) {
    set<Line>::iterator l1, l2, l3, l4, l5;

    lines.insert(newLine);
    l3 = lines.find(newLine);
    l1 = l2 = l4 = l5 = l3;
    --l1; --l1; --l2; ++l4; ++l5; ++l5;

    // for (auto c: lines) cout << c.se.fi;
    while (lines.size() >= 3 && l2 != lines.begin() && l3 != lines.begin() && isBad(*l1, *l2, *l3)) {
        lines.erase(l2);
        query.erase({Map[*l2], *l2});

        l2 = l1; --l1;
    }
    while (lines.size() >= 3 && l5 != lines.end() && l4 != lines.end() && isBad(*l3, *l4, *l5)) {
        lines.erase(l4);
        query.erase({Map[*l4], *l4});
        l4 = l5; ++l5;
    }

    if (lines.size() >= 3 && l3 != lines.begin() && l4 != lines.end() && isBad(*l2, *l3, *l4))
        lines.erase(l3);
    else {
        
        if (l4!=lines.end()) {
            query.erase({ Map[*l4], *l4});
            query.insert({nodes(*l3, *l4), *l4});
            Map[*l4] = nodes(*l3, *l4);
        }

        if (l3 == lines.begin()) {
            query.insert({mx, *l3}); 
            Map[*l3] = mx;    
        }
        else {
            query.insert({ nodes(*l2, *l3), *l3});
            Map[*l3] = nodes(*l2, *l3);    
        }
    }
}

ll get(int x) {
    set<Trip> ::iterator it = query.lower_bound({x, {0, 0}}); --it;
    // cout << it->fi << " " << it->se.fi << " " << it->se.se << endl;
    return fx(it->se, x);
}

int main() {
   ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
   #define file ""
   if (fopen(file,"r"));
       freopen(file,"r",stdin);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int  i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i];
        step[i] = step[i - 1] + sum[i];
    }
    for (int i = 1; i <= n; i++) {
        // dp[i] = max(sum[j - 1] * (j - 1 - i) - step[j - 1] + step[i], dp[i]);
        add({-sum[i - 1], sum[i - 1] * (i - 1) - step[i - 1]});
        dp[i] = get(i) + step[i];
        res = max(res, dp[i]);
    }
    cout << res << endl;

    cout << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
