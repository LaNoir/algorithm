#include <iostream>
#include <queue>
#include <string>
using namespace std;
 
 
int main() {
    int T;
    cin >> T;
    string s;
 
    int count = 0;
    while(count<T){
        count++;
        cin >> s;
 
    int a = 1, b = 1;
    for (int i = 0; i < s.size(); i++) {
        int tempa = a;
        int tempb = b;
 
        if (s[i] == 'L') {
            a = tempa;
            b = tempa + tempb;
        }
        else {
            a = tempa + tempb;
            b = tempb;
        }
 
         
    }
 
    cout << "#"<<count<<" " << a << " " << b << "\n";
    }
}