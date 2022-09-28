#include "Fax.h"

Fax::Fax(string _str) {
    stringLength = _str.length();
    str = _str;
    dictionary = new set<int>;
    hashValues = new int[stringLength];
    characters = new char[stringLength];
    isVisited = new bool[stringLength];
    numOfWays = new int[stringLength];
    long long hashValue = 0;
    int index = 0;
    long long p_pow = 1;
    for(string::reverse_iterator rit = str.rbegin(); rit != str.rend(); rit++){
        unsigned long long coef = (*rit - 'a' + 1)*p_pow % q;
        hashValue = (hashValue + coef)%q;
        p_pow = (p_pow*p)%q;
        *(characters+index) = *rit;
        *(isVisited+index) = false;
        *(numOfWays+index) = 0;
        *(hashValues+index) = hashValue;
        index++;
    }
}
Fax::~Fax() {
    delete dictionary;
    delete []hashValues;
    delete []characters;
    delete []isVisited;
    delete []numOfWays;
}
void Fax::addWord(string newWord) {
    long long hashValue = 0;
    long long p_pow = 1;

    for(string::reverse_iterator rit = newWord.rbegin(); rit != newWord.rend(); rit++){
        unsigned long long coef = (*rit - 'a' + 1)*p_pow %q;
        hashValue = (hashValue + coef) % q;
        p_pow = (p_pow * p) % q;
    }
    dictionary->insert(hashValue);
}
int Fax::execute(int index) {
    if(index >= stringLength-1){
        totalWays++;
        return 1;
    }

    *(isVisited+index) = true;
    int currentHash = 0;
    long long p_pow = 1;
    for(int i = index+1; i < stringLength; i++){
        unsigned long long coef = (*(characters+i) - 'a' + 1)*p_pow % q;
        currentHash = (currentHash + coef) % q;
        p_pow = (p*p_pow)%q;
        if(!dictionary->count(currentHash)){
            continue;
        }
        else if(*(isVisited+i)){
            *(numOfWays+index) = (*(numOfWays+index)+ *(numOfWays+i)) % q;
            totalWays = (totalWays + *(numOfWays+i)) % q;
            continue;
        }
        else if(dictionary->count(currentHash)){
            unsigned long long inc = execute(i) % q;
            *(numOfWays+index) = (*(numOfWays+index) + inc) % q;
        }
    }
    return *(numOfWays+index);
}
void Fax::firstSearch() {
    for(int i = 0; i < stringLength; i++){
        int currentHash = *(hashValues+i);
        if(dictionary->count(currentHash)){
            indexes.push(i);
        }
    }
    while(!indexes.empty()){
        int currIndex = indexes.front();
        indexes.pop();
        execute(currIndex);
    }
}