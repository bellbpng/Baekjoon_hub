#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> map[100001];

void update_distance(vector<int>& min_distance, int cnode){
    int n = min_distance.size();
    vector<bool> visited(n+1, false);
    
    min_distance[cnode] = 0;
    visited[cnode]=true;
    
    queue<int> q;
    q.push(cnode);
    while(!q.empty()){
        cnode = q.front();
        q.pop();
        
        for(int i=0; i<map[cnode].size(); i++){
            int nnode = map[cnode][i];
            if(visited[nnode]==true) continue;
            visited[nnode] = true;
            q.push(nnode);
            min_distance[nnode]=min_distance[cnode]+1;
        }
    }
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    vector<int> min_distance(n+1, -1);
    
    // Generate map
    for(int i=0; i<roads.size(); i++){
        int from = roads[i][0];
        int to = roads[i][1];
        map[from].push_back(to);
        map[to].push_back(from);
    }
    
    update_distance(min_distance, destination);
    
    for(int i=0; i<sources.size(); i++)
        answer.push_back(min_distance[sources[i]]);
    
    return answer;
}