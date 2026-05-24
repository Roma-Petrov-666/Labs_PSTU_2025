#include <iostream>

void bucket_sort(int *arr, int size) {
    if (size <= 1) return;

    const int bucketNum = 10;
    const int bucketSize = 100;
    int buckets[bucketNum][bucketSize];
    int bucketSizes[bucketNum] = {0};

    int max = arr[0];
    for (int i=1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    for (int i=0; i < size; i++) {
        int bucket_idx = (bucketNum * arr[i])/(max + 1);
        
        if (bucketSizes[bucket_idx] < bucketNum) {
            buckets[bucket_idx][bucketSizes[bucket_idx]] = arr[i];
            bucketSizes[bucket_idx]++;
        }
    }

    for (int i=0; i < bucketNum; i++) {
        for (int j=1; j < bucketSizes[i]; j++) {
            int tmp = buckets[i][j];
            int k = j - 1;

            while(k >= 0 && buckets[i][k] > tmp) {
                buckets[i][k + 1] = buckets[i][k];
                k--;
            }
            buckets[i][k + 1] = tmp;
        }
    }

    int idx = 0;
    for (int i=0; i < bucketNum; i++) {
        for (int j=0; j < bucketSizes[i]; j++) {
            arr[idx++] = buckets[i][j];
        }
    }
}

int main() {
    int size = 10;
    int arr[size] = {5, 6, 8, 7, 1, 3, 4, 2, 9, 0};

    bucket_sort(arr, size);

    for (int i=0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}