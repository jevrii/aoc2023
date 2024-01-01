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

void solve()
{
    vector<string> raw_input;
    for (string s; getline(cin, s);) {
        raw_input.push_back(s);
    }

    int n = raw_input.size();
    int m = raw_input[0].size();

    vector<uint8_t> is_empty_row(n);
    vector<uint8_t> is_empty_col(m);

    for (int i = 0; i < n; i++) {
        bool has_hash = false;
        for (int j = 0; j < m; j++) {
            if (raw_input[i][j] == '#') {
                has_hash = true;
                break;
            }
        }
        is_empty_row[i] = !has_hash;
    }

    for (int i = 0; i < m; i++) {
        bool has_hash = false;
        for (int j = 0; j < n; j++) {
            if (raw_input[j][i] == '#') {
                has_hash = true;
                break;
            }
        }
        is_empty_col[i] = !has_hash;
    }

    vector<pii> hashes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (raw_input[i][j] == '#') {
                hashes.push_back({i, j});
            }
        }
    }

    long long ans = 0;
    for (int _i = 0; _i < hashes.size(); _i++) {
        for (int _j = _i + 1; _j < hashes.size(); _j++) {
            const auto& a = hashes[_i];
            const auto& b = hashes[_j];

            long long cur_ans = abs(a.fi - b.fi) + abs(a.se - b.se);

            const int EMPTY_MULTIPLIER = 1'000'000;

            for (int i = min(a.fi, b.fi); i <= max(a.fi, b.fi); i++) {
                if (is_empty_row[i]) {
                    cur_ans += EMPTY_MULTIPLIER - 1;
                }
            }
            for (int i = min(a.se, b.se); i <= max(a.se, b.se); i++) {
                if (is_empty_col[i]) {
                    cur_ans += EMPTY_MULTIPLIER - 1;
                }
            }

            ans += cur_ans;
            //            cerr << _i+1 << "{" << a.fi << "," << a.se << "}";
            //            cerr << _j+1 << "{" << b.fi << "," << b.se << "}";
            //            cerr << " " << cur_ans << "\n";
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
