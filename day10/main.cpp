#include <bits/stdc++.h>

std::vector<std::string> get_raw_input() noexcept
{
    std::vector<std::string> ret;
    for (std::string line; std::getline(std::cin, line);) {
        ret.push_back(line);
    }
    return ret;
}

class solver {
private:
    struct pos_t {
        size_t r{};
        size_t c{};
    };

public:
    solver(const std::vector<std::string>& data)
        : map_(data)
        , n_rows_(map_.size())
        , n_cols_(map_[0].size())

    {}

    uint32_t run_part_1()
    {
        pos_t start = find_starting_pos();
        reset_dfs();
        dfs(start);
        size_t max_depth = 0;
        for (const auto& neighbour : find_neighbours(start)) {
            max_depth = std::max(max_depth, dfs_depth[neighbour.r][neighbour.c]);
        }
        return (max_depth + 1) / 2;
    }

    size_t run_part_2()
    {
        pos_t start = find_starting_pos();

        reset_dfs();
        dfs(start);
        size_t max_depth = 0;
        pos_t max_neighbour{};
        for (const auto& neighbour : find_neighbours(start)) {
            size_t cur_depth = dfs_depth[neighbour.r][neighbour.c];
            if (cur_depth > max_depth) {
                max_depth = cur_depth;
                max_neighbour = neighbour;
            }
        }

        reset_dfs();
        vis[start.r][start.c] = true;
        visited.push_back(start);
        dfs(max_neighbour);

        // Pick's theorem: A = i + b/2 - 1    (i: interior points, b: boundary points)
        //              => i = A - b/2 + 1
        int area = shoelace_signed_area(visited);
        return area - visited.size() / 2 + 1;
    }

private:
    void dfs(const pos_t& cur, size_t cur_depth = 0)
    {
        visited.push_back(cur);
        vis[cur.r][cur.c] = true;
        dfs_depth[cur.r][cur.c] = cur_depth;
        for (const auto& nxt : find_neighbours(cur)) {
            if (!vis[nxt.r][nxt.c]) {
                dfs(nxt, cur_depth + 1);
            }
        }
    }

    void reset_dfs()
    {
        visited.clear();
        dfs_depth = std::vector<std::vector<size_t>>(n_rows_, std::vector<size_t>(n_cols_));
        memset(vis, 0, sizeof(vis));
    }

    std::vector<pos_t> visited;
    std::vector<std::vector<size_t>> dfs_depth;
    bool vis[1000][1000] = {0};

private:
    pos_t find_starting_pos() const noexcept
    {
        for (size_t i = 0; i < n_rows_; ++i) {
            for (size_t j = 0; j < n_cols_; ++j) {
                if (map_[i][j] == 'S') {
                    return pos_t{
                        .r = i,
                        .c = j,
                    };
                }
            }
        }
        assert(0);
        return {};
    }

    static int shoelace_signed_area(const std::vector<pos_t>& points)
    {
        int sum = 0;
        for (size_t i = 0; i < points.size(); i++) {
            const auto& cur = points[i];
            const auto& nxt = points[(i + 1) % points.size()];
            sum += (int(cur.c) + int(nxt.c)) * (int(cur.r) - int(nxt.r));
        }
        return std::abs(sum) / 2;
    }

    std::vector<pos_t> find_neighbours(const pos_t& src) const noexcept
    {
        //  N
        // E S
        //  W
        static const std::map<char, std::string> PIPE_TO_DIRECTIONS = {
            {'|', "NS"},
            {'-', "EW"},
            {'L', "NE"},
            {'J', "NW"},
            {'7', "SW"},
            {'F', "SE"},
            {'.', ""},
            {'S', "NESW"},
        };

        static const std::map<char, std::pair<int, int>> DIRECTION_TO_DXYS = {
            {'N', {-1, 0}},
            {'E', {0, 1}},
            {'S', {1, 0}},
            {'W', {0, -1}},
        };

        std::vector<pos_t> ret;

        for (char dir : PIPE_TO_DIRECTIONS.at(map_[src.r][src.c])) {
            auto [dr, dc] = DIRECTION_TO_DXYS.at(dir);

            if ((src.r == 0 && dr == -1) || (src.r + dr >= n_rows_)) {
                continue;
            }
            if ((src.c == 0 && dc == -1) || (src.c + dc >= n_cols_)) {
                continue;
            }

            bool has_neighbour_complement_dir = false;
            for (char neighbour_dir : PIPE_TO_DIRECTIONS.at(map_[src.r + dr][src.c + dc])) {
                auto [ndr, ndc] = DIRECTION_TO_DXYS.at(neighbour_dir);
                if (ndr == -dr && ndc == -dc) {
                    has_neighbour_complement_dir = true;
                    break;
                }
            }

            if (has_neighbour_complement_dir) {
                ret.push_back({{src.r + dr}, {src.c + dc}});
            }
        }

        return ret;
    }

private:
    const std::vector<std::string> map_;
    const size_t n_rows_ = 0;
    const size_t n_cols_ = 0;
};

int main()
{
    auto raw_input = get_raw_input();
    solver s(raw_input);
    std::cout << s.run_part_1() << std::endl;
    std::cout << s.run_part_2() << std::endl;
}
