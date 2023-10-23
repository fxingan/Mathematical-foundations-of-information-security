#include<iostream>
using namespace std;
int gcd(int n, int m) {
	while (1) {
		int a = n % m;
		if (a == 0) {
			break;
		}
		else {
			n = m;
			m = a;
		}
	}
	return m;
}
int caltulate(int n, int m) {
	int x = m, y = 1, z = 0;
	int r = n, s = 0, t = 1;
	int p, tmpe;
	while (r > 0) {
		p = x / r;
		tmpe = t;
		t = z - p * t;
		z = tmpe;
		tmpe = r;
		r = x - p * r;
		x = tmpe;
	}
	return z;
}
int main() {
	int a, b;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	int z1 = caltulate(a, b);
	//int z2 = caltulate(b, a);
	int x = gcd(a, b);
	//cout << "gcd(" << a << ',' << b << ") = " << x << endl;
	//cout << "lcm(" << a << ',' << b << ") = " << a*b/x << endl;
	if (x == 1) {
		if (z1 >= 0) {
			//cout << a << "mod(" << b << ")的逆元为" << z1 << endl;
			cout << z1;
		}
		else {
			z1 = b + z1;
			//cout << a << "mod(" << b << ")的逆元为" << z1 << endl;
			cout << z1;
		}
	}
	else {
		cout << a << "mod(" << b << ")无逆元" << endl;
	}
	/*if (x == 1) {
		if (z2 >= 0) {
			cout << b << "mod(" << a << ")的逆元为" << z2 << endl;
		}
		else {
			z2 = a + z2;
			cout << b << "mod(" << a << ")的逆元为" << z2 << endl;
		}
	}
	else {
		cout << b << "mod(" << a << ")无逆元" << endl;
	}
	system("pause");*/
	return 0;
}
