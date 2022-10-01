#include <iostream>
#include <chrono>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

int not_equal(string s, string t, int i, int j){
    return s[i] != t[j];
}

int distance(string x, string y){

    int n = x.length();
    int diag;
    int* M = new int[n+1];

    for(int i=0;i<n+1;i++){
        M[i] = i;
    }

    for(int i=1; i<n+1;i++){
        for(int j=0; j<n+1;j++){    
            if(j==0){
                diag = M[j];
                M[j] = i; 
            }
            else{
                int up = 1 + M[j];
                int left = 1 + M[j-1];
                int curr_diag = not_equal(x,y,i,j) + diag;
                int partial_min = min(up,left);

                diag = M[j];
                M[j] = partial_min < curr_diag ? partial_min : curr_diag;
            }
        }
    }
    int res = M[n];
    delete M;
    return res;
}

int main(){
    string s;
    string t;
    cin >> s;
    cin >> t;

    auto t0 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int dist = distance(s,t);
    auto tf = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << dist << endl; 
    cout << tf-t0 << endl;
    return 0;
}