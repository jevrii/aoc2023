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

using block_t = vector<string>;

vector<block_t> parse_input()
{
    vector<block_t> ret;
    ret.push_back({});
    for (string s; getline(cin, s);) {
        if (s.size() == 0) {
            ret.push_back({});
        } else {
            ret.back().push_back(s);
        }
    }
    return ret;
}

std::optional<int> find_row_reflection(const block_t& block, std::optional<int> skip = nullopt)
{
    int nr = block.size();
    for (int r = 0; r + 1 < nr; r++) {
        if (skip.has_value() && r + 1 == skip.value()) {
            continue;
        }
        vector<string> up, down;
        for (int i = r; i >= 0; i--) {
            up.push_back(block[i]);
        }
        for (int i = r + 1; i < nr; i++) {
            down.push_back(block[i]);
        }
        while (up.size() > down.size()) {
            up.pop_back();
        }
        while (down.size() > up.size()) {
            down.pop_back();
        }

        if (up == down) {
            return r + 1;
        }
    }
    return std::nullopt;
}

std::optional<int> find_col_reflection(const block_t& block, std::optional<int> skip = nullopt)
{
    int nr = block.size();
    int nc = block[0].size();

    for (int c = 0; c + 1 < nc; c++) {
        if (skip.has_value() && c + 1 == skip.value()) {
            continue;
        }
        vector<string> left, right;
        for (int i = c; i >= 0; i--) {
            string s;
            for (int j = 0; j < nr; j++) {
                s.push_back(block[j][i]);
            }
            left.push_back(s);
        }
        for (int i = c + 1; i < nc; i++) {
            string s;
            for (int j = 0; j < nr; j++) {
                s.push_back(block[j][i]);
            }
            right.push_back(s);
        }

        while (left.size() > right.size()) {
            left.pop_back();
        }
        while (right.size() > left.size()) {
            right.pop_back();
        }

        if (left == right) {
            return c + 1;
        }
    }
    return std::nullopt;
}

void flip(char& c)
{
    if (c == '#') {
        c = '.';
        return;
    }
    if (c == '.') {
        c = '#';
        return;
    }
    assert(0);
}

void solve()
{
    vector<block_t> cases = parse_input();

    int sum_c = 0, sum_r = 0;
    for (const auto& block : cases) {
        //        {
        //            auto row_reflection = find_row_reflection(block);
        //            if (row_reflection.has_value()) {
        //                sum_r += row_reflection.value();
        //            }
        //        }
        //        {
        //            auto col_reflection = find_col_reflection(block);
        //            if (col_reflection.has_value()) {
        //                sum_c += col_reflection.value();
        //            }
        //        }

        auto row_reflection = find_row_reflection(block);
        auto col_reflection = find_col_reflection(block);

        //        if (row_reflection) {
        //            cerr << "orig r " << row_reflection.value() << '\n';
        //        }
        //        if (col_reflection) {
        //            cerr << "orig c " << col_reflection.value() << '\n';
        //        }

        auto block_cpy = block;
        for (int i = 0; i < block_cpy.size(); i++) {
            for (int j = 0; j < block_cpy[i].size(); j++) {
                flip(block_cpy[i][j]);
                auto row_reflection_new = find_row_reflection(block_cpy, row_reflection);
                auto col_reflection_new = find_col_reflection(block_cpy, col_reflection);
                flip(block_cpy[i][j]);

                if (col_reflection_new.has_value() && col_reflection_new != col_reflection) {
                    sum_c += col_reflection_new.value();
                    goto end;
                }
                if (row_reflection_new.has_value() && row_reflection_new != row_reflection) {
                    sum_r += row_reflection_new.value();
                    goto end;
                }
            }
        }
        assert(0);
    end:;
    }
    cout << sum_c + sum_r * 100;
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
