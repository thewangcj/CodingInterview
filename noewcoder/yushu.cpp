#include <iostream>
#include <string>
using namespace std;

// 输入两个数，第一个表示进制，第二个表示被除数，
// 然后输入除数（0-z）
// 输出余数
int main(int argc, char const *argv[])
{
	int n, m;
	char limit;
	string num;
	cin >> n >> m;
	if(n <= 10) {
		limit = n + 49;
	} else {
        limit = n - 10 + 96;
	}

	cin >> num;
    auto it = num.begin();
    for(it; it != num.end(); it++) {
        if(*it > limit) {
            cout << *it << endl;
            cout << 0 << endl;
            return 0;
        }
    }

    int dig_num = 0;
    int base = 1;
    for(auto it = num.rbegin(); it != num.rend(); it++) {
        if(*it <= '9') {
            dig_num += (*it - '0') * base;
        } else {
            dig_num += (*it - 'a' + 10) * base;
        }

        base *= n;
    }
    cout << dig_num << endl;
    cout << (dig_num % m) << endl;

	return 0;
}
