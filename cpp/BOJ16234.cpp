#include <iostream>
#include <queue>
using namespace std;

int N,L,R;
int board[50][50];
int status[50][50];
int counts[2501];
int sum[2501];
int res = 0;

struct POS{
    int y,x;
};

int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};

void create_area(int sy, int sx, int index){
    queue<POS> q;
    bool visited[50][50]={false,};
    q.push({sy,sx});
    visited[sy][sx] = true;
   
    while(!q.empty()){
        POS cur = q.front();
        q.pop();
        status[cur.y][cur.x] = index;
        ++counts[index];
		sum[index] += board[cur.y][cur.x];
        POS next;
        for(int d = 0; d<4; d++){
            next.x = cur.x+dx[d];
            next.y = cur.y+dy[d];

            if(next.x<0 || next.y<0 || next.x>=N || next.y>=N){
                continue;
            }
            int cha = abs(board[next.y][next.x] - board[cur.y][cur.x]);
            if(visited[next.y][next.x] == false && cha<= R && cha>=L){
                visited[next.y][next.x] = true;
                q.push(next);
            }
        }

    }

}

int main(){
    cin>>N>>L>>R;
    for(int y = 0; y<N; y++){
        for(int x=0; x<N; x++){
            cin>>board[y][x];
        }
    }

    bool is_update = true;
    while(is_update){

    for(int y = 0; y<N; y++){
            for(int x=0; x<N; x++){
            status[y][x] = 0;
        }
    }

    for(int i = 0; i< 2501; i++){
        sum[i] = 0;
        counts[i] = 0;
    }

    is_update = false;
    int index = 0;
        for(int y = 0; y<N; y++){
            for(int x=0; x<N; x++){
                if(status[y][x] == 0){
                    ++index;
                    create_area(y,x,index);
                }
            }
        }

        for(int y = 0; y<N; y++){
            for(int x=0; x<N; x++){
                int cur = status[y][x];
                int avg = sum[cur]/counts[cur];

                if(board[y][x] != avg){
                    board[y][x] = avg;
                    is_update = true;
                }

            }
        }
        if( is_update){
            res++;
        }
    }
    cout << res;
    return 0;
}