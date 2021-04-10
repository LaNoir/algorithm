#include <string>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int dy[4] = { 1,-1,0,0 };
const int dx[4] = { 0,0,1,-1 };

struct POS {
    int y, x, time;
};

int N, M, res;
int map[50][50];
vector<POS> pos;

int bfs(int pick[]) {
    int empty_count = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (map[y][x] == 0) {
                empty_count++;
            }
        }
    }


    queue<POS> q;
    int visited[50][50] = { 0, };
    for (int i = 0; i < M; i++) {
        q.push(pos[pick[i]]);
        visited[pos[pick[i]].y][pos[pick[i]].x] = 1;
    }

    while (!q.empty()) {
        POS cur = q.front();
        q.pop();

        if (map[cur.y][cur.x] == 0) {
            --empty_count;
        }
        if (empty_count == 0) {
            return cur.time;
        }
        POS next;
        next.time = cur.time + 1;
        for (int d = 0; d < 4; d++) {
            next.y = dy[d] + cur.y;
            next.x = dx[d] + cur.x;
            if (next.y < 0 || next.x < 0 || next.y >= N || next.x >= N)
                continue;
            if (visited[next.y][next.x] == 0 && map[next.y][next.x] != 1) {
                q.push(next);
                visited[next.y][next.x] = 1;
            }
        }
    }

    return 987654321;
}

void dfs(int last, int count, int pick[]) {
    if (count == M) {
        res = min(res, bfs(pick));
        return;
    }

    for (int i = last + 1; i < pos.size(); i++) {
        pick[count] = i;
        dfs(i, count + 1, pick);
    }
}


int main() {
    cin >> N >> M;
    POS temp;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> map[y][x];
            if(map[y][x]==2) {
                temp.y = y;
                temp.x = x;
                temp.time = 0;
                pos.push_back(temp);
            }
        }
    }
    res = 987654321;
    int pick[10] = { 0, };
    dfs(-1, 0, pick);

    if (res == 987654321) {
        cout << -1;
    }
    else {
        cout << res;
    }

    return 0;
}