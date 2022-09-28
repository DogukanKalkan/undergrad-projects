#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "Graph.h"


template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}



int main(int argc, char* argv[]) {
    if(argc != 3){
        cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    int numOfBanks = stoi(line);

    Graph g(numOfBanks);

    for(int i = 1; i <= numOfBanks; i++){
        getline(infile, line);
        vector<string> words;
        split1(line, words);

        int j = stoi(words[0]);

        for(int k = 1; k <= j; k++){
            int neighbor = stoi(words[k]);
            g.addNeighbor(i, neighbor);
        }

    }

    g.scc();
    g.crack();
    ofstream myfile;
    myfile.open(argv[2]);
    myfile << g.numOfBanksToBeCracked << " ";
    
    for(vector<int>::iterator it = g.verticesToBeCracked.begin(); it != g.verticesToBeCracked.end(); it++){
        myfile << (*it) << " ";
    }
    

    myfile.close();

    return 0;
}