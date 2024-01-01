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

namespace task {
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

enum LEVEL {
    LOW,
    HIGH,
};

struct msg_event_t {
    string src;
    string dst;
    LEVEL level{};
};

queue<msg_event_t> q;

map<string, vector<string>> children;
map<string, vector<string>> parents;
set<string> watched_modules;
map<string, int> periods;

class module;

map<string, std::unique_ptr<module>> modules;

class module {
public:
    module(const string& name) :name_(name) {}

    virtual void init() {}

    string name() { return name_; }

    virtual void recv(const string& src, LEVEL level) = 0;

    LEVEL last_sent() const { return last_sent_; }

protected:
    void send_to_children(LEVEL level)
    {
        last_sent_ = level;
        for (const auto& child : children[name_]) {
            msg_event_t ev;
            ev.src = name_;
            ev.dst = child;
            ev.level = level;
            q.push(ev);
        }
    }

private:
    LEVEL last_sent_ = LOW;
    string name_;
};

class flip_flop : public module {
    // Flip-flop modules (prefix %) are either on or off; they are initially off. If a flip-flop module receives a high pulse,
    // it is ignored and nothing happens. However, if a flip-flop module receives a low pulse, it flips between on and off.
    // If it was off, it turns on and sends a high pulse. If it was on, it turns off and sends a low pulse.
public:
    flip_flop(const string& name)
        : module(name)
    {}

    void recv(const string& /* src */, LEVEL level) override
    {
        if (level == HIGH) {
            return;
        }
        if (state) {
            send_to_children(LOW);
        } else {
            send_to_children(HIGH);
        }
        state = !state;
    }

private:
    bool state = false;
};

size_t g_iter = 0;

class conjunction : public module {
    // Conjunction modules (prefix &) remember the type of the most recent pulse received from each of their connected
    // input modules; they initially default to remembering a low pulse for each input. When a pulse is received,
    // the conjunction module first updates its memory for that input. Then, if it remembers high pulses for all inputs,
    // it sends a low pulse; otherwise, it sends a high pulse.
public:
    conjunction(const string& name)
        : module(name)
    {}

    void init() override
    {
        for (const auto& par : parents[name()]) {
            memory_[par] = LOW;
        }
    }

    void recv(const string& src, LEVEL level) override
    {
        memory_.at(src) = level;
        for (const auto& [one_name, one_level] : memory_) {
            if (one_level != HIGH) {
                send_to_children(HIGH);
                if (watched_modules.count(name())) {
                    if (!periods.count(name())) {
                        periods[name()] = g_iter;
                    }
                }
                return;
            }
        }
        send_to_children(LOW);
    }

private:
    map<string, LEVEL> memory_;
};

class broadcaster : public module {
public:
    broadcaster()
        : module("broadcaster")
    {}

    void recv(const string& /* src */, LEVEL /* level */) override { send_to_children(LOW); }
};

void solve()
{
    auto raw_input = parse_input();
    for (const auto& line : raw_input) {
        stringstream ss(line);  // &mq -> gq, xn, fv, km, lh, xv, sj
        string name;
        ss >> name;
        string arrow;
        ss >> arrow;

        char type = name[0];

        if (name != "broadcaster") {
            name = name.substr(1);
        }

        for (string child; ss >> child;) {
            if (child.back() == ',') {
                child.pop_back();
            }
            children[name].push_back(child);
            parents[child].push_back(name);
        }

        if (name == "broadcaster") {
            modules[name] = std::make_unique<broadcaster>();
        } else if (type == '%') {
            // flip-flop module (as indicated by the % prefix)
            modules[name] = std::make_unique<flip_flop>(name);
        } else if (type == '&') {
            // conjunction module (as indicated by the & prefix)
            modules[name] = std::make_unique<conjunction>(name);
        } else {
            cerr << "unknown " << name << '\n';
            assert(0);
        }
    }

    for (const auto& [module_name, ptr] : modules) {
        ptr->init();
    }

    for (const string& s : parents[parents["rx"][0]]) {
        watched_modules.insert(s);
    }

    long long clow = 0;
    long long chigh = 0;

    for (size_t iter = 1; iter <= 10000; ++iter) {
        g_iter = iter;
        msg_event_t button_event;
        button_event.src = "button";
        button_event.dst = "broadcaster";
        button_event.level = LOW;

        q.push(button_event);
        bool ok = false;

        while (!q.empty()) {
            auto msg = q.front();
            if (msg.level == LOW) {
                ++clow;
            } else {
                ++chigh;
            }

            q.pop();
            if (modules.count(msg.dst)) {
                modules.at(msg.dst)->recv(msg.src, msg.level);
            }
        }

        if (iter == 1000) {
            cout << "Part 1: " << clow * chigh << '\n';
        }
    }

    long long period_lcm = 1;
    auto lcm_func = [](long long x, long long y) {
        long long g = __gcd(x, y);
        return x / g * y;
    };

    for (const string& s : watched_modules) {
        assert(periods.count(s));
        period_lcm = lcm_func(period_lcm, periods[s]);
    }

    cout << "Part 2: " << period_lcm << '\n';
}
}  // namespace task

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
        task::solve();
    }

#ifdef LOCAL
    cerr << "TIME ELAPSED: " << double(clock() - start_time) / CLOCKS_PER_SEC << '\n';
#endif
}
