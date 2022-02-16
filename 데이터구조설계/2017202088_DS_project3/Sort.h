#pragma once
#include <vector>
#include <iostream>
using namespace std;

void insert(const int& e, vector<int>& array, int left, int i) {
	while (i >= left && e < array[i]) {
		array[i + 1] = array[i];
		i--;
	}
	array[i + 1] = e;
}

void insertionSort(vector<int>& array, const int left, const int right) {
	for (int j = left + 1; j < right; j++) {
		int temp = array[j];
		insert(temp, array, left, j - 1);
	}
}

void quickSort(vector<int>& array, int left, int right) {
	if (left < right) {
		if (right - left < 6)
			insertionSort(array, left, right);
		else {
			int i = left;
			int j = right;
			int pivot = array[left];
			do {
				do i++; while (array[i] < pivot);
				do j--; while (array[j] > pivot);
				if (i < j) {
					int temp = array[i];
					array[i] = array[j];
					array[j] = temp;
				}
			} while (i < j);
			int temp = array[left];
			array[left] = array[j];
			array[j] = temp;

			quickSort(array, left, j);
			quickSort(array, j + 1, right);
		}
	}
}