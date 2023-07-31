#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

typedef struct _fileInfo{
    string filename;
    string head;
    int number;
    int index;
} FileInfo;

bool cmp(FileInfo f1, FileInfo f2){
    if(f1.head != f2.head){
        return f1.head < f2.head;
    }
    if(f1.number != f2.number){
        return f1.number < f2.number;
    }
    return f1.index < f2.index;
}

vector<string> solution(vector<string> files) {
    vector<string> answer;
    
    // parsing
    vector<FileInfo> table;
    string tname, thead, tnumber;
    int tindex;
    for(int index=0; index<files.size(); index++){
        tname.clear(), thead.clear(), tnumber.clear();
        tname = files[index]; tindex = index;
        string file = files[index];
        int idx = 0;
        // head 결정 (소문자)
        for(int i=0; i<file.size(); i++){
            if(isdigit(file[i])) break;
            if(isupper(file[i])) {
                file[i] = tolower(file[i]);
            }
            thead.push_back(file[i]);
            idx = i;
        }
        // number 결정
        for(int i=idx+1; i<file.size(); i++){
            if(!isdigit(file[i])) break;
            tnumber.push_back(file[i]);
        }
        
        FileInfo fi = {tname, thead, stoi(tnumber), tindex};
        table.push_back(fi);
    }
    
    sort(table.begin(), table.end(), cmp);
    for(int i=0; i<table.size(); i++){
        answer.push_back(table[i].filename);
    }
    
    return answer;
}