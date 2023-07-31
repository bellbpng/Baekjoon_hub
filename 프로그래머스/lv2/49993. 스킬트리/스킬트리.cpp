#include <string>
#include <vector>

using namespace std;

bool CheckSkillList(string skill, string trees){
    if(skill == trees) return true;
    for(int i=0; i<trees.size(); i++){
        if(skill[i] != trees[i]) return false;
    }
    return true;
}

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    int skill_arr[26] = {0,};
    for(int i=0; i<skill.size(); i++){
        skill_arr[skill[i] -'A']++;
    }
    
    string tmp;
    for(auto ele:skill_trees){
        tmp.clear();
        for(int i=0; i<ele.size(); i++){
            if(skill_arr[ele[i]-'A']==1)
                tmp.push_back(ele[i]);
        }
        if(CheckSkillList(skill, tmp)) answer++;
    }
    
    return answer;
}