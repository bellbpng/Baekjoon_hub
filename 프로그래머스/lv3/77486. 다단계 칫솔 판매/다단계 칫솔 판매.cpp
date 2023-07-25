#include <string>
#include <vector>
#include <map>

using namespace std;

void setProfit(map<string, string>& relation, map<string, int>& incomes, string worker, int money){
    if(worker=="-") return;
    if(money==0) return;
    
    int sendMoney = money/10;
    int myMoney = money - sendMoney;
    incomes[worker] += myMoney;
    string recommender = relation[worker];
    setProfit(relation, incomes, recommender, sendMoney);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    // relation & incomes init
    map<string, string> relation;
    map<string, int> incomes; // 직원 별 수익
    for(int i=0; i<enroll.size(); i++){
        relation[enroll[i]] = referral[i];
        incomes[enroll[i]] = 0;
    }
    
    // distribute profits
    string worker; int profit;
    for(int i=0; i<seller.size(); i++){
        worker = seller[i];
        profit = amount[i] * 100;
        setProfit(relation, incomes, worker, profit);
    }
    
    for(int i=0; i<enroll.size(); i++){
        worker = enroll[i];
        answer.push_back(incomes[worker]);
    }
    
    return answer;
}