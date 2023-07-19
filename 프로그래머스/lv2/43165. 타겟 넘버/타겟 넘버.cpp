#include <string>
#include <vector>

using namespace std;

int get_target(vector<int>& numbers, vector<int>& cand, int target, int node, int n){
    if(cand.size()==n){
        int sum = 0;
        for(int i=0; i<n; i++){
            sum += cand[i];
        }
        if(sum==target) return 1;
        else return 0;
    }
    
    int ret = 0;
    for(int i=0; i<2; i++){
        if(i==0) cand.push_back(numbers[node]);
        else if(i==1) cand.push_back(numbers[node]*(-1));
        ret += get_target(numbers, cand, target, node+1, n);
        cand.pop_back();
    }
    return ret;
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    int n = numbers.size();
    vector<int> cand;
    answer = get_target(numbers, cand, target, 0, n);
    
    return answer;
}