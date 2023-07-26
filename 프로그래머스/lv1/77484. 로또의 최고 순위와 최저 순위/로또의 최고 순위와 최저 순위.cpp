#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    int allNums[46] = {0, }; // 1 ~ 45
    int rank[7] = {6, 6, 5, 4, 3, 2, 1};
    for(int i=0; i<win_nums.size(); i++){
        allNums[win_nums[i]] = 1;
    }
    
    int hit = 0, numZero = 0;
    for(int i=0; i<lottos.size(); i++){
        if(lottos[i]==0) numZero++;
        else if(allNums[lottos[i]]==1) hit++;
    }
    int maxScore = hit + numZero;
    int minScore = hit;
    answer.push_back(rank[maxScore]);
    answer.push_back(rank[minScore]);
    
    return answer;
}