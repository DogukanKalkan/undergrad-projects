#include "Graph.h"
Graph::Graph(int numOfVertices) {
    sinkToSrc = vector<Vertex>(numOfVertices);
    srcToSink = vector<Vertex>(numOfVertices);
    for(int i = 0; i < numOfVertices; i++){
        sinkToSrc[i].vertexNum = i+1;
        srcToSink[i].vertexNum = i+1;
    }
}
void Graph::addNeighbor(int vertexNum, int neighborVertexNum) {
    if(vertexNum == neighborVertexNum) return;

    srcToSink[vertexNum-1].push(neighborVertexNum);
    sinkToSrc[neighborVertexNum-1].push(vertexNum);
}

void Graph::scc() {
    bool truthTable[sinkToSrc.size()];
    for(vector<Vertex>::iterator iter = srcToSink.begin(); iter != srcToSink.end(); iter++){
        int currNum = (*iter).vertexNum;
        if((*iter).low == (*iter).index && (*iter).neighborList.empty() && sinkToSrc[currNum-1].neighborList.empty()){
            verticesToBeCracked.push_back(currNum);
            numOfBanksToBeCracked++;
            continue;
        }
        if(!truthTable[(*iter).vertexNum-1]){
            scc((*iter), truthTable);
        }
    }
}

int Graph::scc(Vertex &v, bool truthTable[]) {
    int n = -1;
    truthTable[v.vertexNum-1] = true;
    v.index = v.low = counter;
    counter++;
    vertexStack.push(v);
    v.onStack = true;
    for(auto it = v.neighborList.begin(); it != v.neighborList.end(); it++){

        Vertex& child = srcToSink[(*it)-1];
        if(!truthTable[(*it)-1]){
            n = scc(child, truthTable);
            v.low = min(v.low, child.low);
        }
        else if(child.onStack){
            v.low = min(v.low, child.index);
        }
        if(v.low != v.index){ 
            int i = vertexStack.top().vertexNum;
            vertexStack.pop();
            srcToSink[i-1].onStack = false;
            if(n >= 0){
                srcToSink[i-1].neighborList.clear();
            }

            return i;
        }
    }
    int i = vertexStack.top().vertexNum;
    for(auto it = sinkToSrc[i-1].neighborList.begin(); it != sinkToSrc[i-1].neighborList.end(); ){
        if(srcToSink[(*it)-1].low == srcToSink[i-1].low){
            sinkToSrc[i-1].neighborList.remove((*it++));
        }
        else{
            it++;
        }
    }

    srcToSink[i-1].onStack = false;
    vertexStack.pop();
    return -1;
}

void Graph::crack() {
    for(vector<Vertex>::iterator it = sinkToSrc.begin(); it != sinkToSrc.end(); it++){
        int currNum = (*it).vertexNum;
        if(!srcToSink[currNum-1].neighborList.empty() && sinkToSrc[currNum-1].neighborList.empty()){
            numOfBanksToBeCracked++;
            verticesToBeCracked.push_back(currNum);
        }

    }
}