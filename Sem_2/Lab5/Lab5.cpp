#include <iostream>
using namespace std;

const int Max_Size = 5;

void FindMaxelem(int matrix[][Max_Size], int left, int right, int n, int *x, int *y) {
    int max = matrix[right][n-left+1];
    *x = right;
    *y = n-left+1;
    for (int i=right; i <= left; i++) {
        for (int j=n-left+1; j <=n-right+1; j++) {
            if (matrix[i][j] > max) {
                max = matrix[i][j];
                *x = i;
                *y = j;
            }
        }
    }
}

void MaxelemSort(int matrix[][Max_Size], int left, int right, int n) {
    int x, y;
    FindMaxelem(matrix, left, right, n, &x, &y);
    
    int tmp;
    for (int i=0; i <= left-right+1; i++) {
        tmp = matrix[x][i];
        matrix[x][i] = matrix[right][i];
        matrix[right][i] = tmp;
    }
    for (int i=0; i <= left-right; i++) {
        tmp = matrix[i][y];
        matrix[i][y] = matrix[i][n-right+1];
        matrix[i][n-right+1] = tmp;
    }
}

void Submatrices(int matrix[][Max_Size], int n) {
    for (int k=2; k <= n; k++) {
        for (int i=k-1; i < n; i++) {
            MaxelemSort(matrix, i, i-k+1, n);
        }
    }
}

int main() {
	const int N=5;
	//cin>>N;
	int arr[N][N];
	
	for (int i=0; i < N; i++) {
	    for (int j=0; j < N; j++) {
	        cin>>arr[i][j];
	    }
	}
	
    Submatrices(arr, N);
    
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            cout<<arr[i][j]<<"\t";
        }
        cout<<endl;
    }
	
    return 0;
}