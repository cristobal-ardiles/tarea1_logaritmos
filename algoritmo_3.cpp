#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

static const int B = 4;
//using mat = vector<vector<int>>;

typedef struct {
    int* up;
    int* lft;
} Frontera;


int distance_3(string x, string y){
    int n = x.length();
    vector<vector<Frontera>> M = init_mat(n+1);
}

int algoritmo(string x, string y, int b, int k, int l, vector<vector<Frontera>> *M){

    int n = x.length();
    vector<vector<int>> m(B+1, vector<int>(B+1));

    for(int i=1; i<b;i++){
        for(int j=1; j<b;j++){
            int up = 1 + m[i-1][j];
            int left = 1 + m[i][j-1];
            int diag = (x[k*b+i] != y[l*b+j]) + m[i-1][j-1];
            m[i][j] = min(min(up,left),diag);
        }
    }
    int res = m[n][n];
    return res;
}

vector<vector<Frontera>> init_mat(int n){
    vector<vector<Frontera>> M(n+1, vector<Frontera>(n+1)); 
    for(int i=0;i<n/B;i++){
        for (int j= 0; j < n/B; j++)
        {
            M[i][j].up = (int*)malloc(B * sizeof(int));
            M[i][j].lft = (int*)malloc(B * sizeof(int));
        }
    }
    for(int i=0;i<B;i++){
        for (int j= 0; j < n/B; j++)
        {
            M[j][0].up[i] = j*B+i;
            M[j][0].lft[i] = j*B+i;
            M[0][j].up[i] = j*B+i;
            M[0][j].lft[i] = j*B+i;
        }
    }
}

void destroy_mat(vector<vector<Frontera>> M, int n){
    for(int i=0;i<B;i++){
        for (int j= 0; j < n/B; j++)
        {
            delete M[i][j].up;
            delete M[i][j].lft;
        }
    }
}

int distance_1(string x, string y, int b){
    int n = x.length();
    vector<vector<int**>> M(n+1, vector<int**>(n+1));

    

    //m=M[k][l];
    for(int k=1; k<B;k++){
        for(int j=1; j<n+1;j++){
            int up = 1 + M[i-1][j];
            int left = 1 + M[i][j-1];
            int diag = (x[i] != y[j]) + M[i-1][j-1];
            M[i][j] = min(min(up,left),diag);
        }
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

int main(){
    int n=10;
    vector<vector<int**>> M(n+1, vector<int**>(n+1));
    init_mat(M, n+1);
    return 0;
}
