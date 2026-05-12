#include <iostream>

int partitionHoare(int arr[], int low, int high) {

	int p = (high + low) / 2;
	int pivot = arr[p];
	int i = low - 1;
	int j = high + 1;

	while (true)
	{
		do {
			i++;
		} while (arr[i] < pivot);

		do {
			j--;
		} while (arr[j] > pivot);

		if (i >= j) {
			return j;
		}

		if (p == j) p = i;
		else if (p == i) p = j;

		std::swap(arr[i], arr[j]);
	}
}

void quickSortHoare(int arr[], int low, int high) {
	if (low < high) {
		int p = partitionHoare(arr, low, high);

		quickSortHoare(arr, low, p);
		quickSortHoare(arr, p+1, high);
	}
}

int main() {
	int size;
	std::cin >> size;

	int arr[size];
	for(int i=0; i < size; i++) {
	    std::cin >> arr[i];
	}
    
	quickSortHoare(arr, 0, size-1);
	
	for(int i=0; i < size; i++) {
	    std::cout << arr[i] << " ";
	}
	
	return 0;
}