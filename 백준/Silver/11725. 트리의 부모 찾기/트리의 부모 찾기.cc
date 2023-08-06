#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> graph[100001];

void Dfs(vector<bool>& visited, vector<int>& parentNode, int curV, int cnt) {
	if (cnt == n) return;

	for (int i = 0; i < graph[curV].size(); i++) {
		int nnode = graph[curV][i];
		if (visited[nnode] == true) continue;
		visited[nnode] = true;
		parentNode[nnode] = curV;
		Dfs(visited, parentNode, nnode, cnt + 1);
	}
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n-1; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		graph[from].push_back(to);
		graph[to].push_back(from);
	}

	vector<bool> visited(n + 1, false);
	vector<int> parentNode(n + 1, 1); // parentNode[2]는 2번 노드의 부모 노드를 의미함
	visited[1] = true;
	Dfs(visited, parentNode, 1, 1);
	for (int i = 2; i <= n; i++)
		printf("%d\n", parentNode[i]);

	return 0;
}