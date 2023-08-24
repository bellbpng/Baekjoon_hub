#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

int row, col, k;
int rowNum = 3, colNum = 3;
vector<int> rowList[100];
vector<int> colList[100];
int countRowTable[100][101]; // countRowTable[idx][num] 은 idx번 rowList 배열의 num 이 등장한 횟수
int countColTable[100][101];

void printRowList() {
	printf("----------Row List---------------\n");
	for (int r = 0; r < rowNum; r++) {
		for(auto ele:rowList[r])
			printf("%d ", ele);
		printf("\n");
	}
}

void printColList() {
	printf("----------Col List---------------\n");
	for (int c = 0; c < colNum; c++) {
		for (auto ele : colList[c])
			printf("%d ", ele);
		printf("\n");
	}
}

// rowNum >= colNum 인 경우
void operatorR() {
	vector<pair<int, int>> list;
	bool checked[101];
	int num, cnt;
	for (int r = 0; r < rowNum; r++) {
		memset(checked, false, sizeof(checked));
		list.clear();
		for (int i = 0; i < rowList[r].size(); i++) {
			num = rowList[r][i];
			cnt = countRowTable[r][num];
			if (num == 0) continue;
			if (checked[num]) continue;
			checked[num] = true;
			list.push_back(make_pair(cnt, num));
		}
		// 정렬 - first 부터 비교해서 오름차순
		sort(list.begin(), list.end());
		
		// update rowList
		memset(countRowTable[r], 0, sizeof(countRowTable[r]));
		rowList[r].clear();
		for (int i = 0; i < list.size(); i++) {
			rowList[r].push_back(list[i].second);
			rowList[r].push_back(list[i].first);
			countRowTable[r][list[i].second]++;
			countRowTable[r][list[i].first]++;
		}
		colNum = max(colNum, (int)rowList[r].size());
		while (colNum > 100) {
			rowList[r].pop_back();
			colNum--;
		}
	}

	// 0으로 빈칸 채우기
	for (int r = 0; r < rowNum; r++) {
		int cnt = rowList[r].size();
		while (cnt < colNum) {
			rowList[r].push_back(0);
			cnt++;
		}
	}
	// printRowList();

	// update colList
	memset(countColTable, 0, sizeof(countColTable));
	for (int c = 0; c < colNum; c++) {
		colList[c].clear();
		for (int r = 0; r < rowNum; r++) {
			colList[c].push_back(rowList[r][c]);
			countColTable[c][rowList[r][c]]++;
		}
	}
	// printColList();
}

void operatorC() {
	vector<pair<int, int>> list;
	bool checked[101];
	int num, cnt;
	for (int c = 0; c < colNum; c++) {
		memset(checked, false, sizeof(checked));
		list.clear();
		for (int i = 0; i < colList[c].size(); i++) {
			num = colList[c][i];
			cnt = countColTable[c][num];
			if (num == 0) continue;
			if (checked[num]) continue;
			checked[num] = true;
			list.push_back(make_pair(cnt, num));
		}
		// 정렬 - first 부터 비교해서 오름차순
		sort(list.begin(), list.end());

		// update colList
		memset(countColTable[c], 0, sizeof(countColTable[c]));
		colList[c].clear();
		for (int i = 0; i < list.size(); i++) {
			colList[c].push_back(list[i].second);
			colList[c].push_back(list[i].first);
			countColTable[c][list[i].second]++;
			countColTable[c][list[i].first]++;
		}
		rowNum = max(rowNum, (int)colList[c].size());
		while (rowNum > 100) {
			colList[c].pop_back();
			rowNum--;
		}
	}

	// 0으로 빈칸 채우기
	for (int c = 0; c < colNum; c++) {
		int cnt = colList[c].size();
		while (cnt < rowNum) {
			colList[c].push_back(0);
			cnt++;
		}
	}
	// printColList();

	// update rowList
	memset(countRowTable, 0, sizeof(countRowTable));
	for (int r = 0; r < rowNum; r++) {
		rowList[r].clear();
		for (int c = 0; c < colNum; c++) {
			rowList[r].push_back(colList[c][r]);
			countRowTable[r][colList[c][r]]++;
		}
	}
	// printRowList();
}

void setOperate() {
	for (int i = 0; i <= 100; i++) {
		// printRowList();
		if (rowNum >= row && colNum >= col) {
			if (rowList[row - 1][col - 1] == k) {
				printf("%d\n", i);
				return;
			}
		}
		if (rowNum >= colNum) {
			operatorR();
		}
		else {
			operatorC();
		}
	}
	printf("-1\n");
	return;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	scanf("%d %d %d", &row, &col, &k);

	memset(countRowTable, 0, sizeof(countRowTable));
	memset(countColTable, 0, sizeof(countColTable));
	int ele;
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			scanf("%d", &ele);
			rowList[r].push_back(ele);
			colList[c].push_back(ele);
			countRowTable[r][ele]++;
			countColTable[c][ele]++;
		}
	}
	setOperate();
}