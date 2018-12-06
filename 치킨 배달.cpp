/*
https://www.acmicpc.net/problem/15686
*/

#include <cstdio>
#include <vector>
using namespace std;
typedef struct { int r, c; } point;
vector<point> house, chicken;
vector<int> check;
int N, M;

int abs(int num) { return num >= 0 ? num : -num; }
int min(int a, int b) { return a <= b ? a : b; }
int dist(int r1, int c1, int r2, int c2) { return abs(r1 - r2) + abs(c1 - c2); }
int mindist(int r, int c) {	// 가장 짧은 거리 반환
	int ret = 2e9;
	for (const int &i : check)
		ret = min(ret, dist(r, c, chicken[i].r, chicken[i].c));
	return ret;
}

int main(void) {
	int ans = 2e9;
	// 입력부
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int temp;
			scanf("%d", &temp);
			switch (temp) {
			case 1: house.push_back({ i, j }); break;
			case 2: chicken.push_back({ i, j }); break;
			}
		}
	}
	// 처리부
	for (int i = 0; i < (1 << chicken.size()); i++) {
		for (int j = 0; j < chicken.size(); j++)
			if (i & (1 << j))
				check.push_back(j);
		if (check.size() == M) {
			int temp = 0;
			for (const point &h : house)
				temp += mindist(h.r, h.c);
			ans = min(ans, temp);
		}
		check.clear();
	}
	// 출력부
	printf("%d\n", ans);
	return 0;
}