#include <bits/stdc++.h>
using namespace std;
#define int long long

class maxFlow{
    private:
        int n;
        vector<vector<pair<int,int>>> adj;
        int s;
        int t;
        int maxflow = 0;
    public:
        maxFlow(int no, vector<vector<pair<int,int>>> edges, int start, int dest){
            adj = edges;
            n = no;
            s = start;
            t = dest;
        }
        vector<int> shortestPath();
        void push(vector<int> path);
        int getCapacity(int a, int b);
        void changeEdge(int a, int b, int w);
        int solve();
};

vector<int> maxFlow :: shortestPath(){
    queue<int> BFS;
    vector<int> visited(n, -1);
    BFS.push(s);
    visited[s] = 1;
    while(!BFS.empty()){
        int curr = BFS.front();
        BFS.pop();
        //cout << "current node : " << curr << endl;
        for(auto it : adj[curr]){
            int k = it.first;
            if(visited[k] == -1){
                visited[k] = curr;
                BFS.push(k);
            }
        }
    }
    int it = t;
    vector<int> path;
    if(visited[t] == -1) return path;
    while(it != s){
        path.push_back(it);
        it = visited[it];
    }
    path.push_back(s);
    reverse(path.begin(), path.end());
    return path;
}

int maxFlow :: getCapacity(int a, int b){
    for(auto it : adj[a]){
        if(it.first == b) return it.second;
    }
    return 0;
}

void maxFlow :: push(vector<int> path){
    //cout << "entered" << endl;
    int capacity = INT_MAX;
    for(int i = 0; i < path.size() - 1; i++){
        capacity = min(capacity, getCapacity(path[i], path[i + 1]));
    }
    //cout << "capacity" << capacity << endl;
    maxflow += capacity;
    for(int i = 0; i < path.size() - 1; i++){
        changeEdge(path[i], path[i + 1], -capacity);
        changeEdge(path[i + 1], path[i], capacity);
    }
}

void maxFlow :: changeEdge(int a, int b, int w){
    for(auto it = adj[a].begin(); it != adj[a].end(); ++it){
        if((*it).first == b) {
            ((*it).second) += w;
            if((*it).second == 0){
                adj[a].erase(it);
            }
            return;
        }
    }
    adj[a].push_back(make_pair(b, w));
}

int maxFlow :: solve(){
    vector<int> path = {0};
    while(1){
        //cout << "Finding path" << endl;
        path = shortestPath();
        if(path.empty()) break;
        push(path);
        //cout << "Push Successful" << endl;
    }
    return maxflow;
}

int32_t main(){
    // s-3>a-2>t;
    int n;
    cin >> n;
    vector<vector<pair<int,int>>> adj(n);
    int m;
    cin >> m;
    int l, r, c;
    for(int i = 0; i < m; i++){
        cin >> l >> r >> c;
        adj[l].push_back(make_pair(r, c));
    }
    maxFlow* mf = new maxFlow(n, adj, 0, n - 1);
    cout << "maxflow = "<< mf->solve() << endl;
}
