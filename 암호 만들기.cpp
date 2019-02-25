/*
https://www.acmicpc.net/problem/1759
����:
	�ٷ� ���� �ֹ��� ������ �� ���踦 �ָӴϿ� ���� ä �����ϰ� ����� �� ������
	Ȳ���� ��Ȳ�� ������ ��������, 702ȣ�� ���ο� ���� �ý����� ��ġ�ϱ�� �Ͽ���.
	�� ���� �ý����� ���谡 �ƴ� ��ȣ�� �����ϰ� �Ǿ� �ִ� �ý����̴�.
	
	��ȣ�� ���� �ٸ� L���� ���ĺ� �ҹ��ڵ�� �����Ǹ� �ּ� �� ���� ������ �ּ� �� ���� ��������
	�����Ǿ� �ִٰ� �˷��� �ִ�. ���� ���ĵ� ���ڿ��� ��ȣ�ϴ� �������� �������� �̷�� ����
	��ȣ�� �̷�� ���ĺ��� ��ȣ���� �����ϴ� ������ �迭�Ǿ��� ���̶�� �����ȴ�.
	��, abc�� ���ɼ��� �ִ� ��ȣ������ bac�� �׷��� �ʴ�.
	
	�� ���� �ý��ۿ��� �������� ��ȣ�� ������� ���� ������ ������ C������ �ִٰ� �Ѵ�.
	�� ���ĺ��� �Լ��� �ν�, ���� ������ �������� �濡 ħ���ϱ� ���� ��ȣ�� ������ ������ �Ѵ�.
	C���� ���ڵ��� ��� �־����� ��, ���ɼ� �ִ� ��ȣ���� ��� ���ϴ� ���α׷��� �ۼ��Ͻÿ�.

�Է�:
	ù°�ٿ� �� ���� L, C�� �־�����. (3 �� L �� C �� 15)
	���� �ٿ��� C���� ���ڵ��� �������� ���еǾ� �־�����.
	�־����� ���ڵ��� ���ĺ� �ҹ����̸�, �ߺ��Ǵ� ���� ����.

���:
	�� �ٿ� �ϳ���, ���������� ���ɼ� �ִ� ��ȣ�� ��� ����Ѵ�.

���� �Է�:
	4 6
	a t c i s w

���� ���:
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

// password�� ��ȿ���� check
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
a		: ����� �� �ִ� ���ĺ� (�Է�)
l		: ������ �ϴ� ��ȣ�� ���� (�Է�)
password: ������� ���� ��ȣ
i		: ������� ���� �����ؾ� �ϴ� ���ĺ��� �ε���
*/
void go(vector<char> &a, string password, int l, int i) {
	// ��� Ž���� ��ģ ���
	if (i == a.size()) {
		// ��ȣ�� ��ȿ�� ���
		if (password.length() == l && isvalid(password)) {
			cout << password << endl;
		}
		return;
	}

	// ���� ��� ȣ��
	go(a, password + a[i], l, i + 1); // ���� �ε����� ���ĺ��� ����ϴ� ���
	go(a, password, l, i + 1); // ���� �ε����� ���ĺ��� ��� ���ϴ� ���
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