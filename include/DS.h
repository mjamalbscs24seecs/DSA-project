#ifndef DS_H
#define DS_H

#include <vector>
#include <utility>
#include <queue>
#include <stack>
using namespace std;

// ---------- Queue for BFS ----------
class BFSQueue {
private:
    queue<pair<int,int>> q;
public:
    void push(pair<int,int> val){ q.push(val); }
    pair<int,int> pop(){ 
        auto front = q.front(); 
        q.pop(); 
        return front; 
    }
    bool empty(){ return q.empty(); }
};

// ---------- Stack for DFS ----------
class DFSStack {
private:
    stack<pair<int,int>> s;
public:
    void push(pair<int,int> val){ s.push(val); }
    pair<int,int> pop(){ 
        auto top = s.top(); 
        s.pop(); 
        return top; 
    }
    bool empty(){ return s.empty(); }
};

// ---------- Min-Heap for A* ----------
struct Node {
    int x,y;
    int f; // f = g + h
    bool operator>(const Node &other) const { return f > other.f; }
};

class MinHeap {
private:
    priority_queue<Node, vector<Node>, greater<Node>> pq;
public:
    void push(Node n){ pq.push(n); }
    Node pop(){ 
        Node top = pq.top(); 
        pq.pop(); 
        return top; 
    }
    bool empty(){ return pq.empty(); }
};

#endif