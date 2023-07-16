#include <string>
#include <vector>

using namespace std;

int solution(vector<int> absolutes, vector<bool> signs) {
    int answer = 0;
    int len = absolutes.size();
    
    for(int i=0; i<len; i++){
        int val = signs[i]==true? 1: -1;
        answer += (absolutes[i]*val);
    }
    
    
    return answer;
}