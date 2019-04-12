/*
https://www.acmicpc.net/problem/17135
*/

#include <iostream>
#include <vector>
using namespace std;
struct point { int x, y; };

point archer[3];	// 궁수
bool map[15][15];	// 맵의 초기 상태
bool cpy[15][15];	// 시뮬레이션을 위한 카피 맵
int N, M, D, ans = 0;

int abs(int num) { return num < 0 ? -num : num; }
int max(int a, int b) { return a > b ? a : b; }
// 궁수의 위치 (x, y)로부터 공격 가능한 적 탐색
point search(point p) {
	point ret = { -1, -1 };	// 반환할 적의 위치
	int tempD = D + 1;	// 사거리 내 가장 가까운 적과의 거리를 기억하기 위한 변수
	for (int x = N - D; x < N; x++) {
		for (int y = p.y - D + 1; y < p.y + D; y++) {
			if (0 <= y && y < M && cpy[x][y]) {	// 탐색 범위에 적이 존재
				int temp = abs(p.x - x) + abs(p.y - y);	// 적과의 거리 계산
				if (tempD > temp) {	// 사거리 D 이내 또는 더 가까운 적인 경우
					ret = { x, y };	// 적 위치 저장
					tempD = temp;	// 해당 적과의 거리 저장
				}
				else if (tempD == temp && y < ret.y)	// 같은 거리에서 더 왼쪽의 적 발견
					ret = { x, y };	// 해당 적 위치 저장
			}
		}
	}
	return ret;	// 탐색 결과가 존재하지 않는 경우 { -1, -1 } 반환, 존재하는 경우 해당 적의 위치 반환
}

void simulation(void) {
	bool flag = true;	// 적 존재 유무
	int killed = 0;	// 제거한 적의 총합
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cpy[i][j] = map[i][j];
	while (flag) {
		vector<point> v;	// 공격할 적을 저장할 벡터
		flag = false;	// flag 리셋
		for (int i = 0; i < 3; i++) {	// 총 세명의 궁수에 대해
			point p = search(archer[i]);	// 공격할 적 탐색
			if (p.x != -1)	// 탐색 결과 공격 대상이 존재하는 경우
				v.push_back({ p.x, p.y });	// 벡터에 저장 (서로 다른 두 궁수의 타겟이 중복될 수 있음)
		}
		// 공격 가능한 적 제거
		for (int i = 0; i < v.size(); i++) {
			if (cpy[v[i].x][v[i].y]) {	// 해당 위치에 적이 존재하면(중복되는 적인 경우 이미 제거되었을 수 있음)
				cpy[v[i].x][v[i].y] = false;	// 해당 적을 맵에서 제거
				killed++;	// 제거한 적의 수 증가
			}
		}
		// 적 전진
		for (int i = N - 1; i > 0; i--)
			for (int j = 0; j < M; j++) {
				cpy[i][j] = cpy[i - 1][j];
				if (cpy[i][j])	// 적이 아직 존재
					flag = true;	// flag 셋
			}
		for (int j = 0; j < M; j++)	// 가장 윗 줄 초기화
			cpy[0][j] = false;
	}
	ans = max(ans, killed);	//  제거한 적의 최대 수 업데이트
}

void go(int n, int cur) {
	if (n == 3) {
		simulation();
		return;
	}
	for (int i = cur; i < M; i++) {
		archer[n] = { N, i };
		go(n + 1, i + 1);
	}
}

int main(void) {
	// 입력부
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> map[i][j];
	// 처리부
	go(0, 0);
	// 출력부
	setbuf(stdout, NULL);
	printf("%d\n", ans);
	return 0;
}