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

pair<string, vector<int>> parse_line(const string& line)
{
    stringstream ss(line);
    string s, t;
    ss >> s >> t;
    vector<int> target;
    for (char& c : t) {
        if (c == ',') {
            c = ' ';
        }
    }
    {
        stringstream ss2(t);
        int x;
        while (ss2 >> x) {
            target.push_back(x);
        }
    }
    return {s, target};
}

class dp_calculator {
public:
    dp_calculator(const string& s, const vector<int>& target)
        : s_(s)
        , target_(target)
    {
        memset(dp_, -1, sizeof(dp_));
    }

    long long run() { return dpf(0, 0, 0); }

private:
    long long dpf(int idx, int suffix_len, int match_target_idx)
    {
        if (idx == s_.size()) {
            if (suffix_len == 0) {
                if (match_target_idx == target_.size()) {
                    return 1;
                }
                return 0;
            } else {
                if (match_target_idx + 1 == target_.size() && suffix_len == target_.back()) {
                    return 1;
                }
                return 0;
            }
        }

        long long& ret = dp_[idx][suffix_len][match_target_idx];
        if (ret != -1) {
            return ret;
        }

        char c = s_[idx];

        if (c == '#') {
            return ret = dpf(idx + 1, suffix_len + 1, match_target_idx);
        }
        if (c == '.') {
            if (suffix_len > 0) {
                if (match_target_idx >= target_.size() || suffix_len != target_[match_target_idx]) {
                    return 0;
                }
                return ret = dpf(idx + 1, 0, match_target_idx + 1);
            }
            return dpf(idx + 1, 0, match_target_idx);
        }
        if (c == '?') {
            ret = 0;
            // #
            ret += dpf(idx + 1, suffix_len + 1, match_target_idx);

            // .
            if (suffix_len > 0) {
                if (match_target_idx >= target_.size() || suffix_len != target_[match_target_idx]) {
                    ret += 0;
                } else {
                    ret += dpf(idx + 1, 0, match_target_idx + 1);
                }
            } else {
                ret += dpf(idx + 1, 0, match_target_idx);
            }

            return ret;
        }
        assert(0);
        return -1;
    }

private:
    const string& s_;
    const vector<int>& target_;
    long long dp_[120][120][40];
};

class brute_force_calculator {
public:
    brute_force_calculator(const string& s, const vector<int>& target)
        : s_(s)
        , target_(target)
    {}

    long long run()
    {
        int ans = 0;
        int cnt = count(s_.begin(), s_.end(), '?');
        for (int bs = 0; bs < (1 << cnt); bs++) {
            int idx = 0;
            vector<int> v;
            int cur_len = 0;
            for (char c : s_) {
                if (c == '#') {
                    ++cur_len;
                } else if (c == '?') {
                    if (!!((1 << idx) & bs)) {
                        cur_len++;
                    } else {
                        if (cur_len > 0) {
                            v.push_back(cur_len);
                        }
                        cur_len = 0;
                    }
                    ++idx;
                } else {
                    if (cur_len > 0) {
                        v.push_back(cur_len);
                    }
                    cur_len = 0;
                }
            }
            if (cur_len > 0) {
                v.push_back(cur_len);
            }

            if (v == target_) {
                ans++;
            }
        }
        return ans;
    }

private:
    const string& s_;
    const vector<int>& target_;
};

void solve()
{
    vector<string> raw_input;
    for (string s; getline(cin, s);) {
        raw_input.push_back(s);
    }

    long long ans = 0;

    for (const string& line : raw_input) {
        auto [s, target] = parse_line(line);

        string final_s;
        vector<int> final_target;
        for (int i = 0; i < 5; i++) {
            final_s += s;
            if (i + 1 < 5) {
                final_s += "?";
            }
            final_target.insert(final_target.end(), target.begin(), target.end());
        }

        dp_calculator calculator(final_s, final_target);
        //        dp_calculator calculator(s, target);
        //        brute_force_calculator calculator(s, target);
        long long cur_ans = calculator.run();
        //        cerr << cur_ans << '\n';

        ans += cur_ans;
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
