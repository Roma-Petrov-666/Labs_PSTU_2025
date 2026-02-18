#include <iostream>
using namespace std;

int NOD(int n, int m) {
	if (n == m) {return n};
	if (n > m) {return NOD(n - m, m)};
	return NOD(n, m - n);
}

int main() {
	cout << " NOD(10, 3)" << NOD(11, 3) << endl;
}