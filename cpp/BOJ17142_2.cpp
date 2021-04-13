#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N,M;
int board[50][50];
struct POS{
    int y,x, time;
};
int res = 2100000000;
vector<POS> virus;
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};
int bfs(int pick[]){
    queue<POS> q;

    bool visited[50][50] = {false,};

    for(int i =0; i<M; i++){
        q.push(virus[pick[i]]);
        visited[virus[pick[i]].y][virus[pick[i]].x] = true;
    }

    int empty_space = 0;

    for(int y = 0 ;y<N; y++){
        for(int x = 0; x<N; x++){
            if(board[y][x] == 0){
                empty_space++;
            }
        }
    }

    while(!q.empty()){
        POS cur = q.front();
        q.pop();
        if(board[cur.y][cur.x] == 0){
            empty_space--;
        }
        if(empty_space == 0){
            return cur.time;
        }

        for(int d = 0; d<4; d++){
            POS next;
            next.x = cur.x+dx[d];
            next.y = cur.y+dy[d];
            next.time = cur.time+1;

            if(next.x<0||next.y<0||next.x>=N|| next.y>=N){
                continue;
            }
            if(visited[next.y][next.x]==true || board[next.y][next.x] == 1){
                continue;
            }
            q.push(next);
            visited[next.y][next.x]=true;
        }

    }

    return 2100000000;
}

void dfs(int last, int count , int pick[]){
    if(count == M){
        res = min(res, bfs(pick));
        return;
    }

    for(int i = last+1; i<virus.size(); i++){
        pick[count] = i;
        dfs(i,count+1,pick);
    }
}

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    for(int y = 0 ;y<N; y++){
        for(int x = 0; x<N; x++){
            cin>>board[y][x];
            if(board[y][x] == 2){
                virus.push_back({y,x,0});
            }
        }
    }

    int pick[10] = {0,};

    dfs(-1, 0, pick);

    if(res == 2100000000){
        res = -1;
    }
    cout << res;
    return 0;
}