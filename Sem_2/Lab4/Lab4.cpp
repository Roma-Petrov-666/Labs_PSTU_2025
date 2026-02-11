#include <iostream>
using namespace std;

int main() {
	int N = 100;
	int arr[N];
	
	int n;
	cin>>n;
	if (n > 100) {
	    cout<<"Ошибка размера";
	} else {
	    for (int i=0; i < n; i++) {
	        cin>>arr[i];
	    }
	
	    int k;
	    cin>>k;
	
	    while (k < 0) {
	        k += n;
	    }
	    while (k > n) {
	        k -= n;
	    }
	    for (int i=k; i < n; i++) {
	        cout<<arr[i]<<" ";
	    }
	    for (int i=0; i < k; i++) {
	        cout<<arr[i]<<" ";
	    }
	    cout<<endl;
	
	
	    int a, b;
	    cin>>a>>b;
	    if (n+2 > 100) {
	        cout<<"Ошибка размера";
	    } else {
	        arr[n+1] = b;
	        for (int i=n-1; i >= 0; i--) {
	            arr[i+1] = arr[i];
	        }
	        arr[0] = a;
	        n += 2;
	        
	        int j=0;
	        for (int i=0; i < n; i++) {
	            if (arr[i]%2 == 1) {
	                arr[j++] = arr[i];
	            } else {
	                j;
	            }
	        }
	        n = j;
	        
	        
	        int k;
	        cin>>k;
	
	        while (k < 0) {
	            k += n;
	        }
	        while (k > n) {
	            k -= n;
	        }
	        for (int i=k; i < n; i++) {
	            cout<<arr[i]<<" ";
	        }
	        for (int i=0; i < k; i++) {
	            cout<<arr[i]<<" ";
	        }
	    }
	}
    return 0;
}
