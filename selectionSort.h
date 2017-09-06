#ifndef SELECT_SORT_H
#define SELECT_SORT_H

template<class T>
void mySwap(T &x, T &y) {
	T temp = x;
	x = y;
	y = temp;
}

template<class T>
void selectionSort(T a[], int n) {
	for (int i = 0;i < n - 1;i++) {
		int leastIndex = i;
		for (int j = i + 1;j < n;j++)
			if (a[j] > a[leastIndex])
				leastIndex = j;
		mySwap(a[i], a[leastIndex]);
	}
}
#endif
