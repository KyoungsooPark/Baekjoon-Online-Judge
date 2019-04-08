/*
https://www.acmicpc.net/problem/17135
*/

#include <cstdio>
#include <queue>
#include <vector>
using namespace std;
typedef struct { int x, y; } point;

queue<point> q;		// 적의 위치 저장 및 움직임 시뮬레이션을 위한 큐
point archer[3];	// 궁수
int map[15][15];	// 맵의 초기 상태
int cpy[15][15];	// 시뮬레이션을 위한 카피 맵
int cpy_next[15][15];	// 카피 맵의 다음 상태를 저장하기 위한 임시 맵
int N, M, D, ans = 0;

int max(int a, int b) { return a > b ? a : b; }
int abs(int num) { return num >= 0 ? num : -num; }
// 궁수의 위치 (x, y)로부터 공격 가능한 적 탐색
point search(int x, int y) {
	point ret = { -1, -1 };	// 반환할 적의 위치
	int tempD = D + 1;	// 사거리 내 가장 가까운 적과의 거리를 기억하기 위한 변수
	for (int i = x - D; i < x; i++) {
		for (int j = y - D + 1; j <= y + D - 1; j++) {
			if (0 <= j && j < M && cpy[i][j]) {	// 탐색 범위에 적이 존재
				int temp = abs(x - i) + abs(y - j);	 // 적과의 거리 계산
				if (tempD > temp) {	// 사거리 D 이내 또는 더 가까운 적인 경우
					ret = { i, j };	// 적 위치 저장
					tempD = temp;	// 해당 적과의 거리 저장
				}
				else if (tempD == temp) {	// 현재까지 가장 가까운 적과의 거리와 같은 거리의 적 발견
					if (ret.y > j)	// 더 왼쪽의 적인 경우
						ret = { i, j };	// 해당 적 위치 저장
				}
			}
		}
	}
	// 탐색 결과가 존재하지 않는 경우 { -1, -1 } 반환, 존재하는 경우 해당 적의 위치 반환
	return ret;
}

int simulation(void) {
	int killed = 0;	// 제거한 적의 총합
	// 맵 카피
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++) {
			cpy[i][j] = map[i][j];
			if (map[i][j])
				q.push({ i, j });	// 적의 위치 큐에 삽입
		}

	while (!q.empty()) {
		vector<point> v;	// 공격할 적을 저장할 벡터
		for (int i = 0; i < 3; i++) {	// 총 세명의 궁수에 대해
			point p = search(archer[i].x, archer[i].y);	// 공격할 적 탐색
			if (p.x != -1)	// 탐색 결과 공격 대상이 존재하는 경우
				v.push_back(p);	// 벡터에 저장 (서로 다른 두 궁수의 타겟이 중복될 수 있음)
		}
		// 공격 가능한 적 제거
		for (int i = 0; i < v.size(); i++)
			if (cpy[v[i].x][v[i].y]) {	// 해당 위치에 적이 존재하면(중복되는 적인 경우 이미 제거되었을 수 있음)
				killed++;	// 제거한 적의 수 증가
				cpy[v[i].x][v[i].y] = 0;	// 해당 적을 맵에서 제거
			}
		int size = q.size();	// 전체 적을 일괄적으로 움직이기 위한 변수
		while (size--) {
			point p = q.front(); q.pop();
			if (cpy[p.x][p.y]) {	// 궁수에게 제거되지 않은 경우
				p.x++;	// 성이 있는 위치로 한 칸 접근
				if (p.x < N) {	// 성벽에 도달하지 않은 경우
					cpy_next[p.x][p.y] = 1;	// 다음 상태 맵(cpy_next 배열)에 해당 적 표시
					q.push(p);	// 큐에 삽입
				}
			}
		}
		// cpy 맵에 cpy_next 복사 및 cpy_next 초기화
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				cpy[i][j] = cpy_next[i][j], cpy_next[i][j] = 0;
	}
	return killed;	// 제거한 적의 총합 반환
}

void go(int n, int cur) {
	if (n == 3) {
		ans = max(ans, simulation());
		return;
	}
	for (int i = cur; i < M; i++) {
		archer[n] = { N, i };
		go(n + 1, cur + 1);
	}
}

int main(void) {
	// 입력부
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			scanf("%d", &map[i][j]);
	// 처리부
	go(0, 0);
	// 출력부
	setbuf(stdout, NULL);
	printf("%d\n", ans);
	return 0;
}