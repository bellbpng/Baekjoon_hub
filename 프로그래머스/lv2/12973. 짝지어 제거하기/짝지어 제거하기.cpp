#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = -1;
    int len = s.length();
    int front = 0, rear = front+1;
    stack<int> not_removed;
    
    while(true){
        if(front>=len){
            answer = 1;
            break;
        }
        if(rear>=len){
            answer = 0;
            break;
        }
        
        if(s[front]==s[rear]){
            rear++;
            if(not_removed.size()==0)
                front = rear++;
            else{
                front = not_removed.top();
                not_removed.pop();
            }
        }
        else{
            not_removed.push(front);
            front = rear++;
        }
    }
    

    return answer;
}