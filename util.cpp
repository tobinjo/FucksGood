#include "util.h"
#include "mt19937.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <string>

using namespace std;

static bool gDebugMode;

void set_debug_mode(bool flag){
    
    gDebugMode = flag;
}

bool get_debug_mode(){
    
    if(gDebugMode==true) return true;
    else return false;
}

int eecs280_rand_int(int x){
    
    assert(x > 0);
    int bigRand = genrand_int31();
    int trueRand;
    
    if(bigRand < x)
        trueRand = bigRand;
    else
        trueRand = bigRand % x;
    
    if(get_debug_mode()){
        cout<< "DEBUG eecs280_rand_int(" << x << ") " << trueRand <<endl;
    }
    return trueRand;
}

double eecs280_rand_probability(){
    
    double random = genrand_real1();
    while(random > 1){
        random = genrand_real1();
    }
    
    if(get_debug_mode()){
        cout << "DEBUG eecs280_rand_probability() "<< random << endl;
    }
    return random;
}


