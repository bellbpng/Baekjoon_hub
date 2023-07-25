#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

map<int, int> updateTotalTime(vector<pair<int, int>>& inArr, vector<pair<int, int>>& outArr){
    map<int, int> ret;
    vector<bool> outVisited(outArr.size(), false);
    vector<bool> inVisited(inArr.size(), false);
    
    int carNum;
    for(int i=0; i<inArr.size(); i++){
        carNum = inArr[i].first;
        for(int j=0; j<outArr.size(); j++){
            if(carNum==outArr[j].first && outVisited[j]==false){
                inVisited[i] = true;
                outVisited[j]=true;
                if(ret.find(carNum)==ret.end())
                    ret[carNum] = outArr[j].second - inArr[i].second;
                else
                    ret[carNum] += (outArr[j].second - inArr[i].second);
                break;
            }
        }
    }
    
    // 나가지 못한 차량 시간 계산
    int endTime = 23*60 + 59;
    for(int i=0; i<inVisited.size(); i++){
        if(inVisited[i]==false){
            carNum = inArr[i].first;
            // cout << "car num: " << carNum << ", " << "cur time: " << inArr[i].second << endl;
            if(ret.find(carNum)==ret.end())
                ret[carNum] = endTime - inArr[i].second;
            else
                ret[carNum] += (endTime - inArr[i].second);
        }
    }
    
    return ret;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    vector<pair<int, int>> inArr, outArr;
    // parsing
    string state, time, hour, min, scarNum;
    int carNum;
    stringstream ss;
    for(int i=0; i<records.size(); i++){
        ss.clear();
        ss.str(records[i]);
        ss >> time >> scarNum >> state;
        hour.push_back(time[0]), hour.push_back(time[1]);
        min.push_back(time[3]), min.push_back(time[4]);
        int tMin = stoi(hour)*60 + stoi(min);
        hour.clear(); min.clear();
        carNum = stoi(scarNum);
        if(state=="IN"){
            inArr.push_back(make_pair(carNum, tMin));
        }
        else if(state=="OUT"){
            outArr.push_back(make_pair(carNum, tMin));
        }
    }
    
    map<int, int> carTime = updateTotalTime(inArr, outArr);
    int parkingTime, totalFee;
    bool alpha;
    for(auto ele:carTime){
        // cout << "car num: " << ele.first << ", " << ele.second << endl;
        parkingTime = ele.second;
        if(parkingTime < fees[0]) // 기본 시간보다 작은 경우 기본 요금 청구
            answer.push_back(fees[1]);
        else{
            alpha = (parkingTime - fees[0]) % fees[2];
            totalFee = fees[1] + ((parkingTime - fees[0])/fees[2] + alpha) * fees[3];
            answer.push_back(totalFee);
        }
    }

    return answer;
}