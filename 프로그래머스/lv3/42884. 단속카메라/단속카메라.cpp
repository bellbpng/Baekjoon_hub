#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b){
    return a.second < b.second;
}

int solution(vector<vector<int>> routes) {
    int answer = 0;
    int n = routes.size();
    
    // 진출 지점을 기준으로 오름차순 정렬
    vector<pair<int, int>> cars;
    for(int i=0; i<n; i++){
        cars.push_back(make_pair(routes[i][0], routes[i][1]));
    }
    sort(cars.begin(), cars.end(), cmp);
    
    answer = n;
    int cam_idx = cars[0].second;
    for(int i=1; i<n; i++){
        int start = cars[i].first;
        int end = cars[i].second;
        if(start<=cam_idx) 
            answer--;
        else 
            cam_idx = end;
    }
    
    return answer;
}