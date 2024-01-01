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

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

enum DIRECTION {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NONE,
};

struct queue_item_t {
    int r{};
    int c{};
    int cost{};
    DIRECTION dir{};
};

vector<string> parse_input()
{
    vector<string> ret;
    for (string s; getline(cin, s);) {
        if (!s.empty()) {
            ret.push_back(s);
        }
    }
    return ret;
}

void solve()
{
    auto raw_input = parse_input();

    int nr = raw_input.size();
    int nc = raw_input[0].size();

    int a[150][150] = {0};
    for (int r = 0; r < nr; ++r) {
        for (int c = 0; c < nc; ++c) {
            a[r][c] = raw_input[r][c] - '0';
        }
    }

    auto cmp = [](const queue_item_t& lhs, const queue_item_t& rhs) { return lhs.cost > rhs.cost; };
    priority_queue<queue_item_t, vector<queue_item_t>, decltype(cmp)> q(cmp);
    bool vis[150][150][10] = {0};

    queue_item_t start;
    start.r = 0;
    start.c = 0;
    start.cost = 0;
    start.dir = NONE;
    q.push(start);

    int ans = INF;

    while (!q.empty()) {
        auto node = q.top();
        q.pop();
        if (vis[node.r][node.c][node.dir]) {
            continue;
        }
        //        cerr << node.r << ',' << node.c << ' ' << node.dir << ' ' << node.cost << '\n';
        vis[node.r][node.c][node.dir] = true;
        if (node.r == nr - 1 && node.c == nc - 1) {
            ans = min(ans, node.cost);
        }

        for (int dir = UP; dir <= LEFT; ++dir) {
            if (dir == node.dir) {
                continue;
            }
            if (dir == (node.dir ^ 0b10)) {
                continue;
            }
            int step_cost = 0;
            for (int len = 1; len <= 10; ++len) {
                int nxt_r = node.r + dr[dir] * len;
                int nxt_c = node.c + dc[dir] * len;
                if (nxt_r < 0 || nxt_r >= nr) {
                    break;
                }
                if (nxt_c < 0 || nxt_c >= nc) {
                    break;
                }
                step_cost += a[nxt_r][nxt_c];
                if (len <= 3) {
                    continue;
                }
                if (vis[nxt_r][nxt_c][dir]) {
                    continue;
                }
                queue_item_t next_node;
                next_node.r = nxt_r;
                next_node.c = nxt_c;
                next_node.cost = node.cost + step_cost;
                next_node.dir = static_cast<DIRECTION>(dir);
                q.push(next_node);
            }
        }
    }

    cout << ans << '\n';
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
