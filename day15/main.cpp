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

vector<string> parse_input()
{
    string line;
    cin >> line;
    for (char& c : line) {
        if (c == ',') {
            c = ' ';
        }
    }
    vector<string> ret;
    stringstream ss(line);

    string s;
    while (ss >> s) {
        ret.push_back(s);
    }
    return ret;
}

enum class OPER_TYPE {
    REMOVE,
    EMPLACE,
};

struct lens_t {
    string label;
    int val{};
};

void solve()
{
    vector<vector<lens_t>> boxes(256);
    for (const auto& s : parse_input()) {
        int hash = 0;
        OPER_TYPE op;
        string label;
        for (char c : s) {
            if (c == '=') {
                op = OPER_TYPE::EMPLACE;
                break;
            }
            if (c == '-') {
                op = OPER_TYPE::REMOVE;
                break;
            }
            hash += c;
            hash *= 17;
            hash %= 256;
            label.push_back(c);
        }

        if (op == OPER_TYPE::REMOVE) {
            auto& box = boxes[hash];
            auto it = find_if(
                box.begin(), box.end(), [&](const lens_t& lens) { return lens.label == label; });
            if (it != box.end()) {
                box.erase(it);
            }
        } else if (op == OPER_TYPE::EMPLACE) {
            int val = s.back() - '0';
            auto& box = boxes[hash];
            auto it = find_if(
                box.begin(), box.end(), [&](const lens_t& lens) { return lens.label == label; });
            if (it != box.end()) {
                it->val = val;
            } else {
                box.push_back({label, val});
            }
        }
    }

    long long ans = 0;
    for (size_t i = 0; i < boxes.size(); ++i) {
        for (size_t j = 0; j < boxes[i].size(); ++j) {
            ans += (i + 1) * (j + 1) * boxes[i][j].val;
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
