#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> banned_user_map[8]; // 최대 8개의 아이디가 존재
vector<string> sorted_arr;
bool banned_list[8] = {false, };
int cnt = 0;

// 와일드카드(*)은 모두 매칭 가능하고, 서로 위치가 같으나 문자가 다르면 false 반환
bool check_possible(string& usr_id, string& ban_id, int len){
    for(int i=0; i<len; i++){
        if(ban_id[i]=='*') continue;
        if(usr_id[i] != ban_id[i]) return false;
    }
    return true;
}

void set_banned_user_map(vector<string>& user_id, vector<string>& banned_id){
    for(int ban_idx = 0; ban_idx < banned_id.size(); ban_idx++){
        string ban_id = banned_id[ban_idx];
        for(int usr_idx=0; usr_idx<user_id.size(); usr_idx++){
            string usr_id = user_id[usr_idx];
            if(ban_id.size() != usr_id.size()) continue;
            if(check_possible(usr_id, ban_id, usr_id.size())){
                banned_user_map[ban_idx].push_back(usr_idx);
            }
        }
    }
}

bool check_overlapped(vector<int> cpy_restricted_id){
    sort(cpy_restricted_id.begin(), cpy_restricted_id.end());
    
    string sid;
    for(int i=0; i<cpy_restricted_id.size(); i++){
        sid += to_string(cpy_restricted_id[i]);
    }
    
    for(int j=0; j<sorted_arr.size(); j++){
        if(sid == sorted_arr[j]) return false;
    }
    sorted_arr.push_back(sid);
    return true;
}

void get_all_possible_list(int cid, vector<int>& restricted_id, int len){
    // 기저사례: 모든 제공 받은 id에 대해서 탐색이 끝났을 때
    // 제재 아이디 목록의 길이가 banned_id 의 길이와 같다면 1 반환
    if(cid>=len) {
        if(restricted_id.size()==len && check_overlapped(restricted_id)==true) {
            cnt++;
        }
        return;
    }
    if(banned_user_map[cid].size()==0) 
        get_all_possible_list(cid+1, restricted_id, len);
    
    for(int i=0; i<banned_user_map[cid].size(); i++){
        int user_idx = banned_user_map[cid][i];
        if(banned_list[user_idx]==true) continue;
        banned_list[user_idx] = true;
        restricted_id.push_back(user_idx);
        get_all_possible_list(cid+1, restricted_id, len);
        banned_list[user_idx] = false;
        restricted_id.pop_back();
    }
}

int solution(vector<string> user_id, vector<string> banned_id) {
    int answer = 0;
    
    set_banned_user_map(user_id, banned_id);
    
    vector<int> restricted_id;
    get_all_possible_list(0, restricted_id, banned_id.size());
    
    answer = cnt;
    return answer;
}