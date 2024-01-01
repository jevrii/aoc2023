#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#pragma GCC optimize("trapv")
using namespace std;

#define pii pair<int, int>
#define pll pair<long long, long long>
#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define DEBUG 1
#define cerr   \
    if (DEBUG) \
    cerr
#define test cerr << "hi\n";

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<long long>(l, r)(rng)
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;

#define MAXN 200005
#define INF 0x3f3f3f3f3f3f3f3f
//#define MOD 998244353LL
#define MOD 1000000007LL

vector<string> a;
int nr, nc;
bool vis[150][150];
int ans;
int cnt = 0;

int dr[] = {-1, 0, 0, 1};
int dc[] = {0, -1, 1, 0};
map<char, pii> m;

void dfs(int r, int c)
{
    if (r == nr - 1) {
        ans = max(ans, cnt - 1);
        return;
    }
    for (int d = 0; d < 4; ++d) {
        int nxt_r = r + dr[d];
        int nxt_c = c + dc[d];
        if (nxt_r < 0 || nxt_r >= nr || nxt_c < 0 || nxt_c >= nc) {
            continue;
        }
        if (vis[nxt_r][nxt_c]) {
            continue;
        }
        if (a[nxt_r][nxt_c] == '#') {
            continue;
        }
        //        if (a[nxt_r][nxt_c] != '.') {
        //            auto op = m.find(a[nxt_r][nxt_c])->second;
        //            if (op != make_pair(dr[d], dc[d])) {
        //                continue;
        //            }
        //        }
        ++cnt;
        vis[nxt_r][nxt_c] = true;
        dfs(nxt_r, nxt_c);
        --cnt;
        vis[nxt_r][nxt_c] = false;
    }
}

void solve()
{
    m['>'] = {0, 1};
    m['<'] = {0, -1};
    m['^'] = {-1, 0};
    m['v'] = {1, 0};
    for (string s; getline(cin, s);) {
        if (s.empty()) {
            continue;
        }
        a.push_back(s);
    }
    nr = a.size();
    nc = a[0].size();

    vis[0][1] = true;
    ++cnt;
    dfs(0, 1);
    cout << ans << '\n';

    //    for (string s : a) {
    //        cout << s << '\n';
    //    }
}

int main()
{
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    auto start_time = clock();
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    //    cin >> t;
    for (int no = 1; no <= t; no++) {
        //        cout << "Case #" << no << ": ";
        solve();
    }

#ifdef LOCAL
    cerr << "TIME ELAPSED: " << double(clock() - start_time) / CLOCKS_PER_SEC << '\n';
#endif
}
