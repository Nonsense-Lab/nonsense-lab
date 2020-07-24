#include <string>
#include <iostream>
#include <random>
#include <fstream>
#include <map>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;

#define FALSE false
#define TRUE true

void init(map<char, int>& MapWaitingForInitialization) {
    int ctr = 0;
    for (char a = 'A'; a < 'Z'; a++) {
        MapWaitingForInitialization[a] = ctr;
        ctr++;
    }
    return;
}
