/*
https://www.acmicpc.net/problem/11438
*/

#include <cstdio>
#include <vector>
#define MAX_NODE 100001
#define MAX_LEVEL	16
// �ִ� ��� ������ 100,000 �̰�, 2^16 = 65,536, 2^17 = 131,072 �̹Ƿ�
// MAX_LEVEL�� 17�� �����ϸ� depth�� ���� ū �־��� ���� (��� ����� �ڽ��� 1���� ���� Ʈ��)
// 17��° ���� Ž�� �� ��Ʈ ��带 �Ѿ ���� (131,072 > 100,000)
// ���� 50,000 >= log_2(MAX_LEVEL)�� �����ϴ� 15���� ����
using namespace std;

vector<int> graph[MAX_NODE];	// graph[x] = x�� ����� ��� ���. graph[x][i] = x�� ����� i��° ���
int depth[MAX_NODE];	// depth[x] = ��� x�� depth
int ancestor[MAX_NODE][MAX_LEVEL + 1];	// ancestor[x][y] = x�� 2^y��° ����

void swap(int &a, int &b) { int tmp = a; a = b; b = tmp; }
// graph�� �̿��Ͽ� tree �����
void getTree(int here, int parent) {
	depth[here] = depth[parent] + 1;
	ancestor[here][0] = parent;	// here�� 2^(0)��° ����, �� here�� �θ�
	
	// ancestor array ����
	for (int i = 1; i <= MAX_LEVEL; i++) {
		int tmp = ancestor[here][i - 1];	// tmp = here�� 2^(i-1)��° ����
		// here�� 2^(i)��° ���� = tmp�� 2^(i-1)��° ����
		// ex) here�� 2��° ���� = tmp(here�� 1��° ����)�� 1��° ����
		ancestor[here][i] = ancestor[tmp][i - 1];
	}
	// here�� �ڽ� ��忡 ���� ��� ȣ��
	for (int i = 0; i < graph[here].size(); i++) {
		int there = graph[here][i]; // there = here�� ����� i��° ���
		if (there != parent)
			// ex) 1�� ��Ʈ�̰�, 2�� 3�� 1�� �ڽ�, 4�� 5�� 2�� �ڽ��̸�
			//		graph[1] = { 2, 3 }
			//		graph[2] = { 1, 4, 5 }
			//		graph[3] = { 1, ... } �̰�,
			//     here = 2, there = 1�� �� there�� here�� �θ��̹Ƿ� ����
			getTree(there, here);
	}
}
// �ּ� ���� ���� Ž��
int lca(int a, int b) {
	// depth[a]�� depth[b]�� ���� ������ depth[b]�� ������
	if (depth[a] != depth[b]) {
		if (depth[a] > depth[b])
			swap(a, b);
		for (int i = MAX_LEVEL; i >= 0; i--)
			if (depth[a] <= depth[ancestor[b][i]])
				b = ancestor[b][i];
	}
	// a�� b�� ���� ���̸� �ڱ� �ڽ� ����. ex) ���� Ʈ������ LCA
	if (a == b) return a;
	// a�� b�� ���� ������ �� ����� ���� ������ ã�� �̵�
	for (int i = MAX_LEVEL; i >= 0; i--)
		// �� ����� ������ ���� ������ ������ ������ �̵�
		if (ancestor[a][i] != ancestor[b][i])
			a = ancestor[a][i], b = ancestor[b][i];
    
	return ancestor[a][0];	// ���� ���� ����
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