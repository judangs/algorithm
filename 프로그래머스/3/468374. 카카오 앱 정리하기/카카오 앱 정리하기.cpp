#include <queue>
#include <vector>

using namespace std;

namespace {

struct Cell {
    int r;
    int c;
};

bool is_square(const vector<Cell>& cells) {
    int min_r = 1e9;
    int max_r = -1;
    int min_c = 1e9;
    int max_c = -1;

    for (const Cell& cell : cells) {
        min_r = min(min_r, cell.r);
        max_r = max(max_r, cell.r);
        min_c = min(min_c, cell.c);
        max_c = max(max_c, cell.c);
    }

    int height = max_r - min_r + 1;
    int width = max_c - min_c + 1;
    if (height != width || height * width != static_cast<int>(cells.size())) {
        return false;
    }

    vector<vector<char>> filled(height, vector<char>(width, false));
    for (const Cell& cell : cells) {
        filled[cell.r - min_r][cell.c - min_c] = true;
    }

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (!filled[r][c]) {
                return false;
            }
        }
    }

    return true;
}

void shift_app(vector<Cell>& cells, int dr, int dc, int n, int m) {
    for (Cell& cell : cells) {
        cell.r = (cell.r + dr + n) % n;
        cell.c = (cell.c + dc + m) % m;
    }
}

}  // namespace

vector<vector<int>> solution(vector<vector<int>> board, vector<vector<int>> commands) {
    int n = static_cast<int>(board.size());
    int m = static_cast<int>(board[0].size());

    int max_id = 0;
    for (const auto& row : board) {
        for (int id : row) {
            max_id = max(max_id, id);
        }
    }

    vector<vector<Cell>> apps(max_id + 1);
    vector<int> ids;
    vector<char> exists(max_id + 1, false);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            int id = board[r][c];
            if (id == 0) {
                continue;
            }
            apps[id].push_back({r, c});
            if (!exists[id]) {
                exists[id] = true;
                ids.push_back(id);
            }
        }
    }

    const int dr[5] = {0, 0, 1, 0, -1};
    const int dc[5] = {0, 1, 0, -1, 0};

    for (const auto& command : commands) {
        int start = command[0];
        int dir = command[1];

        vector<char> seeds(max_id + 1, false);
        seeds[start] = true;

        while (true) {
            bool has_seed = false;
            for (int id : ids) {
                if (seeds[id]) {
                    has_seed = true;
                    break;
                }
            }
            if (!has_seed) {
                break;
            }

            vector<vector<int>> occupant(n, vector<int>(m, 0));
            for (int id : ids) {
                for (const Cell& cell : apps[id]) {
                    occupant[cell.r][cell.c] = id;
                }
            }

            vector<char> moving(max_id + 1, false);
            queue<int> q;
            for (int id : ids) {
                if (seeds[id]) {
                    moving[id] = true;
                    q.push(id);
                }
            }

            while (!q.empty()) {
                int id = q.front();
                q.pop();

                for (const Cell& cell : apps[id]) {
                    int nr = (cell.r + dr[dir] + n) % n;
                    int nc = (cell.c + dc[dir] + m) % m;
                    int next_id = occupant[nr][nc];
                    if (next_id != 0 && !moving[next_id]) {
                        moving[next_id] = true;
                        q.push(next_id);
                    }
                }
            }

            for (int id : ids) {
                if (moving[id]) {
                    shift_app(apps[id], dr[dir], dc[dir], n, m);
                }
            }

            vector<char> next_seeds(max_id + 1, false);
            for (int id : ids) {
                if (moving[id] && !is_square(apps[id])) {
                    next_seeds[id] = true;
                }
            }
            seeds.swap(next_seeds);
        }
    }

    vector<vector<int>> answer(n, vector<int>(m, 0));
    for (int id : ids) {
        for (const Cell& cell : apps[id]) {
            answer[cell.r][cell.c] = id;
        }
    }

    return answer;
}
