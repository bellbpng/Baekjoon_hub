#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

int get_ctg_len(vector<string> cpy_gems){
    int len = cpy_gems.size();
    sort(cpy_gems.begin(), cpy_gems.end());
    int ctg_len = 1;
    string ref = cpy_gems[0];
    for(int i=1; i<len; i++){
        if(ref != cpy_gems[i]){
            ctg_len++;
            ref = cpy_gems[i];
        }
    }
    
    return ctg_len;
}

vector<int> solution(vector<string> gems) {
    vector<int> answer = {1, 1};
    int ctg_len = get_ctg_len(gems);
    int gems_len = gems.size();
    int dsp_start = 1;
    int dsp_end;
    
    map<string, int> dict;
    map<string, int>::iterator iter;
    string gem;
    for(int i=0; i<gems_len; i++){
        gem = gems[i];
        iter = dict.find(gem);
        if(iter==dict.end()) // 찾을 수 없다면 end 반환
            dict[gem] = 1;
        else
            dict[gem]++;
        if(dict.size()==ctg_len){
            dsp_end = i+1;
            break;
        }
    }
    
    // 보석 종류가 1개라면 [1,1] 반환
    if(dict.size()==1)
        return answer;
    
    // 보석 종류가 2개 이상인 경우
    int nstart, nend;
    int diff = dsp_end - dsp_start + 1;
    answer[0] = dsp_start; answer[1] = dsp_end;
    while(dsp_start<dsp_end && dsp_end <= gems_len){
        nstart = dsp_start + 1;
        nend = dsp_end;
        gem = gems[dsp_start-1];
        dict[gem]--;
        if(dict[gem]==0){
            dict[gem]++;
            dsp_end++;
            if(dsp_end<=gems_len)
                dict[gems[dsp_end-1]]++;
        }
        else{
            if(diff > (nend - nstart + 1)){
                diff = nend - nstart + 1;
                answer[0] = nstart;
                answer[1] = nend;
            }
            dsp_start = nstart;
        }
    }
    return answer;
}