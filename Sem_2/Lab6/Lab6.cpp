#include <iostream>
#include <string>
using namespace std;

int CountWords(string str) {
    int counter=0;
    for (int i=1; i < str.length(); i++) {
        if (str[i] == ' ' && str[i-1] != ' ') {counter++;}
    }
    
    if (str[str.length()-2] == ' ') {
        return counter;
    }
    else {
        return counter+1;
    }
}

void Split(string arr[], string str) {
    int i=0;
    if (str[0] != ' ') { arr[i] += str[0]; }
    for (int j=1; j < str.length(); j++) {
        if (str[j] != ' ') {
            arr[i] += str[j];
        } else if (str[j-1] != ' ') {i++;}
    }
}

void Sort(string arr[], int n) {
    string tmp;
    
    for(int i=0; i < n-1; i++) {
        for (int j=0; j < n-j-1; j++) {
            if (arr[j] > arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main() {
	string str;
    getline(cin, str);
    str[str.length()-1] = ' ';

    const int n = CountWords(str);
    string arr[n];
    Split(arr, str);
    Sort(arr, n);
    
    string str_ans;
    for (int i=0; i < n; i++) {
        str_ans += arr[i] + ' ';
    }
    str_ans[str_ans.length()-1] = '.';
    
    cout<<str_ans;
    
    return 0;
}
