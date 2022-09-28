#include <iostream>
#include "Vertex.h"
#include <vector>
#include <stack>

class Graph{
public:
    int numOfBanksToBeCracked = 0;
    vector<int> verticesToBeCracked;
    vector<Vertex> srcToSink;
    vector<Vertex> sinkToSrc;
    int counter = 1;
    stack<Vertex> vertexStack;
    Graph(int numOfVertices);
    void addNeighbor(int vertexNum, int neighborVertexNum);
    void scc();
    void crack();
private:
    int scc(Vertex& v, bool truthTable[]);

};
