#include "Vertex.h"

Vertex::Vertex(int _vertexNum) {
    vertexNum = _vertexNum;
}
Vertex::Vertex(const Vertex& vertex) {
    low = vertex.low; index = vertex.index; vertexNum = vertex.vertexNum;
    onStack = vertex.onStack; 
    neighborList = vertex.neighborList;
}
Vertex& Vertex::operator=(const Vertex& vertex) {
    low = vertex.low; index = vertex.index; vertexNum = vertex.vertexNum;
    onStack = vertex.onStack; 
    neighborList = vertex.neighborList;
}
Vertex::Vertex(Vertex&& vertex) {
    low = vertex.low; index = vertex.index; vertexNum = vertex.vertexNum;
    onStack = vertex.onStack; 
    neighborList = move(vertex.neighborList);
    vertex.low = 0;vertex.index = 0;vertex.vertexNum = 0;
    vertex.onStack = false;
}
Vertex& Vertex::operator=(Vertex&& vertex) {
    low = vertex.low; index = vertex.index; vertexNum = vertex.vertexNum;
    onStack = vertex.onStack;
    neighborList = move(vertex.neighborList);
    vertex.low = 0;vertex.index = 0;vertex.vertexNum = 0;
    vertex.onStack = false;
}
void Vertex::push(int& _vertexNum) {
    neighborList.push_front(_vertexNum);
}




