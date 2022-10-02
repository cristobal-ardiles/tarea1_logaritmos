#include <iostream>
#include <chrono>
#include <vector>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

int distance_2(string x, string y){

    int n = x.length();
    int diag;
    vector<int> M(n+1);

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
                int curr_diag = (x[i] != y[j]) + diag;
                diag = M[j];
                M[j] = min(curr_diag, min(up,left));
            }
        }
    }
    int res = M[n];
    return res;
}