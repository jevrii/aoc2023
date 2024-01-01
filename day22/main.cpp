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

int a[15][15][400];
int top[15][15];

struct block_t {
    pii x;
    pii y;
    pii z;
};

map<int, set<int>> out;
map<int, set<int>> in;

int topo_proc(int start)
{
    queue<int> q;
    int in_deg[1400] = {0};
    for (const auto& [src, tos] : out) {
        for (int x : tos) {
            ++in_deg[x];
        }
    }

    q.push(start);
    int ans = 0;
    while (!q.empty()) {
        int u = q.front();
        ++ans;
        q.pop();
        for (int v : out[u]) {
            if (!--in_deg[v]) {
                q.push(v);
            }
        }
    }
    return ans - 1;
}

void solve()
{
    // 4,5,12~5,5,12
    vector<block_t> blocks;
    for (string s; getline(cin, s);) {
        for (char& c : s) {
            if (!isdigit(c)) {
                c = ' ';
            }
        }
        block_t b;
        stringstream ss(s);
        ss >> b.x.fi >> b.y.fi >> b.z.fi;
        ss >> b.x.se >> b.y.se >> b.z.se;
        blocks.push_back(b);
    }

    sort(blocks.begin(), blocks.end(),
        [](const block_t& lhs, const block_t& rhs) { return lhs.z.fi < rhs.z.fi; });

    int idx = 0;
    for (const auto& b : blocks) {
        ++idx;
        int max_z = 0;
        for (int x = b.x.fi; x <= b.x.se; ++x) {
            for (int y = b.y.fi; y <= b.y.se; ++y) {
                max_z = max(max_z, top[x][y]);
            }
        }
        int bottom_z = max_z + 1;
        int height = b.z.second - b.z.fi + 1;

        for (int x = b.x.fi; x <= b.x.se; ++x) {
            for (int y = b.y.fi; y <= b.y.se; ++y) {
                for (int z = bottom_z; z < bottom_z + height; ++z) {
                    a[x][y][z] = idx;
                }
                top[x][y] = bottom_z + height - 1;
            }
        }
    }

    for (int x = 0; x < 15; ++x) {
        for (int y = 0; y < 15; ++y) {
            for (int z = 0; z + 1 < 400; ++z) {
                int lo = a[x][y][z];
                int hi = a[x][y][z + 1];
                // lo support hi
                if (lo > 0 && hi > 0 && (lo != hi)) {
                    out[lo].insert(hi);
                    in[hi].insert(lo);
                }
            }
        }
    }

    //    int ans = 0;
    //    for (int i = 1; i <= idx; i++) {
    //        bool can_remove = true;
    //        for (int s : out[i]) {
    //            if (in[s].size() == 1) {
    //                can_remove = false;
    //            }
    //        }
    //        if (can_remove) {
    //            ++ans;
    //        }
    //    }

    int ans = 0;

    for (int v = 1; v <= idx; ++v) {
        ans += topo_proc(v);
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
