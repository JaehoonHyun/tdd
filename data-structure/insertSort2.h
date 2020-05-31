#pragma once
void insertSort(int list[], int n) {
	int i, j, key;

	for (i = 1; i < n; i++) {

		key = list[i];

		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j];
		}

		list[j + 1] = key;
	}

	// 8 5 6
}

void insertSort2(int list[], int n) {

	int i, j, key;

	for (i = 1; i < n; i++) {

		key = list[i];

		for (j = i - 1; j >= 0 && list[j] > key; j--) {
			list[j + 1] = list[j];
		}

		list[j + 1] = key;
	}
}