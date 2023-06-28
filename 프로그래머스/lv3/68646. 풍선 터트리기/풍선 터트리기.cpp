#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool check_final_possible(vector<int>& dp_front, vector<int>& dp_back, int val, int idx){
    int n = dp_front.size();
    int front = idx-1;
    int end = n-1-front-1;
    
    int left_min = dp_front[front];
    int right_min = dp_back[end];
    
    // cout << "dp_front idx: " << front << " dp_back index: " << end << endl;
    if(val>left_min && val>right_min) return false;
    return true;
}

// Debugging
void print_dp(vector<int>& dp1, vector<int>& dp2){
    cout << "------dp front-----\n";
    for(auto ele:dp1){
        cout << ele << " ";
    }
    cout << endl;
    cout << "------dp back-----\n";
    for(auto ele:dp2){
        cout << ele << " ";
    }
    cout << endl;
}

int solution(vector<int> a) {
    int n = a.size();
    if(n==1) return 1;
    else if(n==2) return 2;
    
    // dp_front[i]는 0~i 범위에서의 최솟값
    // dp_back[i]는 (n-1) ~ (n-i) 범위에서의 최솟값
    int cnt=2;
    vector<int> dp_front(n), dp_back(n);
    dp_front[0] = a[0]; dp_back[0] = a[n-1];
    for(int i=1; i<n; i++){
        dp_front[i] = a[i]<dp_front[i-1] ? a[i] : dp_front[i-1];
        dp_back[i] = a[n-1-i]<dp_back[i-1] ? a[n-1-i] : dp_back[i-1];
    }
    
    // print_dp(dp_front, dp_back);
    
    for(int i=1; i<n-1; i++){
        if(check_final_possible(dp_front, dp_back, a[i], i))
            cnt++;
    }
    
    return cnt;
}