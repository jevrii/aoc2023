#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
// #pragma GCC optimize ("trapv")
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
// #define MOD 998244353LL
#define MOD 1000000007LL

class Discretizer {
public:
    int query(string s)
    {
        if (!str_to_int.count(s)) {
            return str_to_int[s] = str_to_int.size();
        }
        return str_to_int[s];
    }

private:
    map<string, int> str_to_int;
};

struct edge_pair_t {
    int left{};
    int right{};
};
vector<edge_pair_t> edges(1000);
vector<uint8_t> is_src(1000);
vector<uint8_t> is_target(1000);

Discretizer discretizer;

int vis[1000][300];
int cnt = 0;
int cnt_valid = 0;
vector<int> period;

void dfs(int node, int action_idx, const string& actions)
{
    if (vis[node][action_idx] != -1) {
        period.push_back(cnt - vis[node][action_idx]);
        cout << cnt - vis[node][action_idx] << ' ' << vis[node][action_idx] << ' ';
        for (int i = 0; i < 1000; i++) {
            if (is_target[i] && vis[i][0] != -1) {
                cout << vis[i][0] << ' ';
            }
        }
        return;
    }

    vis[node][action_idx] = cnt;
    cnt++;
    if (actions[action_idx] == 'L') {
        node = edges[node].left;
    } else {
        node = edges[node].right;
    }

    (action_idx += 1) %= actions.size();
    dfs(node, action_idx, actions);
}

void solve()
{
    vector<string> raw_input;
    for (string line; getline(cin, line);) {
        raw_input.push_back(line);
    }
    string actions = raw_input[0];

    for (int i = 2; i < raw_input.size(); i++) {
        stringstream ss(raw_input[i]);
        string src, eq, left, right;  // BPQ = (VXR, TLN)
        ss >> src >> eq >> left >> right;
        left = left.substr(1, 3);
        right = right.substr(0, 3);
        edge_pair_t e{};
        e.left = discretizer.query(left);
        e.right = discretizer.query(right);
        edges[discretizer.query(src)] = e;

        if (src.back() == 'A') {
            is_src[discretizer.query(src)] = true;
        } else if (src.back() == 'Z') {
            is_target[discretizer.query(src)] = true;
        }
    }

    for (int i = 0; i < raw_input.size(); i++) {
        if (is_src[i]) {
            memset(vis, -1, sizeof(vis));
            cnt = 0;
            cnt_valid = 0;
            dfs(i, 0, actions);
            cout << cnt << ' ' << cnt_valid << '\n';
        }
    }

    for (int i = 0; i < period.size(); i++) {
        cout << period[i] << ",";
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
