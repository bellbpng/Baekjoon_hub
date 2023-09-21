#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>
using namespace std;

int v, e;
int group[10001];
// costs[i][0] : from, costs[i][1] : to, costs[i][2] : w
vector<vector<int>> costs;

// 비용이 적은 순서대로 정렬
bool cmp(vector<int> v1, vector<int> v2) {
	return v1[2] < v2[2];
}

int findGroup(int node) {
	if (node == group[node]) return node;
	return findGroup(group[node]);
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d", &v, &e);
	int ans = 0;

	for (int i = 0; i < e; i++) {
		int from, to, w;
		scanf("%d %d %d", &from, &to, &w);
		vector<int> node = { from, to, w };
		costs.push_back(node);
	}
	sort(costs.begin(), costs.end(), cmp);

	// init group
	for (int i = 0; i < v; i++) {
		group[i] = i;
	}

	for (int i = 0; i < costs.size(); i++) {
		int from = costs[i][0];
		int to = costs[i][1];
		int w = costs[i][2];

		int gfrom = findGroup(from);
		int gto = findGroup(to);
		if (gfrom != gto) {
			ans += w;
			if (gfrom < gto) group[gto] = gfrom;
			else group[gfrom] = gto;
		}
	}

	printf("%d\n", ans);
	return 0;
}