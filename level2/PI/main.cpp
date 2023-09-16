#include <iostream>
#include <vector>
using namespace std;

// 大整数类
class BigInteger {
    // 存储大整数的数字
        public:
        BigInteger() {}

        // 创建指定位数的大整数
        BigInteger(int n) {
            digits.assign(n, 0);
        }

        // 大整数加法
        BigInteger add(BigInteger b) {
            BigInteger c;
            int carry = 0;
            for (int i = 0; i < digits.size() || i < b.digits.size(); i++) {
                int d1 = i < digits.size() ? digits[i] : 0;
                int d2 = i < b.digits.size() ? b.digits[i] : 0;
                int sum = d1 + d2 + carry;
                c.digits.push_back(sum % 10);
                carry = sum / 10;
            }
            if (carry > 0) {
                c.digits.push_back(carry);
            }
            return c;
        }

        // 大整数减法
        BigInteger subtract(BigInteger b) {
            BigInteger c;
            int borrow = 0;
            for (int i = 0; i < digits.size(); i++) {
                int d1 = digits[i];
                int d2 = i < b.digits.size() ? b.digits[i] : 0;
                int diff = d1 - d2 - borrow;
                if (diff < 0) {
                    diff += 10;
                    borrow = 1;
                } else {
                    borrow = 0;
                }
                c.digits.push_back(diff);
            }
            // 去除前导0
            while (c.digits.size() > 1 && c.digits.back() == 0) {
                c.digits.pop_back();
            }
            return c;
        }

        // 大整数乘法
        BigInteger multiply(BigInteger b) {
            BigInteger c;
            c.digits.assign(digits.size() + b.digits.size(), 0);
            for (int i = 0; i < digits.size(); i++) {
                int carry = 0;
                for (int j = 0; j < b.digits.size(); j++) {
                    int temp = digits[i] * b.digits[j] + carry;
                    int pos = i + j;
                    carry = temp / 10;
                    c.digits[pos] += temp % 10;
                }
                if (carry > 0) {
                    c.digits[i + b.digits.size()] += carry;
                }
            }
            // 去除前导0
            while (c.digits.size() > 1 && c.digits.back() == 0) {
                c.digits.pop_back();
            }
            return c;
        }

        // 输出大整数
        void print() {
            for(int i = digits.size() - 1; i >= 0; i--) {
                cout << digits[i];
            }
            cout << endl;
        }

    vector<int> digits;
};

// 计算圆周率前n位
BigInteger calcPi(int n) {
    BigInteger x(n);
    BigInteger pi(n);
    for(int i = 0; i < n; i++) {
        x.digits[0] = 1;
        x.digits.resize(1);

        BigInteger tmp = x;
        if (i % 2 == 1) {
            tmp = pi.subtract(tmp);
        } else {
            tmp = pi.add(tmp);
        }
        pi = tmp;
    }
    return pi;
}

int main() {
    int n = 10000;
    BigInteger pi = calcPi(n);
    pi.print();
    return 0;
}