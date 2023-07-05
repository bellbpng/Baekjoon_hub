#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 오름차순 정렬
bool cmp(int a, int b)
{
    return a<b;
}

int set_match(vector<int>& A, vector<int>& B){
    int n = A.size();
    int aidx=0, bidx=0;
    
    int ret = 0;
    while(true){
        if(aidx>=n) break;
        if(bidx>=n) break;
        
        if(A[aidx] < B[bidx]){ // matching
            ret++;
            aidx++;
            bidx++;
        }
        else{
            bidx++;
        }
    }
    return ret;
}

int solution(vector<int> A, vector<int> B) {
    int answer = -1;
    int n = A.size();
    
    int a_min = *min_element(A.begin(), A.end());
    int a_max = *max_element(A.begin(), A.end());
    int b_min = *min_element(B.begin(), B.end());
    int b_max = *max_element(B.begin(), B.end());
    
    // n점 획득
    if(a_max < b_min) return n;
    // 0점 획득
    if(b_max < a_min) return 0;
    
    sort(A.begin(), A.end(), cmp);
    sort(B.begin(), B.end(), cmp);
    answer = set_match(A,B);
    
    return answer;
}