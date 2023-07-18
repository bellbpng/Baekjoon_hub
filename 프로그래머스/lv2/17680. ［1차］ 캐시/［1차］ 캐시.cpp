#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <cctype>

using namespace std;

void set_to_lower_case(vector<string>& cities){
    for(int i=0; i<cities.size(); i++){
        for(int j=0; j<cities[i].size(); j++){
            if(isupper(cities[i][j]))
                cities[i][j] = tolower(cities[i][j]);
        }
    }
}

string get_lru_city(map<string, int>& cache){
    string city = cache.begin()->first;
    int least_val = cache.begin()->second;
    
    for(auto ele:cache){
        if(ele.second < least_val){
            least_val = ele.second;
            city = ele.first;
        }
    }
    return city;
}

int solution(int cacheSize, vector<string> cities) {
    int run_time = 0;    
    if(cacheSize==0) {
        run_time = cities.size() * 5;
        return run_time;
    }
    
    set_to_lower_case(cities);
    
    map<string, int> cache;
    for(int i=0; i<cities.size(); i++){
        // cache에 없는 경우(miss) 실행시간 5 증가
        if(cache.find(cities[i])==cache.end()){
            if(cache.size()==cacheSize){
                cache.erase(get_lru_city(cache));
            }
            run_time += 5;
            cache[cities[i]]=i;
        }
        else { // cache에 있는 경우(hit) 실행시간 1 증가
            run_time++;
            cache[cities[i]]=i;
        }
        
    }
    
    return run_time;
}