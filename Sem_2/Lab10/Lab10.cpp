#include <iostream>
#include <string>

using namespace std;

string randomString(int minLen = 3, int maxLen = 8) {
    int len = rand() % (maxLen - minLen + 1) + minLen;
    string s;
    for (int i = 0; i < len; i++) {
        char c = 'a' + rand() % 26;
        s.push_back(c);
    }
    return s;
}

int main() {
	int n;
	cin>>n;

	string* arr = new string[n];

	for (int i=0; i < n; i++) {
		arr[i] = randomString();
	}
	
	
	int newSize=0;
    for (int i=0; i < n; i++) {
        if (arr[i][0] != 'a') {
            newSize++;
        }
    }
    
    
    string* result = new string[newSize];
    if (newSize > 0) {
        int idx=0;
        for (int i=0; i < n; i++) {
            if (arr[i][0] != 'a') {
                result[idx++] = arr[i];
            }
        }
    }
    

    if (newSize == 0) {
        cout << "Все строки начинались на 'a'. Массив пуст.";
    } else {
        for (int i=0; i < newSize; i++) {
            cout<<result[i]<<" ";
        }
    }
    
    
    delete[] arr;
    delete[] result;
    
    
    return 0;
}