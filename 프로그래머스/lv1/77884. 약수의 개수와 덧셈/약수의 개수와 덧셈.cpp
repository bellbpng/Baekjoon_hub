#include <string>
#include <vector>

using namespace std;

int solution(int left, int right) {
    int answer = 0;
    
    vector<int> power_num;
    for(int i=1; i<=32; i++){
        power_num.push_back(i*i);
    }
    
    for(int num=left; num<=right; num++){
        bool flag = true;
        for(int i=0; i<power_num.size(); i++){
            if(num==power_num[i]){
                answer -= num;
                flag = false;
                break;
            }
        }
        if(flag) answer += num;
    }
    
    return answer;
}