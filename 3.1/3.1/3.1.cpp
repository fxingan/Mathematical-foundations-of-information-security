#include<iostream>
using namespace std;
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
	cout << "n=";
	int n;
	cin >> n;
	int* b = new int[n];
	int* m = new int[n];
	int* M = new int[n];
	int* x = new int[n];//存放逆元
	int i = 0;
	int sum = 1;
	for (i = 0; i < n; i++) {
		cout << "b_" << i << "=" ;
		cin >> b[i] ;
	}
	for (i = 0; i < n; i++) {
		cout << "m_" << i << "=" ;
		cin >> m[i];
		sum *= m[i];
		M[i] = 1;
	}
	for (i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				M[i] *= m[j];
			}
		}
	}
	for (i = 0; i < n; i++) {
		x[i] = caltulate(M[i], m[i]);
	}
	int a = 0;
	for (i = 0; i < n; i++) {
		a += x[i] * M[i] * b[i];
	}
	while (a - sum >= 0) {
		a -= sum;
	}
	cout << "该方程组的解为x≡" << a << " (mod " << sum << ")" << endl;
	system("pause");
	return 0;
}