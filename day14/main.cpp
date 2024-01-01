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

void slide_left(string& s)
{
    int right_of_wall = 0;
    int cur_cnt = 0;
    for (int i = 0; i <= s.size(); i++) {
        if (i == s.size() || s[i] == '#') {
            for (int j = right_of_wall; j < right_of_wall + cur_cnt; j++) {
                s[j] = 'O';
            }
            for (int j = right_of_wall + cur_cnt; j < i; j++) {
                s[j] = '.';
            }
            right_of_wall = i + 1;
            cur_cnt = 0;
        } else if (s[i] == 'O') {
            ++cur_cnt;
        }
    }
}

void tilt_north(vector<string>& a, bool need_reverse)
{
    for (int c = 0; c < a[0].size(); c++) {
        string col;
        for (int r = 0; r < a.size(); r++) {
            col.push_back(a[r][c]);
        }
        if (need_reverse) {
            reverse(col.begin(), col.end());
        }
        slide_left(col);
        if (need_reverse) {
            reverse(col.begin(), col.end());
        }
        for (int r = 0; r < a.size(); r++) {
            a[r][c] = col[r];
        }
    }
}

void tilt_west(vector<string>& a, bool need_reverse)
{
    for (int r = 0; r < a.size(); r++) {
        if (need_reverse) {
            reverse(a[r].begin(), a[r].end());
        }
        slide_left(a[r]);
        if (need_reverse) {
            reverse(a[r].begin(), a[r].end());
        }
    }
}

void solve()
{
    vector<string> a;
    for (string s; getline(cin, s);) {
        a.push_back(s);
    }

    map<vector<string>, int> cache;
    int cycle_len = 0;
    int cycle_start = 0;

    const int real_iters = 1'000'000'000;
    for (int i = 0; i < real_iters; i++) {
        if (cache.count(a)) {
            cycle_start = cache[a];
            cycle_len = i - cycle_start;
            cout << "found cache at " << i << ' ' << cycle_start << '\n';
            break;
        }
        cache.insert({a, i});
        tilt_north(a, false);
        tilt_west(a, false);
        tilt_north(a, true);
        tilt_west(a, true);
    }

    const int target = (real_iters - cycle_start) % cycle_len + cycle_start;
    for (const auto& [block, idx] : cache) {
        if (idx == target) {
            a = block;
            break;
        }
    }

    //    for (const auto& s : a) {
    //        cout << s << '\n';
    //    }

    int ans = 0;
    for (int r = 0; r < a.size(); r++) {
        ans += count(a[r].begin(), a[r].end(), 'O') * (a.size() - r);
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
