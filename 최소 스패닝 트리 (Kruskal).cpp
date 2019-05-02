/*
https://www.acmicpc.net/problem/1197
*/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

class Edge {
public:
	int left, right, weight;
	Edge(int left, int right, int weight) { this->left = left, this->right = right, this->weight = weight; }
	bool operator < (const Edge &e) const { return this->weight < e.weight; }
};

vector<Edge> v;
int set[10001];
int V, E;
// ���� x�� ���� ��ȣ ��ȯ
int Find(int x) { return set[x] == x ? x : set[x] = Find(set[x]); }
// ���� �ٸ� �� ���� a, b�� ������ �������� ����
void Union(int a, int b) { a = Find(a), b = Find(b); a < b ? set[b] = a : set[a] = b; }
// ���� �ٸ� �� ���� a, b�� ���� �������� �˻�
bool isUnion(int a, int b) { return Find(a) == Find(b); }
// Kruskal �˰���
long long kruskal(void) {
	long long ret = 0;
	for (int v = 1; v <= V; v++)
		set[v] = v;	// �ʱ� ��� ������ ���� ��ȣ�� �ڽ��� ��ȣ�� ����
	sort(v.begin(), v.end());	// graph�� ��� ������ ����ġ ���� �������� ����
	for (const Edge &e : v) {	// ���ĵ� ������ ���� ������� ����Ŭ �˻� �� ����
		if (!isUnion(e.left, e.right)) {	// �� ������ ���� �ٸ� ���� => ���� ���� �� ����Ŭ �߻� ����
			ret += e.weight;	// ���� ����
			Union(e.left, e.right);	// ���� �������� ����
		}
	}
	return ret;
}

int main(void) {
	scanf("%d %d", &V, &E);
	while (E--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		v.push_back(Edge(a, b, c));
	}
	printf("%d\n", kruskal());
	return 0;
}