#include <iostream>
#include <vector>
#include <queue>

#define INF 9e8
using namespace std;

vector<pair<int, int>> table[20001];
// 우선순위 큐는 첫번째 인자를 우선적으로 비교하여 정렬함
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int dist[20001];
int V, E;

void dijkstra(int start) {
	pq.push(make_pair(0, start)); // (w, v) 순서로 올 것
	dist[start] = 0;

	while (!pq.empty()) {
		int u = pq.top().second;
		int w = pq.top().first;
		pq.pop();

		for (int i = 0; i < table[u].size(); i++) {
			int v = table[u][i].first;
			int x = table[u][i].second;
			if (dist[v] > w + x) {
				dist[v] = w + x;
				pq.push(make_pair(w+x, v));
			}
		}
	}
}

int main()
{
	int K;
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d", &V, &E);
	scanf("%d", &K);

	int u, v, w;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &w);
		table[u].push_back(make_pair(v, w));
	}

	// init
	for (int v = 1; v <= V; v++) {
		dist[v] = INF;
	}
	dijkstra(K);
	for (int v = 1; v <= V; v++) {
		if (dist[v] == INF) printf("INF\n");
		else printf("%d\n", dist[v]);
	}
}
