#include <iostream>
#include <map>
#include <set>
#include "math.h"
#include <queue>
using namespace std;
#define p 31
#define q 1000000007

class Fax{
public:
    set<int> *dictionary;
    int *hashValues;
    char *characters;
    bool *isVisited;
    int *numOfWays;
    int totalWays = 0;
    queue<int> indexes;
    int stringLength;
    string str;
    Fax(string _str);
    ~Fax();
    void addWord(string newWord);
    int execute(int index);
    void firstSearch();

};