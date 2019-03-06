/*
https://www.acmicpc.net/problem/11438
*/

#include <cstdio>
#include <vector>
#define MAX_NODE 100001
#define MAX_LEVEL	16
// 최대 노드 개수는 100,000 이고, 2^16 = 65,536, 2^17 = 131,072 이므로
// MAX_LEVEL을 17로 설정하면 depth가 가장 큰 최악의 경우라도 (모든 노드의 자식이 1개인 편향 트리)
// 17번째 조상 탐색 시 루트 노드를 넘어가 버림 (131,072 > 100,000)
// 따라서 50,000 >= log_2(MAX_LEVEL)를 만족하는 15으로 설정
using namespace std;

vector<int> graph[MAX_NODE];	// graph[x] = x와 연결된 모든 노드. graph[x][i] = x와 연결된 i번째 노드
int depth[MAX_NODE];	// depth[x] = 노드 x의 depth
int ancestor[MAX_NODE][MAX_LEVEL + 1];	// ancestor[x][y] = x의 2^y번째 조상

void swap(int &a, int &b) { int tmp = a; a = b; b = tmp; }
// graph를 이용하여 tree 만들기
void getTree(int here, int parent) {
	depth[here] = depth[parent] + 1;
	ancestor[here][0] = parent;	// here의 2^(0)번째 조상, 즉 here의 부모
	
	// ancestor array 구성
	for (int i = 1; i <= MAX_LEVEL; i++) {
		int tmp = ancestor[here][i - 1];	// tmp = here의 2^(i-1)번째 조상
		// here의 2^(i)번째 조상 = tmp의 2^(i-1)번째 조상
		// ex) here의 2번째 조상 = tmp(here의 1번째 조상)의 1번째 조상
		ancestor[here][i] = ancestor[tmp][i - 1];
	}
	// here의 자식 노드에 대해 재귀 호출
	for (int i = 0; i < graph[here].size(); i++) {
		int there = graph[here][i]; // there = here와 연결된 i번째 노드
		if (there != parent)
			// ex) 1이 루트이고, 2와 3은 1의 자식, 4와 5는 2의 자식이면
			//		graph[1] = { 2, 3 }
			//		graph[2] = { 1, 4, 5 }
			//		graph[3] = { 1, ... } 이고,
			//     here = 2, there = 1일 때 there는 here의 부모이므로 제외
			getTree(there, here);
	}
}
// 최소 공통 조상 탐색
int lca(int a, int b) {
	// depth[a]와 depth[b]가 같지 않으면 depth[b]를 맞춰줌
	if (depth[a] != depth[b]) {
		if (depth[a] > depth[b])
			swap(a, b);
		for (int i = MAX_LEVEL; i >= 0; i--)
			if (depth[a] <= depth[ancestor[b][i]])
				b = ancestor[b][i];
	}
	// a와 b가 같은 수이면 자기 자신 리턴. ex) 편향 트리에서 LCA
	if (a == b) return a;
	// a와 b가 같지 않으면 두 노드의 공통 조상을 찾아 이동
	for (int i = MAX_LEVEL; i >= 0; i--)
		// 두 노드의 조상이 같지 않으면 같아질 때까지 이동
		if (ancestor[a][i] != ancestor[b][i])
			a = ancestor[a][i], b = ancestor[b][i];
    
	return ancestor[a][0];	// 공통 조상 리턴
}

int main() {
	int N, M;
	scanf("%d", &N);
	// graph 만들기
	while (--N) {
		int from, to;
		scanf("%d %d", &from, &to);
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	depth[0] = -1;
	getTree(1, 0);
	scanf("%d", &M);
	while (M--) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}
	return 0;
}