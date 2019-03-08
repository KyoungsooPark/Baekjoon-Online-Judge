/*
https://www.acmicpc.net/problem/16235
*/

#include <cstdio>
#include <queue>
#define MAX_AGE	1010
using namespace std;
typedef struct { int x, y; } tree;

queue<tree> q[MAX_AGE + 1];
int map[10][10], A[10][10], dead[10][10];
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int N, M, K;
// 봄: 나이가 어린 나무부터 자신의 나이만큼 양분을 먹고 나이 1 증가. 양분이 부족한 나무는 죽음
void spring(void) {
	int qsize[MAX_AGE + 1];	// 나이 별 현재까지 존재하는 나무의 수
	for (int age = 1; age <= MAX_AGE; age++)
		qsize[age] = q[age].size();

	for (int age = 1; age <= MAX_AGE; age++) {
		while (qsize[age]--) {
			tree t = q[age].front(); q[age].pop();
			if (map[t.x][t.y] < age) {	// 양분이 부족한 경우
				dead[t.x][t.y] += age / 2;	// 여름에 추가될 양분을 dead 배열에 저장
				continue;
			}
			map[t.x][t.y] -= age;	// map에서 나무의 나이만큼 양분 흡수
			q[age + 1].push(t);	// 나이 1 증가
		}
	}
}
// 여름: 봄에 죽은 나무가 자신이 있던 칸에 나이를 2로 나눈 값만틈 양분으로 추가. 소수점 아래는 제거
void summer(void) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] += dead[i][j], dead[i][j] = 0;
}
// 가을: 나이가 5의 배수인 나무가 인접한 8개의 칸에 나이 1인 나무를 번식
void fall(void) {
	for (int p = 5; p <= MAX_AGE; p += 5) {	// 나이가 5의 배수인 나무가
		int size = q[p].size();
		while (size--) {
			tree t = q[p].front(); q[p].pop(); q[p].push(t);
			for (int d = 0; d < 8; d++) {	// 인접한 8개의 칸에
				int nx = t.x + dx[d], ny = t.y + dy[d];
				if (0 <= nx && nx < N && 0 <= ny && ny < N)
					q[1].push({ nx, ny });	// 나이가 1인 나무를 번식
			}
		}
	}
}
// 겨울: A에 저장된 양만큼 map에 양분 추가
void winter(void) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			map[i][j] += A[i][j];
}

int main(void) {
	int ans = 0;
	// 입력부
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]), map[i][j] = 5;
	while (M--) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		q[z].push({ x - 1, y - 1 });
	}
	// 처리부
	while (K--) { spring(); summer(); fall(); winter(); }
	for (int age = 1; age <= MAX_AGE; age++)
		ans += q[age].size();
	// 출력부
	printf("%d\n", ans);
	return 0;
}