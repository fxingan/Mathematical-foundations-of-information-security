#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    else {
        return gcd(b, a % b);
    }
}
int mod_pow(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
bool is_primitive_root(int root, int mod) {
    vector<bool> used(mod - 1, false);
    int cur = 1;
    for (int i = 1; i <= mod - 2; i++) {
        cur = (cur * root) % mod;
        if (used[cur - 1]) {
            return false;
        }
        used[cur - 1] = true;
    }
    return true;
}
int acc_f(int mod) {
    int f = mod, temp = mod;
    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            f = f / i * (i - 1);
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    if (temp > 1) {
        f = f / temp * (temp - 1);
    }
    return f;
}
int find_min_primitive_root(int mod) {
    int f = acc_f(mod);
    vector<int> factors;
    int temp = f;
    for (int i = 2; i * i <= temp; i++) {
        if (temp % i == 0) {
            factors.push_back(i);
            while (temp % i == 0) {
                temp /= i;
            }
        }
    }
    if (temp > 1) {
        factors.push_back(temp);
    }
    for (int root = 2; root <= mod; root++) {
        bool flag = true;
        for (int factor : factors) {
            if (mod_pow(root, f / factor, mod) == 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return root;
        }
    }
    return -1;
}
void print_ind_table(int root, int mod) {
    cout << " ind_table " << root << " mod " << mod << ":" << endl;
    int rows = mod / 10 + 2;
    int cols = 11;
    vector<vector<int>> table(rows, vector<int>(cols, -1));
    for (int i = 0; i < acc_f(mod); i++) {
        int j = mod_pow(root, i, mod);
        int row = j / 10 + 1;
        int col = j % 10 + 1;
        table[row][col] = i;
    }
    for (int i = 0; i < 10; i++) {
        table[0][i + 1] = i;
    }
    for (int i = 0; i < mod / 10 + 1; i++) {
        table[i + 1][0] = i;
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (table[row][col] == -1) {
                cout << "     ";
            }
            else {
                cout << setw(5) << table[row][col];
            }
        }
        cout << endl;
    }
}

int main() {
    int mod;
    cout << " Input a number: ";
    cin >> mod;
    int root = find_min_primitive_root(mod);
    if (root == -1) {
        cout << " There is no primitive root modulo " << mod << endl;
    }
    else if (root > 1) {
        cout << " The smallest primitive root modulo " << mod << " is " << root << endl;
        print_ind_table(root, mod);
    }
    else {
        cout << mod << " is not a prime and does not have a primitive root." << endl;
    }
    system("pause");
    return 0;
}