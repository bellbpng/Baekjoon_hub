#include <string>
#include <vector>

using namespace std;

int link_computer(vector<vector<int>>& computers, vector<bool>& linked, int cur_computer, int n){
    for(int ncom=0; ncom<n; ncom++){
        if(ncom==cur_computer) continue;
        int link_state = computers[cur_computer][ncom];
        if(link_state==1 && linked[ncom]==false){
            linked[ncom]=true;
            link_computer(computers, linked, ncom, n);
        }
    }
    return 1;
}


int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    vector<bool> linked(n, false);
    for(int ccom=0; ccom<n; ccom++){
        if(linked[ccom]==true) continue;
        linked[ccom] = true;
        answer += link_computer(computers, linked, ccom, n);
    }
    
    return answer;
}