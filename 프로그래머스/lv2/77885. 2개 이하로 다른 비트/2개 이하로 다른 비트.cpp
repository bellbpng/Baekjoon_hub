#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    
    for(int i=0; i<numbers.size(); i++){
        long long num = numbers[i];
        
        if(num%2==0){ // 짝수인 경우 0번 비트에 + 1
            answer.push_back(num+1);
        }
        else{ // 홀수인 경우
            // 1. 작은 수의 비트부터 0인 곳을 찾는다.
            long long data = num;
            long long mask = 1;
            int cnt = 0;
            while((data & 1) != 0){
                cnt++;
                data >>= 1;
            }
            data++; // 0 -> 1
            data <<= cnt;
            data = data | num;
            mask <<= (cnt - 1);
            data -= mask; // 0 옆 비트를 1로
            answer.push_back(data);
        }
    }
    
    return answer;
}