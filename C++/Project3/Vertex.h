#include <iostream>
#include <forward_list>
using namespace std;

class Vertex{
public:
    bool isToBeCracked = false;
    int low = -1;
    int index = -1;
    int vertexNum = 0;
    bool onStack = false;
    forward_list<int> neighborList;
    Vertex(int _vertexNum=0);
    Vertex(const Vertex& vertex);
    Vertex& operator=(const Vertex& vertex);
    Vertex(Vertex&& vertex);
    Vertex& operator=(Vertex&& vertex);
    void push(int& _vertexNum);
};

