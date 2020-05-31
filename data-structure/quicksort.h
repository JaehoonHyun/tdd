#pragma once


int partition(int *arr, int low, int high) {
	
	int pivot;

	//첫번째를 pivot으로 잡는다.
	pivot = arr[low];
	
	do {


	} while (low < high);


}

void quicksort(int *arr, int low, int high) {

	if (low < high) {
		int pi = partition(arr, low, high);

		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

//quicksort(arr,fisrtidx,lastindex)