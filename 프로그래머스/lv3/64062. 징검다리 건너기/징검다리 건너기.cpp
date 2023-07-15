#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool check_cross_stones(vector<int>& stones, int mid, int k){
    int cnt = 0;
    for(int i=0; i<stones.size(); i++){
        if(stones[i]-mid <= 0) cnt++;
        else cnt = 0;
        if(cnt>=k) return false;
    }
    return true;
}

int solution(vector<int> stones, int k) {
    int max_student = *max_element(stones.begin(), stones.end());
    
    // 이분탐색으로 징검다리를 건널 수 있는 학생 수를 찾아간다.
    // mid 에서 건너지 못한다면, right = mid - 1 로 바꿔서 탐색
    // mid 에서 건널 수 있다면, mid 이하인 값들에서는 건널 수 있으므로 left = mid+1 로 바꿔서 탐색
    int left = 1, right = max_student;
    int mid = 0;
    while(left<=right){
        mid = (left+right)/2;
        if(check_cross_stones(stones, mid, k)){
            left = mid + 1;           
        }
        else{
            right = mid - 1;
        }
    }
    
    return left;
}