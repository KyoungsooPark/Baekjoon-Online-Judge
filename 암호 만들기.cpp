/*
https://www.acmicpc.net/problem/1759
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int L, C;
vector<char> v(15);

bool isvalid(string s) {
	int j = 0, m = 0;
	for (char c : s) {
		if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
			m++;	// 모음 개수 증가
		else
			j++;	// 자음 개수 증가
	}
	return j >= 2 && m >= 1;	// 자음 2개 이상, 모음 1개 이상 조건 만족 여부 반환
}

void go(int i, string s) {
	if (i == C) {
		if (s.length() == L && isvalid(s))	// 조합한 암호가 길이와 자음, 모음 조건을 만족
			cout << s << endl;	// 가능성 있는 암호 출력
		return;
	}
	go(i + 1, s + v[i]);	// i번째 알파벳 선택
	go(i + 1, s);	// i번째 알파벳 탈락
}

int main(void) {
	// 입력부
	cin >> L >> C;
	for (int i = 0; i < C; i++)
		cin >> v[i];

	// 처리부
	sort(v.begin(), v.begin() + C);
	go(0, "");

	return 0;
}
