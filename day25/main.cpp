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

class DSU {
public:
    DSU(int n)
    {
        n_ = n;
        par_.resize(n);
        iota(par_.begin(), par_.end(), 0);
        size_.resize(n);
        fill(size_.begin(), size_.end(), 1);
    }

    int get(int x)
    {
        assert(0 <= x && x <= n_);
        return par_[x] == x ? x : par_[x] = get(par_[x]);
    }

    bool join(int x, int y)
    {
        assert(0 <= x && x <= n_);
        assert(0 <= y && y <= n_);

        x = get(x), y = get(y);
        if (x == y) {
            return false;
        }
        par_[x] = y;
        size_[y] += size_[x];
        return true;
    }

    int size(int x) { return size_.at(get(x)); }

private:
    int n_;
    vector<int> par_;
    vector<int> size_;
};

class karger_runner {
public:
    karger_runner(int n, const vector<pii>& edges)
        : n_(n)
        , edges_(edges)
    {}

    int run()
    {
        const int ITERS = 5000;
        int ans = 0;
        int min_cut = INF;

        for (int iter = 0; iter < ITERS; ++iter) {
            auto result = do_iteration();
            if (result.fi < min_cut) {
                min_cut = result.fi;
                map<int, int> groups;
                for (int i = 0; i < n_; i++) {
                    groups[result.se.get(i)] = result.se.size(i);
                }
                ans = groups.begin()->se * groups.rbegin()->se;
            }
        }
        return ans;
    }

private:
    pair<int, DSU> do_iteration()
    {
        DSU dsu(n_);
        int group_cnt = n_;

        vector<pii> edges_cpy = edges_;
        shuffle(edges_cpy.begin(), edges_cpy.end(), rng);

        for (size_t i = 0; i < edges_cpy.size(); ++i) {
            int x = edges_cpy[i].fi;
            int y = edges_cpy[i].se;
            if (dsu.join(x, y)) {
                --group_cnt;
            }
            if (group_cnt == 2) {
                break;
            }
        }
        int cut = 0;
        for (const auto& edge : edges_cpy) {
            if (dsu.get(edge.fi) != dsu.get(edge.se)) {
                ++cut;
            }
        }
        return {cut, dsu};
        assert(0);
    }

private:
    const int n_;
    const vector<pii> edges_;
};

int name_to_idx(const string& s)
{
    static map<string, int> m;
    if (m.count(s)) {
        return m[s];
    }
    return m[s] = m.size();
}

void solve()
{
    vector<pii> edges;
    set<string> names;

    for (string s; getline(cin, s);) {
        if (s.empty()) {
            continue;
        }
        stringstream ss(s);
        string src;
        ss >> src;
        src.pop_back();
        names.insert(src);

        for (string nxt; ss >> nxt;) {
            names.insert(nxt);
            edges.push_back({name_to_idx(src), name_to_idx(nxt)});
        }
    }

    int n = names.size();
    karger_runner runner(n, edges);
    cout << runner.run() << '\n';
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
