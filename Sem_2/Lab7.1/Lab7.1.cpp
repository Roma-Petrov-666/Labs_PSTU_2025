#include <iostream>
#include <string>

using namespace std;

int func(int arr[], int n) {
    int max = arr[0];
    for (int i=1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return max;
}

int func(string s) {
    int len=0;
    int max_len=0;
    for (int i=0; i < s.length(); i++) {
        if (s[i] != ' ') {
            len++;
        } else {
            if (len > max_len) {
                max_len = len;
            }
            len = 0;
        }
    }
    if (len > max_len) {
        max_len = len;
    }
    
    return max_len;
}

int main() {
	int arr[5] = {1, 2, 3, 4, 5};
	string s = "abc de f ghijkl";
	
    cout<<func(arr, 5)<<endl;
    cout<<func(s)<<endl;
    
    return 0;
}