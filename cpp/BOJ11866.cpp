#include <iostream>
#include <queue>
using namespace std;


int N,K;

int main(){
    queue<int> q;
    cin>>N>>K;
    cout << "<";
    for(int i = 0; i<N; i++){
        q.push(i+1);
    }
    int count = 1;
    while(!q.empty()){
        if(count % K ==0){
            if(q.size()>=2)
                cout<< q.front()<<", ";
            else
                cout <<q.front();
            q.pop();
        } 
        else{
            q.push(q.front());
            q.pop();
        }
        count ++;
    }
    cout << ">";
}