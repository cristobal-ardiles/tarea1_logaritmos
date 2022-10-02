#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

int distance_1(string x, string y){
    int n = x.length();
    vector<vector<int>> M(n+1, vector<int>(n+1));
    //int M[32768][32768];
    for(int i=0;i<n+1;i++){
        M[i][0] = i;
        M[0][i] = i;
    }

    for(int i=1; i<n+1;i++){
        for(int j=1; j<n+1;j++){
            int up = 1 + M[i-1][j];
            int left = 1 + M[i][j-1];
            int diag = (x[i] != y[j]) + M[i-1][j-1];
            M[i][j] = min(min(up,left),diag);
        }
    }
    int res = M[n][n];
    return res;
}

