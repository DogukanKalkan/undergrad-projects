#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <queue>
#include "Graph.h"
using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char* argv[]) {
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> firstLine;
    split1(line, firstLine);

    int rows = stoi(firstLine[0]);
    int columns = stoi(firstLine[1]);

    Graph g(rows, columns);

    for(int i = 0; i < rows; i++){
        getline(infile, line);
        vector<string> words;
        split1(line, words);
        for(int j = 0; j < columns; j++){
            *(*(g.vertices+i)+j) = stoi(words[j]);
            *(*(g.truthTable+i)+j) = false;
        }
    }
    getline(infile, line);
    getline(infile,line);
    vector<string> coordinates;
    split1(line, coordinates);

    ofstream myfile;
    myfile.open(argv[2]);
    myfile << g.executePrim(stoi(coordinates[0]), stoi(coordinates[1]), stoi(coordinates[2]), stoi(coordinates[3]));
    myfile.close();
    return 0;
}