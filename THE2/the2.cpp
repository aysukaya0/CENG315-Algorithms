#include "the2.h"

int counting_sort(std::string* arr, int size, int n) {
    int k = 27;
    int* c = new int[k];
    int iterations = 0;
    std::string* result = new std::string[size];

    for (int i = 0; i < k; i++) {
        c[i] = 0;
    }

    for (int j = 0; j < size; j++) {
        if (arr[j].length() <= n) {
            c[0]++;
        } 
        else {
            c[arr[j][n] - 'A' + 1]++;
        }
        iterations++;
    }

    for (int i = 1; i < k; i++) {
        c[i] = c[i] + c[i - 1];
        iterations++;
    }

    for (int j = size - 1; j >= 0; j--) {
        if (arr[j].length() <= n) {
            result[c[0]-1] = arr[j];
            c[0]--;
        } 
        else {
            int index = arr[j][n] - 'A' + 1;
            result[c[index]-1] = arr[j];
            c[index]--;
        }
        iterations++;
        
    }

    for (int i = 0; i < size; i++) {
        arr[i] = result[i];
        iterations++;
    }

    delete[] c;
    delete[] result;

    return iterations;
}

int radix_string_sort(std::string* arr, int size, bool ascending) {
    int iterations = 0;

    int n = 0;
    for (int i = 0; i < size; i++) {
        int length = arr[i].length();
        if (length > n) {
            n = length;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        iterations += counting_sort(arr, size, i);
    }

    if (!ascending) {
        for (int i = 0, j = size - 1; i < size / 2; i++, j--) {
            std::string temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    return iterations;
}
