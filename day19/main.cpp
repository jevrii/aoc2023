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

struct range_t {
    pii val[4];
};

pair<pii, pii> split(pii src, int x)
{
    // [src.fi, src.se), val < x

    if (src.fi < x && x < src.se) {
        // [src.fi, x) [x, src.se)
        return {{src.fi, x}, {x, src.se}};
    }
    if (src.se <= x) {
        return {src, {x, x}};
    }
    return {{x, x}, src};
}

using task_func_t = function<pair<range_t, range_t>(const range_t&)>;

task_func_t build_func(const string& s)
{
    // a<1989
    const string xmas = "xmas";
    int idx = xmas.find(s[0]);
    char oper = s[1];
    int split_pos = stoi(s.substr(2));

    return [split_pos, idx, oper](const range_t& r) {
        // val < x

        // val > x
        // !(val <= x)
        // !(val < x + 1)
        pair<pii, pii> splitted = split(r.val[idx], split_pos + (oper == '>' ? +1 : 0));
        range_t c1 = r;
        range_t c2 = r;
        c1.val[idx] = splitted.fi;
        c2.val[idx] = splitted.se;

        if (oper == '>') {
            swap(c1, c2);
        }
        return make_pair(c1, c2);
    };
}

struct task_t {
    task_func_t func;
    string nxt;
};

long long len(const pii& x)
{
    if (x.fi >= x.se) {
        return 0;
    }
    return x.se - x.fi;
}

struct workflow_t {
    vector<task_t> tasks;
    string def;
};

map<string, workflow_t> workflows;

long long dfs(const string& s, const range_t& r)
{
    if (s == "R") {
        return 0;
    }
    if (s == "A") {
        long long ret = 1;
        for (int i = 0; i < 4; ++i) {
            ret *= len(r.val[i]);
        }
        return ret;
    }
    long long ans = 0;
    range_t cur = r;
    for (const auto& t : workflows[s].tasks) {
        auto res = t.func(cur);
        ans += dfs(t.nxt, res.first);
        cur = res.second;
    }
    ans += dfs(workflows[s].def, cur);
    return ans;
}

void solve()
{
    for (string s; getline(cin, s);) {
        // ht{s<1042:A,a<3744:A,a>3879:lb,zsj}
        for (char& c : s) {
            if (c == ',' || c == '{' || c == '}') {
                c = ' ';
            }
        }
        stringstream ss(s);
        string name;
        ss >> name;
        vector<string> tasks;
        for (string t; ss >> t;) {
            tasks.push_back(t);
        }
        string def = tasks.back();
        tasks.pop_back();

        workflow_t w;
        w.def = def;
        for (string t : tasks) {
            for (char& c : t) {
                if (c == ':') {
                    c = ' ';
                }
            }
            stringstream ss2(t);
            string f, n;
            ss2 >> f >> n;
            task_t task;
            task.func = build_func(f);
            task.nxt = n;
            w.tasks.push_back(task);
        }
        workflows[name] = w;
    }

    range_t start;
    for (int i = 0; i < 4; ++i) {
        start.val[i] = {1, 4001};
    }
    cout << dfs("in", start) << '\n';
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
