#include "generator.hpp"
#include <vector>
#include <random>
#include <chrono>

using namespace std;

vector<int> biv::generator::generate(int N){
    vector<int> a;
    mt19937 mt(time(nullptr));
    for(;N-- > 0;){
        int p = (mt()%10); int q = (mt()%10);
        a.push_back(pow(2,p)*pow(3,q));
    }
    return a;
}