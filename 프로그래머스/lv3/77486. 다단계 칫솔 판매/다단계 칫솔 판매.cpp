#include <string>
#include <vector>
#include <iostream>

using namespace std;

void convert_recommander_to_idx(vector<string>& enroll, int idx, vector<int>& referral_t, string name){
    int n = enroll.size();
    for(int i=0; i<n; i++){
        if(enroll[i] == name){
            referral_t[idx] = i;
        }
    }
}

void convert_seller_to_idx(vector<string>& enroll, int idx, vector<int>& seller_t, string name){
    int n = enroll.size();
    for(int i=0; i<n; i++){
        if(enroll[i] == name){
            seller_t[idx] = i;
        }
    }
}

void update_money(vector<int>& answer, vector<int>& referral_t, int seller_idx, int profit){
    // 기저사례: 나한테 들어온 돈이 0일때
    if(profit==0) return;
    // 기저사례: seller_idx==-1 인 경우
    if(seller_idx==-1) return;
    
    int send_money = profit/10;
    int my_money = profit - send_money;
    answer[seller_idx] += my_money;
    
    int nseller_idx = referral_t[seller_idx];
    update_money(answer, referral_t, nseller_idx, send_money);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    
    int n = enroll.size();
    vector<int> referral_t(n);
    vector<int> answer(n, 0);
    
    string rname;
    for(int i=0; i<n; i++){
        rname = referral[i];
        if(rname=="-") {
            referral_t[i]=-1; // center
            continue;
        }
        convert_recommander_to_idx(enroll, i, referral_t, rname);
    }
    
    int sell_len = seller.size();
    vector<int> seller_t(sell_len);
    string sname;
    for(int i=0; i<sell_len; i++){
        sname = seller[i];
        convert_seller_to_idx(enroll, i, seller_t, sname);
    }
    
    int seller_idx;
    for(int i=0; i<sell_len; i++){
        seller_idx = seller_t[i];
        update_money(answer, referral_t, seller_idx, amount[i]*100);
    }
    
    return answer;
}