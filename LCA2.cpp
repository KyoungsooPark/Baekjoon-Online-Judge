/*
https://www.acmicpc.net/problem/11438
*/

#include <cstdio>
#include <vector>
#define MAX_NODE 100001
#define MAX_LEVEL	16
// MAX_NODE는 100,000 이고, 2^16 = 65,536, 2^17 = 131,072 이므로
// max_level을 17로 설정하면 depth가 가장 큰 최악의 경우라도 (모든 노드의 자식이 1개인 편향 트리)
// 17번째 조상 탐색 시 루트 노드를 넘어가 버림. 따라서 max_level = log_2(100,000) 보다 작은 정수인 16이 최댓값이다.
using namespace std;

vector<int> graph[MAX_NODE];	// graph[x] :: x와 연결된 모든 노드. graph[x][i] :: x와 연결된 i번째 노드
int depth[MAX_NODE];	// depth[x] :: 노드 x의 depth
int ac[MAX_NODE][17];	// ac[x][y] :: x의 2^y번째 조상을 의미

void swap(int &a, int &b) { int tmp = a; a = b; b = tmp; }
// graph를 이용하여 tree 만들기
void getTree(int here, int parent) {
	depth[here] = depth[parent] + 1;
	ac[here][0] = parent;	// here의 2^(0)번째 조상, 즉 here의 첫 번째 조상
	
	for (int i = 1; i <= MAX_LEVEL; i++) {
		// tmp :: here의 2^(i-1)번째 조상
		// here의 2^(i)번째 조상 = tmp의 2^(i-1)번째 조상. 즉, ac[here][i] = ac[tmp][i-1]
		// ex) here의 8번째 조상 = tmp(here의 4번째 조상)의 4번째 조상
		int tmp = ac[here][i - 1];
		ac[here][i] = ac[tmp][i - 1];	
	}

	for (int i = 0; i < graph[here].size(); i++) {
		// there :: x와 연결된 i번째 노드
		// ex) 1이 루트 노드이고, 2와 3은 1의 자식 노드, 4와 6은 2의 자식 노드일 때,
		//		graph[1] :: { 2, 3 }
		//		graph[2] :: { 1, 4, 6 }
		//		graph[3] :: { 1 } 
		// 이므로, here = 1, there = 2에서 getTree(2, 1) 재귀 호출 시 there(1) = parent(1)인 경우는 제외
		int there = graph[here][i];
		if (there != parent)
			getTree(there, here);
	}
}

int lca(int a, int b) {
	// depth[a]와 depth[b]가 같지 않으면 depth[b]를 맞춰줌
	if (depth[a] != depth[b]) {
		if (depth[a] > depth[b])
			swap(a, b);
		for (int i = MAX_LEVEL; i >= 0; i--)
			if (depth[a] <= depth[ac[b][i]])
				b = ac[b][i];
	}
	// a와 b가 같은 수이면 자기 자신 리턴
	if (a == b)
		return a;
	// a와 b가 같지 않으면 두 노드의 공통 조상을 찾아 올라감
	for (int i = MAX_LEVEL; i >= 0; i--) {
		// 두 노드의 조상이 같지 않으면 같아질 때까지 올라감
		if (ac[a][i] != ac[b][i])
			a = ac[a][i], b = ac[b][i];
	}
	return ac[a][0];	// 공통 조상 리턴
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