#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

static const int B = 5;
//using mat = vector<vector<int>>;

typedef struct {
    int* up;
    int* left;
} FronteraNW;

typedef struct {
    int* down;
    int* right;
} FronteraSE;


FronteraNW init_fr(int n){
    FronteraNW f; 
    f.up = (int*)malloc(n * sizeof(int));
    f.left = (int*)malloc(n * sizeof(int));
    return f;
    }

FronteraSE init_fr2(int n){
    FronteraSE f; 
    f.down = (int*)malloc(n * sizeof(int));
    f.right = (int*)malloc(n * sizeof(int));
    return f;
    }

vector<vector<FronteraNW>> init_mat(int n){
    vector<vector<FronteraNW>> M(n+1, vector<FronteraNW>(n+1)); 
    for(int i=0;i<n/B;i++){
        for (int j= 0; j < n/B; j++)
        {
            M[i][j].up = (int*)malloc((B+1) *sizeof(int));
            M[i][j].left = (int*)malloc((B+1) *sizeof(int));
        }
    }
    for(int i=0;i<B+1;i++){
        for (int j= 0; j < n/B; j++)
        {
            M[j][0].up[i] = j*B+i;
            M[j][0].left[i] = j*B+i;
            M[0][j].up[i] = j*B+i;
            M[0][j].left[i] = j*B+i;
        }
    }
    return M;
}


FronteraSE algoritmo(string x, string y, int k, int l, FronteraNW f_i){

    int n = x.length();
    vector<vector<int>> m(B+1, vector<int>(B+1));
    FronteraSE f_f = init_fr2(B+1);

    for (int i = 0; i < B+1; i++)
    {
        m[0][i] = f_i.left[i];
        m[i][0] = f_i.up[i] ;
    }

    for(int i=1; i<B+1;i++){
        for(int j=1; j<B+1;j++){
            int up = 1 + m[i-1][j];
            int left = 1 + m[i][j-1];
            int diag = (x[k*B+i] != y[l*B+j]) + m[i-1][j-1];
            m[i][j] = min(min(up,left),diag);
        }
    }
    //cout << m << endl;

    for (int i = 0; i < B+1; i++)
    {
        f_f.right[i] = m[B][i];
        f_f.down[i] = m[i][B] ;
    }
    
    return f_f;
}

int distance_3(string x, string y){
    int n = x.length();
    vector<vector<FronteraNW>> M = init_mat(n+1);

    int res = n;
    FronteraNW f_0 = M[0][0];
    for (int l = 0; l < n/B; l++){
        for (int k = 0; k < n/B; k++){
            FronteraSE f = algoritmo(x,y,k,l, M[l][k]);
            if (k<n/B-1) M[l][k+1].left = f.right;
            if (l<n/B-1) M[l+1][k].up = f.down;
            if (k==n/B-1 && l==n/B-1) res = f.right[B];
        }
    }
    return res;
    
}


void destroy_mat(vector<vector<FronteraNW>> M, int n){
    for(int i=0;i<B+1;i++){
        for (int j= 0; j < n/B; j++)
        {
            delete M[i][j].up;
            delete M[i][j].left;
        }
    }
}


//int main(){
//    int n=15;
//    cout << distance_3("bananaaaaaeeeee", "ananasaaaaeeeee") << endl;
//    //cout << distance_3("bananaaaaaeeeee", "ananasaaaaeeeee") << endl;
//    return 0;
//}
