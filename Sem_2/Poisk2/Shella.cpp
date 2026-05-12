#include <iostream>

void shellSort(int arr[], int size) {
	for (int step = size/2; step > 0; step /= 2) {
		for (int i=step; i < size; i++) {
			int temp = arr[i];
			int j;
			for (j=i; j >= step && arr[j-step] > temp; j -= step) {
				arr[j] = arr[j-step];
			}
			arr[j] = temp;
		}
	}
}


int main() {
	int size;
	std::cin >> size;

	int arr[size];
	for(int i=0; i < size; i++) {
	    std::cin >> arr[i];
	}
    
	shellSort(arr, size);
	
	for(int i=0; i < size; i++) {
	    std::cout << arr[i] << " ";
	}
	
	return 0;
}