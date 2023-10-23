#include <iostream>
using namespace std;
int main() {
	int n, m, a;
	cout << "n=";
	cin >> n;
	cout << "m=";
	cin >> m;
	int x = n * m;
	while (1) {
		a = n % m;
		if (a == 0) {
			break;
		}
		else {
			n = m;
			m = a;
		}
	}
	int y = x / m;
	cout << "gcd(n,m)=" << m << endl;
	cout << "lcm(n,m)=" << y << endl;
	system("pause");
	return 0;
}