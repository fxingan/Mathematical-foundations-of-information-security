#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
};

class Curve {
private:
    int p; // 模数
    int a, b; // 参数

public:
    Curve(int p, int a, int b) {
        this->p = p;
        this->a = a;
        this->b = b;
    }

    // 判断是否为椭圆曲线
    bool isCurve() {
        int term1 = 4 * (a * a * a);
        int term2 = 27 * (b * b);
        return (term1 + term2) % p != 0;
    }

    // 判断点是否在椭圆曲线上
    bool isPointOnCurve(int x, int y) {
        int term1 = (y * y);
        int term2 = (x * x * x);
        return (term1 - term2 - a * x - b) % p == 0;
    }

    // 点的相加操作
    long long int mod(unsigned long long int a, long long int q)  //求a^q modp
    {
        unsigned long long int y;

        //使用二进制平方乘法计算 pow(a,q) % p
        y = 1;

        while (q != 0)
        {
            //对于q中的每个1，累加y

            if (q & 1)
                y = (y * a) % p;
            //对于q中的每一位，计算a的平方
            a = (a * a) % p;
            //准备q中的下一位
            q = q >> 1;
        }

        return (long long int)y;
    }

    Point addition(Point p1, Point p2) {//x1!=x2
        Point n;
        long long int kk = 0;

        //当pp1 pp2有一个为(-1,-1)
        if (p1.x == -1 && p1.y == -1) {
            return p2;
        }
        else if (p2.x == -1 && p2.y == -1) {
            return p1;
        }

        //两个点都不为(-1,-1)
        else {
            if (p1.x == p2.x) {//两个点横坐标相等

                if ((p1.y + p2.y) % p == 0) {//两个点纵坐标和为0，即pp1+pp2=(-1,-1)
                    n.x = -1;
                    n.y = -1;
                    return n;
                }

                else {
                    //kk=(3*x1^2+a)/(2*y1)  mod p
                    long long int t = 3 * p1.x;
                    t %= p;
                    t *= p1.x;
                    t %= p;
                    t += a;
                    t %= p;
                    kk = t * mod(2 * p1.y, p - 2);
                    kk %= p;
                }
            }

            else {//两个点横坐标不相等
                //kk=(y2-y1)/(x2-x1)  mod p
                long long int t = p2.y - p1.y;
                while (t < 0) {
                    t += p;
                }
                t %= p;
                long long int w = p2.x - p1.x;
                while (w < 0) {
                    w += p;
                }
                w %= p;
                kk = t * mod(w, p - 2);
                kk %= p;
            }
        }
        n.x = kk * kk - p1.x - p2.x;
        while (n.x < 0) {
            n.x += p;
        }
        n.x %= p;
        n.y = -p1.y + kk * (p1.x - n.x);
        while (n.y < 0) {
            n.y += p;
        }
        n.y %= p;
        return n;
    }
    //点乘
    Point Multiplication(const Point& p1, int k) {
        Point p2;
        if (k == 0) {
            p2.x = -1;
            p2.y = -1;
            return p2;
        }
        else {
            long long int i = 0;
            p2.x = -1;
            p2.y = -1;
            Point pp = p2;

            //将k拆分成2的次方的和
            while (k != 0) {

                if (i == 0) {
                    pp = p1;
                }
                else {
                    pp = addition(pp, pp);
                }

                if (k & 1) {
                    p2 = addition(pp, p2);
                }
                k >>= 1;
                i++;
            }
            return p2;
        }
    }
    // 计算椭圆曲线上点P的阶
    int PointOrder(const Point& p1) {
        Point current = p1;
        int order = 1;

        // 重复进行点加法，直到返回无穷远点 O
        while (current.x != -1 || current.y != -1) {
            current = addition(current, p1);
            order++;
        }

        return order;
    }
    void CurvePoints( ) {
        vector<Point> points;
        int order = 0;

        for (int x = 0; x < p; x++) {
            for (int y = 0; y < p; y++) {

                if(isPointOnCurve(x, y)){
                    points.push_back({ x, y });
                    order++;
                }
            }
        }

        // 输出所有点的坐标
        cout << "椭圆曲线上的所有点：" << endl;
        cout << " O " << endl;
        for (const auto& point : points) {
            cout << "(" << point.x << "," << point.y << ")" << endl;
        }

        // 输出椭圆曲线的阶
        cout << "椭圆曲线的阶：" << order+1 << endl;
    }
};

int main() {
    int p, a, b;
    cout << "请输入椭圆曲线的参数 p, a, b：" << endl;
    cin >> p >> a >> b;

    Curve curve(p, a, b);

    if (!curve.isCurve()) {
        cout << "输入的参数不满足椭圆曲线的条件！" << endl;
        return 0;
    }

    Point P, Q, sum, mul;
    

    // 输入点 P 和 Q 的坐标
    cout << "请输入点 P 的坐标：" << endl;
    cin >> P.x >> P.y;
    if (!curve.isPointOnCurve(P.x, P.y)) {
        cout << "P点不在椭圆曲线上！" << endl;
        return 0;
    }

    cout << "请输入点 Q 的坐标：" << endl;
    cin >> Q.x >> Q.y;

    if(!curve.isPointOnCurve(Q.x, Q.y)) {
        cout << "Q点不在椭圆曲线上！" << endl;
        return 0;
    }
    
    // 计算 P+Q
    sum = curve.addition(P, Q);

    // 输出结果
    cout << "P+Q 的坐标为：" << endl;
    cout << "(" << sum.x << "," << sum.y << ")" << endl;

    // 计算 kP
    int k;
    cout << "请输入倍数k" << endl;
    cin >> k;
    mul= curve.Multiplication(P, k);

    //输出结果
    cout << "kP的坐标为：" << endl;
    cout << "(" << mul.x << "," << mul.y << ")" << endl;

    int ord1 = curve.PointOrder(P);
    cout << "P的阶为：" << ord1 << endl;

    curve.CurvePoints();
    system("pause");
    return 0;
}