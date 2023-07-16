#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b){
    return a<b;
}

vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    
    int sum;
    for(int i=0; i<numbers.size()-1; i++){
        for(int j=i+1; j<numbers.size(); j++){
            sum = numbers[i] + numbers[j];
            if(find(answer.begin(), answer.end(), sum) == answer.end())
                answer.push_back(sum);
        }
    }
    
    sort(answer.begin(), answer.end(), cmp);
    return answer;
}