/*
https://www.acmicpc.net/problem/2606
*/

#include <cstdio>
#include <vector>
using namespace std;

int set[101];

int Find(int x) { return (x == set[x]) ? x : set[x] = Find(set[x]); }
void Union(int x, int y) { x = Find(x), y = Find(y); x < y ? set[y] = x : set[x] = y; }
bool isUnion(int x, int y) { return Find(x) == Find(y); }

int main(void) {
	int N, M, cnt = 0;
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; i++)
		set[i] = i;

	for (int i = 1; i <= M; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		Union(a, b);
	}

	for (int i = 2; i <= N; i++)
		if (isUnion(1, i))
			cnt++;

	printf("%d\n", cnt);
	return 0;
}
