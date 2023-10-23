#include<iostream>
using namespace std;
int calculate(int a, int b, int mod)
{
	int long long  result = 1; 
	int c[64] = { 0 };
	int length = 0;
	while (b)
	{
		c[length] = b & 1;
		length++;
		b >>= 1;
	}
	for (int j = length - 1; j >= 0; j--)
	{
		if (c[j] == 1)
			result = (result * result * a) % mod;
		else
			result = (result * result) % mod;
	}
	return result;
}

int main()
{
	int a, b, mod;
	int result;
	cout << "Please input: " << endl;
	cin >> a >> b >> mod;
	result = calculate(a, b, mod);
	cout << a << '^' << b << "(mod" << mod << ")" << "=" << result << endl;
	system("pause");
	return 0;
}
