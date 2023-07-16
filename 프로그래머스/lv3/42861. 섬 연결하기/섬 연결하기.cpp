#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(vector<int> a, vector<int> b){
    return a[2] < b[2];
}

int find_group(vector<int>& group, int node){
    if(node == group[node])
        return node;
    else
        return find_group(group, group[node]);
}

// 크루스칼 알고리즘
// 최소신장트리 - 사이클이 없는 그래프, 가중치 합이 최소가 되는 트리
int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    
    // 오름차순 정렬
    sort(costs.begin(), costs.end(), cmp);
    vector<int> group(n); // 노드 별 그룹(루트) 번호. group[i] = 1 은 i번 노드는 1번 노드를 루트로 가짐
    for(int i=0; i<n; i++)
        group[i] = i;
    
    int from, to, w;
    for(int i=0; i<costs.size(); i++){
        from = costs[i][0];
        to = costs[i][1];
        w = costs[i][2];
        
        int gfrom = find_group(group, from);
        int gto = find_group(group, to);
        if(gfrom != gto){
            answer += w;
            if(gfrom<gto) group[gto] = gfrom;
            else group[gfrom] = gto;
        }
    }
    
    return answer;
}