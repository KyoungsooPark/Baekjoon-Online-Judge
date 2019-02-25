/*
https://www.acmicpc.net/problem/1759
문제:
	바로 어제 최백준 조교가 방 열쇠를 주머니에 넣은 채 깜빡하고 서울로 가 버리는
	황당한 상황에 직면한 조교들은, 702호에 새로운 보안 시스템을 설치하기로 하였다.
	이 보안 시스템은 열쇠가 아닌 암호로 동작하게 되어 있는 시스템이다.
	
	암호는 서로 다른 L개의 알파벳 소문자들로 구성되며 최소 한 개의 모음과 최소 두 개의 자음으로
	구성되어 있다고 알려져 있다. 또한 정렬된 문자열을 선호하는 조교들의 성향으로 미루어 보아
	암호를 이루는 알파벳이 암호에서 증가하는 순서로 배열되었을 것이라고 추측된다.
	즉, abc는 가능성이 있는 암호이지만 bac는 그렇지 않다.
	
	새 보안 시스템에서 조교들이 암호로 사용했을 법한 문자의 종류는 C가지가 있다고 한다.
	이 알파벳을 입수한 민식, 영식 형제는 조교들의 방에 침투하기 위해 암호를 추측해 보려고 한다.
	C개의 문자들이 모두 주어졌을 때, 가능성 있는 암호들을 모두 구하는 프로그램을 작성하시오.

입력:
	첫째줄에 두 정수 L, C가 주어진다. (3 ≤ L ≤ C ≤ 15)
	다음 줄에는 C개의 문자들이 공백으로 구분되어 주어진다.
	주어지는 문자들은 알파벳 소문자이며, 중복되는 것은 없다.

출력:
	각 줄에 하나씩, 사전식으로 가능성 있는 암호를 모두 출력한다.

예제 입력:
	4 6
	a t c i s w

예제 출력:
	acis
	acit
	aciw
	acst
	acsw
	actw
	aist
	aisw
	aitw
	astw
	cist
	cisw
	citw
	istw
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// password가 유효한지 check
int isvalid(string password) {
	int ja = 0, mo = 0;
	for (char x : password) {
		if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u')
			mo++;
		else
			ja++;
	}
	return ja >= 2 && mo >= 1;
}

/*
a		: 사용할 수 있는 알파벳 (입력)
l		: 만들어야 하는 암호의 길이 (입력)
password: 현재까지 만든 암호
i		: 사용할지 말지 결정해야 하는 알파벳의 인덱스
*/
void go(vector<char> &a, string password, int l, int i) {
	// 모든 탐색을 마친 경우
	if (i == a.size()) {
		// 암호가 유효한 경우
		if (password.length() == l && isvalid(password)) {
			cout << password << endl;
		}
		return;
	}

	// 다음 경우 호출
	go(a, password + a[i], l, i + 1); // 현재 인덱스의 알파벳을 사용하는 경우
	go(a, password, l, i + 1); // 현재 인덱스의 알파벳을 사용 안하는 경우
}

int main(void) {
	int l, c;
	cin >> l >> c;
	vector<char> a(c);
	for (int i = 0; i < c; i++)
		cin >> a[i];
	sort(a.begin(), a.end());
	go(a, "", l, 0);

	return 0;
}

//#include <iostream>
//#include <algorithm>
//#include <string>
//using namespace std;
//
//int isvalid(string password) {
//	int ja = 0, mo = 0;
//	for (char x : password) {
//		if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u')
//			mo++;
//		else
//			ja++;
//	}
//	return ja >= 2 && mo >= 1;
//}
//
//void go(char a[], int n, string password, int l, int i) {
//	if (i == n) {
//		if (password.length() == l && isvalid(password))
//			cout << password << endl;
//		return;
//	}
//	go(a, n, password + a[i], l, i + 1);
//	go(a, n, password, l, i + 1);
//}
//
//int main(void) {
//	int l, n;
//	char a[15];
//	cin >> l >> n;
//	for (int i = 0; i < n; i++)
//		cin >> a[i];
//	sort(a, a + n);
//	go(a, n, "", l, 0);
//	return 0;
//}