#include <queue>
#include <iostream>
using namespace std;

struct Element{
    int x;
    int y;
    int heightDiff;
    Element():x(0),y(0),heightDiff(0){}
    Element(int _x, int _y, int _heightDiff):x(_x), y(_y), heightDiff(_heightDiff){};
    bool operator <(const Element& e)const{
        return heightDiff > e.heightDiff;
    }
};

class Graph{
public:
    int rows;
    int columns;
    int** vertices;
    bool** truthTable;
    Graph(int _rows, int _columns);
    ~Graph();
    int executePrim(const int& x1, const int& y1, const int& x2, const int& y2);
};
