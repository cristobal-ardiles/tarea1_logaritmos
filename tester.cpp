#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include "algoritmo_1.cpp"
#include "algoritmo_2.cpp"
#include <fstream>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::chrono::high_resolution_clock;


char* make_str(int len){
    char* s = (char*)malloc(len +1);
    for (int i = 0; i < len; i++)
    {
        s[i] = 'a' + rand()%26;
    }
    s[len] = '\0';
    return s;
}
void test(string filename, int reps, int (*fun)(string, string)){
    ofstream arch(filename);
    arch << "tamaño,distancia,tiempo " << endl;
    char *s;
    char *t;
    for (int r = 1; r < reps+1; r++)
    {
        int len = 8;
        s = make_str(len);
        t = make_str(len);
        for (int i = 3; i < 16; i++)
        {
            s = make_str(len);
            t = make_str(len);
            auto t0 = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
            int dist = fun(s,t);
            auto tf = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
            int dt = (tf-t0);
            cout << "Tamanio: " << len << endl; 
            cout << "Distancia: " << dist << endl; 
            cout << "Tiempo: " << dt << endl;
            arch << len << "," << dist << "," << dt << endl;
            len = 2*len;
        }
    }
    arch.close();
    delete s;
    delete t;

}

int main(){
    int reps = 4;
    test("test1.txt", 4, distance_1);
    test("test2.txt", 4, distance_2);
    return 0;
}