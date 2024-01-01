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

const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, 1, -1, 0};
bool vis[1500][1500] = {0};
int dis[1500][1500] = {0};

pii calculate(const vector<string>& a, pii start, int target_dis)
{
    memset(vis, 0, sizeof(vis));
    memset(dis, 0, sizeof(dis));
    const int n = a.size();
    const int m = a[0].size();

    queue<pii> q;
    q.push(start);
    dis[start.fi][start.se] = 0;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            pii nxt{cur.fi + dx[d], cur.se + dy[d]};
            if (nxt.fi < 0 || nxt.fi >= n || nxt.se < 0 || nxt.se >= m) {
                continue;
            }
            if (a[nxt.fi][nxt.se] == '#') {
                continue;
            }
            if (vis[nxt.fi][nxt.se]) {
                continue;
            }
            q.push(nxt);
            vis[nxt.fi][nxt.se] = true;
            dis[nxt.fi][nxt.se] = dis[cur.fi][cur.se] + 1;
        }
    }

    pii ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (vis[i][j] && (dis[i][j] <= target_dis)) {
                if (dis[i][j] % 2 == target_dis % 2) {
                    ++ans.fi;
                } else {
                    ++ans.se;
                }
            }
        }
    }

    return ans;
}

void solve()
{
    vector<string> a;
    for (string s; getline(cin, s);) {
        a.push_back(s);
    }

    int n = a.size();
    int m = a[0].size();

    pii start;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == 'S') {
                start = {i, j};
            }
        }
    }
    //    cout << calculate(a, start, 64).fi << '\n';

    {
        vector<string> big_a;
        for (int i = 0; i < 9 * 131; ++i) {
            big_a.push_back("");
            for (int j = 0; j < 9 * 131; ++j) {
                big_a.back().push_back(a[i % 131][j % 131]);
            }
        }
        cerr << big_a[4 * 131 + 65][4 * 131 + 65] << '\n';
        pii big_start = {4 * 131 + 65, 4 * 131 + 65};
        cout << calculate(big_a, big_start, 65).fi << '\n';
        cout << calculate(big_a, big_start, 131 + 65).fi << '\n';
        cout << calculate(big_a, big_start, 131 * 2 + 65).fi << '\n';
        cout << calculate(big_a, big_start, 131 * 3 + 65).fi << '\n';
        cout << calculate(big_a, big_start, 131 * 4 + 65).fi << '\n';

        // then interpolate using lagrange for 202300 (day 9)
    }
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
