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

int** create_square_matrix(int dim){
    int** M = new int*[dim];
    for(int i=0; i<dim; i++){
        M[i] = new int[dim];
    }
    return M;
}

void destroy_matrix(int** ptr, int dim){
    for(int i=0; i<dim; i++){
        delete ptr[i];
    }
    delete ptr;
}

int distance(string x, string y){

    int n = x.length();
    int **M = create_square_matrix(n+1);
    for(int i=0;i<n+1;i++){
        M[i][0] = i;
        M[0][i] = i;
    }

    for(int i=1; i<n+1;i++){
        for(int j=1; j<n+1;j++){
            int up = 1 + M[i-1][j];
            int left = 1 + M[i][j-1];
            int diag = not_equal(x,y,i,j) + M[i-1][j-1];
            int partial_min = min(up,left);
            M[i][j] = partial_min < diag ? partial_min : diag;
        }
    }
    int res = M[n][n];
    destroy_matrix(M,n+1);
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