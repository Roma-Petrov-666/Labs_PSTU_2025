#include iostream
using namespace std;

void hanoi(int n, int start, int point, int tmp) {
	if (n == 0) return;
	hanoi(n - 1, start, tmp, point);
	cout  start   =   point  endl;
	hanoi(n - 1, tmp, point, start);
}

int main() {
	hanoi(3, 1, 3, 2);

}
