#include <iostream>

void merge(int * arr, int left, int mid, int right) {
    int left_r = mid - left + 1;
    int right_r = right - mid;

    int *left_arr = new int[left_r];
    int *right_arr = new int[right_r];

    for (int i=0; i < left_r; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int i=0; i < right_r; i++) {
        right_arr[i] = arr[mid + i + 1];
    }

    int left_idx = 0;
    int right_idx = 0;
    int merge_idx = left;

    while (left_idx < left_r && right_idx < right_r) {
        if (left_arr[left_idx] <= right_arr[right_idx]) {
            arr[merge_idx] = left_arr[left_idx];
            left_idx++;
        }
        else {
            arr[merge_idx] = right_arr[right_idx];
            right_idx++;
        }
        merge_idx++;
    }

    while(left_idx < left_r) {
        arr[merge_idx] = left_arr[left_idx];
        left_idx++;
        merge_idx++;
    }

    while(right_idx < right_r) {
        arr[merge_idx] = right_arr[right_idx];
        right_idx++;
        merge_idx++;
    }

    delete[] left_arr;
    delete[] right_arr;
}

void merge_sort(int *arr, int start, int end) {
    if (start >= end) return;

    int mid = (start + end)/2;

    merge_sort(arr, start, mid);
    merge_sort(arr, mid + 1, end);
    merge(arr, start, mid, end);
}

int main() {
    int size = 10;
    int arr[size] = {5, 6, 8, 7, 1, 3, 4, 2, 9, 0};

    merge_sort(arr, 0, size-1);

    for (int i=0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}