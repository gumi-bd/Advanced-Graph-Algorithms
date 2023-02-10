#include <bits/stdc++.h>
using namespace std;
#define int long long

class Node{
    private:
        int index;
        int h = 0;
        int ex = 0;
        vector<pair<int, int>> edges;
    public:
        Node(int i){
            index = i;
        }
        int getIndex(){
            return index;
        }
        int getHeight(){
            return h;
        }
        int getExcess(){
            return ex;
        }
        vector<pair<int, int>> getEdges(){
            return edges;
        }
        void addHeight(int he){
            h += he;
        }
        void addExcess(int e){
            ex += e;
        }
        void addEdge(int node, int cap){
            edges.push_back(make_pair(node, cap));
        }
        void removeEdge(int node){
            for(auto it = edges.begin(); it != edges.end(); ++it){
                if((*it).first == node) {
                    edges.erase(it);
                    return;
                }
            }
        }
        void clearEdges(){
            edges.clear();
        }
};

class CompareHeight{
    public:
    bool operator()(Node* n1, Node* n2){
    if(n1->getHeight() < n2->getHeight()) return true;
        return false;
    }
};

class maxFlow{
    private:
        vector<Node*> nodes;
        priority_queue<Node*, vector<Node*>, CompareHeight> nodeHeights;
        int s;
        int t;
    public:
        maxFlow(vector<Node*> n, int start, int dest){
            nodes = n;
            s = start;
            t = dest;
        }
        void initPref();
        void push(int a, int b);
        void relabel(int a);
        int solve();
};

void maxFlow::initPref(){
    for(int i = 0; i < nodes.size(); i++){
        if(i == s) nodes[i]->addHeight(nodes.size());
        else nodes[i]->addHeight(0);
        if(i != s && i != t) nodeHeights.push(nodes[i]);
    }
    vector<pair<int,int>> v = nodes[s]->getEdges();
    for(int i = 0; i < v.size(); i++){
        int index = v[i].first;
        int cap = v[i].second;
        nodes[index]->addEdge(s, cap);
        nodes[index]->addExcess(cap);
        nodes[s]->addExcess(-cap);
    }
    nodes[s]->clearEdges();
}

void maxFlow::push(int a, int b){
    cout << "Pushing from " << a << " to " << b << endl;
    vector<pair<int,int>> v = nodes[a]->getEdges();
    int cap = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i].first == b) cap = v[i].second;
    }
    int f = min(nodes[a]->getExcess(), cap);
    nodes[a]->removeEdge(b);
    cap -= f;
    int cap2 = 0;
    v = nodes[b]->getEdges();
    for(int i = 0; i < v.size(); i++){
        if(v[i].first == a) cap2 = v[i].second;
    }
    nodes[b]->removeEdge(a);
    cap2 += f;
    nodes[b]->addExcess(f);
    nodes[a]->addExcess(-f);
    if(cap > 0) nodes[a]->addEdge(b, cap);
    if(cap2 > 0) nodes[b]->addEdge(a, cap2);
    if(nodes[a]->getExcess() > 0) nodeHeights.push(nodes[a]);
    if(nodes[b]->getExcess() > 0 && b != t) nodeHeights.push(nodes[b]);
}

void maxFlow::relabel(int a){
    cout << "Relabeling node " << a << endl;
    nodes[a]->addHeight(1);
    nodeHeights.push(nodes[a]);
}

int maxFlow::solve(){
    initPref();
    while(!nodeHeights.empty()){
        Node* curr = nodeHeights.top();
        nodeHeights.pop();
        if(curr->getExcess() == 0) continue;
        vector<pair<int,int>> v = curr->getEdges();
        int i;
        for(i = 0; i < v.size(); i++){
            if(nodes[v[i].first]->getHeight() < curr->getHeight()){
                push(curr->getIndex(), nodes[v[i].first]->getIndex());
                break;
            }
        }
        if(i == v.size()){
            relabel(curr->getIndex());
        }
    }
    return -nodes[s]->getExcess();
}

int32_t main(){
    // s-3>a-2>t;
    int n;
    cin >> n;
    vector<Node*> nodes;
    for(int i = 0; i < n; i++){
        Node* curr = new Node(i);
        nodes.push_back(curr);
    }
    int m;
    cin >> m;
    int l, r, c;
    for(int i = 0; i < m; i++){
        cin >> l >> r >> c;
        nodes[l - 1]->addEdge(r - 1, c);
    }
    maxFlow* mf = new maxFlow(nodes, 0, n-1);
    cout << "maxflow = "<< mf->solve() << endl;
}