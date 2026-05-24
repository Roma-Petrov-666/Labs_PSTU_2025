#include <iostream>

void counting_sort(int *arr, int size) {
    if (size <= 1) {
        return;
    }

    int max = arr[0];

    for (int i=1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int *cnt = new int[max + 1]{0};
    int *output = new int[size];

    for (int i=0; i < size; i++) {
        cnt[arr[i]]++;
    }

    for (int i=1; i <= max; i++) {
        cnt[i] += cnt[i-1];
    }

    for (int i=size - 1; i >= 0; i--) {
        output[cnt[arr[i]]-1] = arr[i];
        cnt[arr[i]]--;
    }

    for (int i=0; i < size; i++) {
        arr[i] = output[i];
    }

    delete[] cnt;
    delete[] output;
}

int main() {
    int size = 10;
    int arr[size] = {5, 6, 8, 7, 1, 3, 4, 2, 9, 0};

    counting_sort(arr, size);

    for (int i=0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}