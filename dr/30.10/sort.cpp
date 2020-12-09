#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<int> generateVector() {
    srand(time(NULL));
    std::vector<int> tmp(0);
    for (int i = 0; i < 32; ++i) {
        tmp.push_back(random() % 201 - 100);
    }
    return tmp;
}

void show_vector(std::vector<int>& v) {
    for (int &i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

//Odd-Even sort implementation
void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void oddEvenSort(std::vector<int> &x) {
    int sort = 0, i;
    while (!sort) {
        sort = 1;
        for (i = 1;i < x.size();i += 2) {
            if (x[i] > x[i+1]) {
                swap(&x[i], &x[i+1]);
                sort = 0;
            }
        }
        for (i = 0;i < x.size() - 1;i += 2) {
            if (x[i] > x[i + 1]) {
                swap(&x[i], &x[i + 1]);
                sort = 0;
            }
        }
    }
}

// Quick Sort implementation
void quickSort(std::vector<int> &numbers, int left, int right)
{
    int pivot;
    int l_hold = left;
    int r_hold = right;
    pivot = numbers[left];
    while (left < right)
    {
        while ((numbers[right] >= pivot) && (left < right))
            --right;
        if (left != right)
        {
            numbers[left] = numbers[right];
            ++left;
        }
        while ((numbers[left] <= pivot) && (left < right))
            ++left;
        if (left != right)
        {
            numbers[right] = numbers[left];
            --right;
        }
    }
    numbers[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        quickSort(numbers, left, pivot - 1);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right);
}

// Bitonic Sort Implementation
// Битонная сортировка работает только
// с массивами размером равным степени двойки
// это не баг, так и должно быть
void bitonicSeqMerge(std::vector<int> &a, int start, int BseqSize, int direction) {
    if (BseqSize>1){
        int k = BseqSize/2;
        for (int i=start; i<start+k; i++)
            if (direction==(a[i]>a[i+k]))
                std::swap(a[i],a[i+k]);
        bitonicSeqMerge(a, start, k, direction);
        bitonicSeqMerge(a, start+k, k, direction);
    }
}

void bitonicSortrec(std::vector<int> &a,int start, int BseqSize, int direction) {
    if (BseqSize>1){
        int k = BseqSize/2;
        bitonicSortrec(a, start, k, 1);
        bitonicSortrec(a, start+k, k, 0);
        bitonicSeqMerge(a, start, BseqSize, direction);
    }
}

void bitonicSort(std::vector<int> &a) {
    bitonicSortrec(a, 0, a.size(), 1);
}

int main() {
    std::vector<int> oddeven = generateVector();
    std::cout << "Before odd even sort original array\n";
    show_vector(oddeven);
    oddEvenSort(oddeven);
    std::cout << "After odd even sort original array\n";
    show_vector(oddeven);
    std::cout << '\n';

    std::vector<int> quick = generateVector();
    std::cout << "Before quick sort original array\n";
    show_vector(quick);
    oddEvenSort(quick);
    std::cout << "After quick sort original array\n";
    show_vector(quick);
    std::cout << '\n';

    std::vector<int> bitonic = generateVector();
    std::cout << "Before bitonic sort original array\n";
    show_vector(bitonic);
    oddEvenSort(bitonic);
    std::cout << "After bitonic sort original array\n";
    show_vector(bitonic);
    std::cout << '\n';
    return 0;
}