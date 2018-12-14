/*
https://www.acmicpc.net/problem/11438
*/

#include <cstdio>
#include <vector>
#define MAX_NODE 100001
#define MAX_LEVEL	16
// MAX_NODE�� 100,000 �̰�, 2^16 = 65,536, 2^17 = 131,072 �̹Ƿ�
// max_level�� 17�� �����ϸ� depth�� ���� ū �־��� ���� (��� ����� �ڽ��� 1���� ���� Ʈ��)
// 17��° ���� Ž�� �� ��Ʈ ��带 �Ѿ ����. ���� max_level = log_2(100,000) ���� ���� ������ 16�� �ִ��̴�.
using namespace std;

vector<int> graph[MAX_NODE];	// graph[x] :: x�� ����� ��� ���. graph[x][i] :: x�� ����� i��° ���
int depth[MAX_NODE];	// depth[x] :: ��� x�� depth
int ac[MAX_NODE][17];	// ac[x][y] :: x�� 2^y��° ������ �ǹ�

void swap(int &a, int &b) { int tmp = a; a = b; b = tmp; }
// graph�� �̿��Ͽ� tree �����
void getTree(int here, int parent) {
	depth[here] = depth[parent] + 1;
	ac[here][0] = parent;	// here�� 2^(0)��° ����, �� here�� ù ��° ����
	
	for (int i = 1; i <= MAX_LEVEL; i++) {
		// tmp :: here�� 2^(i-1)��° ����
		// here�� 2^(i)��° ���� = tmp�� 2^(i-1)��° ����. ��, ac[here][i] = ac[tmp][i-1]
		// ex) here�� 8��° ���� = tmp(here�� 4��° ����)�� 4��° ����
		int tmp = ac[here][i - 1];
		ac[here][i] = ac[tmp][i - 1];	
	}

	for (int i = 0; i < graph[here].size(); i++) {
		// there :: x�� ����� i��° ���
		// ex) 1�� ��Ʈ ����̰�, 2�� 3�� 1�� �ڽ� ���, 4�� 6�� 2�� �ڽ� ����� ��,
		//		graph[1] :: { 2, 3 }
		//		graph[2] :: { 1, 4, 6 }
		//		graph[3] :: { 1 } 
		// �̹Ƿ�, here = 1, there = 2���� getTree(2, 1) ��� ȣ�� �� there(1) = parent(1)�� ���� ����
		int there = graph[here][i];
		if (there != parent)
			getTree(there, here);
	}
}

int lca(int a, int b) {
	// depth[a]�� depth[b]�� ���� ������ depth[b]�� ������
	if (depth[a] != depth[b]) {
		if (depth[a] > depth[b])
			swap(a, b);
		for (int i = MAX_LEVEL; i >= 0; i--)
			if (depth[a] <= depth[ac[b][i]])
				b = ac[b][i];
	}
	// a�� b�� ���� ���̸� �ڱ� �ڽ� ����
	if (a == b)
		return a;
	// a�� b�� ���� ������ �� ����� ���� ������ ã�� �ö�
	for (int i = MAX_LEVEL; i >= 0; i--) {
		// �� ����� ������ ���� ������ ������ ������ �ö�
		if (ac[a][i] != ac[b][i])
			a = ac[a][i], b = ac[b][i];
	}
	return ac[a][0];	// ���� ���� ����
}

int main() {
	int N, M;
	scanf("%d", &N);
	// graph �����
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