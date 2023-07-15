#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> graph[20001];

bool cmp(int a, int b){
    return a>b;
}

void set_distance(vector<int>& distance, int n){
    vector<bool> visited(n+1, false);
    queue<int> q;
    
    int cnode = 1;
    int nnode;
    q.push(cnode);
    visited[cnode] = true;
    
    while(!q.empty()){
        cnode = q.front();
        q.pop();
        
        for(int i=0; i<graph[cnode].size(); i++){
            nnode = graph[cnode][i];
            if(visited[nnode]==true) continue;
            visited[nnode] = true;
            distance[nnode] = distance[cnode]+1;
            q.push(nnode);
        }
    }
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0;
    int len_edge = edge.size();
    
    // init
    for(int i=0; i<len_edge; i++){
        int from = edge[i][0];
        int to = edge[i][1];
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
    
    vector<int> distance(n+1, 0);
    set_distance(distance, n);
    
    sort(distance.begin(), distance.end(), cmp);
    int max_val = distance[0];
    answer=1;
    for(int i=1; i<n; i++){
        if(max_val == distance[i])
            answer++;
    }
    
    return answer;
}