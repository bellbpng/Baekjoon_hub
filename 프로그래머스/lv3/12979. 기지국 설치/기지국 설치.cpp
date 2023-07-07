#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    int answer = 0;
    
    // 전파가 도달되지 않는 부분 영역의 길이를 담는다.
    vector<int> not_comm_area;
    int comm_area = 2*w+1; // 기지국이 전파할 수 있는 영역의 길이
    int apt_idx, start = 1, end;
    int len;
    for(int i=0; i<stations.size(); i++){
        apt_idx = stations[i];
        end = apt_idx - w; // 전파가 전달되지 않는 마지막 아파트 다음을 가리킴
        len = end - start;
        if(len>=1)
            not_comm_area.push_back(len);
        start = apt_idx + w + 1; // 전파가 전달되지 않는 아파트 시작점
    }
    end = n+1;
    len = end - start;
    if(len>=1) not_comm_area.push_back(len);
    
    for(int i=0; i<not_comm_area.size(); i++){
        int cnt = not_comm_area[i]/comm_area;
        int r = not_comm_area[i]%comm_area;
        if(r>0) cnt++;
        answer += cnt;
    }
    
    return answer;
}