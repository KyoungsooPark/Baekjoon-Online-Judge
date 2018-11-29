/*
https://www.acmicpc.net/problem/16235
*/

#include <cstdio>
#include <queue>
#define PRIORITY	1000
using namespace std;
typedef struct { int x, y, l; } point;

queue<point> q[PRIORITY];	// 우선순위 큐
int map[10][10], A[10][10];
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
int N, M, K;

void spring(void) {
	int qsize[PRIORITY];
	for (int p = 1; p < PRIORITY; p++)
		// 나무의 나이를 증가시켜서 다시 큐에 삽입하므로 큐 사이즈가 수시로 달라짐
		// 따라서 미리 현재 큐 사이즈를 저장해야 함
		qsize[p] = q[p].size();

	for (int p = 1; p < PRIORITY; p++) {
		while (qsize[p]--) {
			point pnt = q[p].front();
			q[p].pop();
			if (map[pnt.x][pnt.y] >= p) {	// 양분이 충분한 경우
				map[pnt.x][pnt.y] -= p;	// 양분 섭취
				pnt.l++;		// 나이 증가
				q[pnt.l].push(pnt);	// 해당 나이의 큐에 삽입
			}
			else			// 양분이 부족한 경우
				q[0].push(pnt);	// 나무가 죽어 0번째 큐에 삽입
		}
	}
}

void summer(void) {
	int qsize = q[0].size();
	while (qsize--) {
		point pnt = q[0].front();
		q[0].pop();
		map[pnt.x][pnt.y] += pnt.l / 2;	// 죽은 나무 나이의 절반이 양분으로 추가
	}
}

void fall(void) {
	// 나이가 5의 배수인 나무가 번식
	for (int p = 5; p < PRIORITY; p += 5) {
		int qsize = q[p].size();
		while (qsize--) {
			point pnt = q[p].front();
			q[p].pop();
			for (int d = 0; d < 8; d++) {
				int nx = pnt.x + dx[d], ny = pnt.y + dy[d];
				if (0 <= nx && nx < N && 0 <= ny && ny < N)
					q[1].push({ nx, ny, 1 });	// 번식 가능한 위치에 나이 1의 나무 번식
			}
			q[p].push(pnt);	// 새로운 나무를 번식시킨 나무를 다시 큐에 삽입
		}
	}
}

void winter(void) {
	// 양분 추가
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			map[x][y] += A[x][y];
}

int main(void) {
	int ans = 0;
	
	// 입력부
	scanf("%d %d %d", &N, &M, &K);
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			scanf("%d", &A[x][y]);
			map[x][y] = 5;
		}
	}
	for (int m = 0; m < M; m++) {
		int x, y, l;
		scanf("%d %d %d", &x, &y, &l);
		q[l].push({ x - 1, y - 1, l });
	}
	
	// 처리부
	while (K--)
		spring(), summer(), fall(), winter();
	
	// 출력부
	for (int p = 1; p < PRIORITY; p++)
		ans += q[p].size();
	printf("%d\n", ans);

	return 0;
}
