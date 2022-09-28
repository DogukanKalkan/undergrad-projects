#include "Graph.h"

Graph::Graph(int _rows, int _columns) {
    rows = _rows;
    columns = _columns;
    vertices = new int*[rows];
    truthTable = new bool*[rows];
    for(int i = 0; i < rows; i++){
        vertices[i] = new int[columns];
        truthTable[i] = new bool[columns];
    }
}
Graph::~Graph() {
    for(int i = 0; i < rows; i++){
        delete []vertices[i];
        delete []truthTable[i];
    }
    delete []vertices;
    delete []truthTable;
}

int Graph::executePrim(const int& x1, const int& y1, const int& x2, const int& y2) {
    int ladderHeight = 0;
    priority_queue<Element> *pQueue = new priority_queue<Element>;
    pQueue->push(Element(x1-1,y1-1,0));
    *(*(vertices+x1)+y1) = true;

    while(!*(*(truthTable+x2-1)+y2-1)){
        int x = pQueue->top().x;
        int y = pQueue->top().y;
        int diff = pQueue->top().heightDiff;
        pQueue->pop();
        if(diff > ladderHeight) ladderHeight = diff;
        *(*(truthTable+x)+y) = true;
        int currentHeight = *(*(vertices+x)+y);
        if(x-1 >= 0 && !*(*(truthTable+x-1)+y)){
            int nextHeight = *(*(vertices+x-1)+y);
            int nextDiff = abs(currentHeight-nextHeight);
            pQueue->push(Element(x-1,y,nextDiff));
        }
        if(x+1 < rows && !*(*(truthTable+x+1)+y)){
            int nextHeight = *(*(vertices+x+1)+y);
            int nextDiff = abs(currentHeight-nextHeight);
            pQueue->push(Element(x+1,y,nextDiff));
        }
        if(y-1 >= 0 && !*(*(truthTable+x)+y-1)){
            int nextHeight = *(*(vertices+x)+y-1);
            int nextDiff = abs(currentHeight-nextHeight);
            pQueue->push(Element(x,y-1,nextDiff));
        }
        if(y+1 < columns && !*(*(truthTable+x)+y+1)){
            int nextHeight = *(*(vertices+x)+y+1);
            int nextDiff = abs(currentHeight-nextHeight);
            pQueue->push(Element(x,y+1,nextDiff));
        }
    }
    delete pQueue;
    return ladderHeight;
}