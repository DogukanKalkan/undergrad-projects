#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <iterator>
#include "Event.h"
#include <time.h>
#include "EventExecuter.h"
#include <iomanip>

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
    if (argc != 3) {
        cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
        return 1;
    }

    Event e(Event::Type ::ARRIVAL,Passenger(0,0,0,0,false,false),0);



    ifstream infile(argv[1]);
    string line;
    getline(infile,line);
    vector<string> firstLine;
    split1(line, firstLine);
    int nOfPassengers = stoi(firstLine[0]);
    int nOfLug = stoi(firstLine[1]);
    int nOfSec = stoi(firstLine[2]);

    cout << nOfPassengers << " " << nOfLug  << " " << nOfSec << endl;

    priority_queue<Event> eventQueue = priority_queue<Event>();

    for(int i = 0; i < nOfPassengers; i++){
    	getline(infile, line);
    	vector<string> words;
    	split1(line, words);
    	int arrTime = stoi(words[0]);
    	int depTime = stoi(words[1]);
    	int lugTime = stoi(words[2]);
    	int secTime = stoi(words[3]);
    	bool isVip = words[4] == "V" ? true : false; // words[4]ü popluyor sanırsam poplamıyorsa sıkıntı
    	bool hasLug = words[5] == "L" ? true : false;
    	Passenger p(arrTime, depTime, lugTime, secTime, isVip, hasLug);
    	Event e(Event::Type::ARRIVAL, p, arrTime);
    	eventQueue.push(e);
    }

    ofstream myfile;
    myfile.open(argv[2]);

    for(int i = 1; i < 9; i++) {
        EventExecuter eventExecuter(nOfLug, nOfSec);
        eventExecuter.eventQueue = eventQueue;

        while (!eventExecuter.eventQueue.empty()) {
            eventExecuter.execute(i);
        }
        int lateNum = eventExecuter.numOfLatePassengers;
        cout << fixed << setprecision(2) << eventExecuter.totalTime/(double)nOfPassengers << " " << lateNum << endl;

    }
    myfile.close();

    return 0;

}