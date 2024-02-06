#include "the1.h"

void swap_elements(unsigned short& first, unsigned short& second) {
    unsigned short temp = first;
    first = second;
    second = temp;
}

int max_int(int first, int second) {
    return (first >= second) ? first : second;
}

double absolute(double first) {
    return (first >= 0) ? first : -first;
}

int lomuto(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int size) {
    unsigned short x = arr[size - 1];
    int i = -1;
    int total_swap = 0;
    double total_distance = 0;
    for (int j = 0; j < size-1; j++) {
        if (arr[j] >= x) {
            i++;
            swap_elements(arr[i], arr[j]);
            total_distance += absolute(i - j);
            total_swap++;
            max_dist = max_int(max_dist, absolute(i - j));
        }
    }
    swap_elements(arr[i+1], arr[size - 1]);
    total_distance += absolute(i+1 -(size-1));
    total_swap++;
    avg_dist = (avg_dist * swap + total_distance) / (swap + total_swap);
    swap += total_swap;
    max_dist = max_int(max_dist, absolute(i+1 - (size - 1)));
    
    return i+1;
}

int hoare_func(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, int size) {
    unsigned short x = arr[(size - 1) / 2];
    int i = -1;
    int j = size;
    while (true) {
        do {j--; } while (arr[j] < x);
        do {i++; } while (arr[i] > x);
        if (i < j) {
            swap_elements(arr[i], arr[j]);
            avg_dist = (avg_dist * swap + absolute(i - j)) / (swap+1);
            swap++;
            max_dist = max_int(max_dist, absolute(i - j));
        } 
        else return j;
    }
}

int medianIndexOfThree(unsigned short* arr, int size) {
    unsigned short first = arr[0];
    unsigned short middle = arr[(size-1)/2];
    unsigned short last = arr[size-1];
    
    if ((first > middle && first < last) || (first > last && first < middle)) return 0;
    else if ((middle > first && middle < last) || (middle > last && middle < first)) return (size-1)/2;
    else if ((last > first && last < middle) || (last > middle && last < first)) return size-1;
    else return -1;
    
}


int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size) {
    if (size <= 1) {
        return 1;
    }
    
    int recursion_count = 0;
    int p;
    

    if (hoare) { //pivot is the middle element
        if (median_of_3 && size > 2){
            int medianIndex = medianIndexOfThree(arr, size);
            if (medianIndex != -1 && medianIndex != (size-1)/2){
                swap_elements(arr[medianIndex], arr[(size-1)/2]);
                avg_dist = (avg_dist * swap + absolute((size-1)/2 - medianIndex)) / (swap+1);
                swap++;
                max_dist = max_int(max_dist, absolute((size-1)/2 - medianIndex));
            }
        }
        p = hoare_func(arr, swap, avg_dist, max_dist, size);
        recursion_count += quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, p+1);
        recursion_count += quickSort(arr + p + 1, swap, avg_dist, max_dist, hoare, median_of_3, size - p - 1);
    } 
    
    else { //pivot is the last element
        if (median_of_3 && size > 2){
            int medianIndex = medianIndexOfThree(arr, size);
            if (medianIndex != -1 && medianIndex != size-1){
                swap_elements(arr[medianIndex], arr[size-1]);
                avg_dist = (avg_dist * swap + absolute(size-1 - medianIndex)) / (swap+1);
                swap++;
                max_dist = max_int(max_dist, absolute(size-1 - medianIndex));
            }
        }
        p = lomuto(arr, swap, avg_dist, max_dist, size);
        recursion_count += quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, p);
        recursion_count += quickSort(arr + p + 1, swap, avg_dist, max_dist, hoare, median_of_3, size - p - 1);
    }
    return recursion_count + 1;
}











