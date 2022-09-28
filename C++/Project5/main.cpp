#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "Fax.h"


int main(int argc, char* argv[]) {
    ifstream infile;
    infile.open(argv[1]);
    string line;
    infile >> line;
    Fax f(line);
    infile >> line;
    int dictSize = stoi(line);

    for(int i = 0; i < dictSize; i++){
        infile >> line;
        f.addWord(line);
    }


    f.firstSearch();
    infile.close();
    long result = f.totalWays;
    ofstream myfile;
    myfile.open(argv[2]);
    myfile << result;
    myfile.close();

    return 0;
}