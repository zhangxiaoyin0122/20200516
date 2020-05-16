#include <iostream>
using namespace std;

int& add1(int& a) {
	return ++a;
}
int& add2(int a) {
	return ++a;
}

void test() {
	int a = 1;
	int& b = add1(a);
	int& c = add2(a);
	cout << b << endl;
	cout << c << endl;
}
//计数排序
void countSort(int* array, int n) {
	int min = array[0], max = array[0];
	for (int i = 0; i < n; i++) {
		if (min > array[i])
			min = array[i];
		if (max < array[i])
			max = array[i];
	}
	int range = max - min + 1;
	int* tmp = (int*)malloc(sizeof(int)*range);
	memset(tmp, 0, sizeof(int)*range);
	//计数
	for (int i = 0; i < n; i++) {
		tmp[array[i] - min]++;
	}
	int idx = 0;
	//恢复数组
	for (int i = 0; i < range; i++) {
		while (tmp[i]--) {
			array[idx++] = i + min;
		}
	}
	free(tmp);
}
//合并
void merge(int* array, int begin,int mid, int end, int* tmp) {
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	int idx = begin;
	while (begin1 <= end1 && begin2 <= end2) {
		if (array[begin1] < array[begin2])
			tmp[idx++] = array[begin1++];
		else
			tmp[idx++] = array[begin2++];
	}
	if (begin1 <= end1)
		memcpy(tmp + idx, array + begin1, sizeof(int)*(end1 - begin1 + 1));
	if (begin2 <= end2)
		memcpy(tmp + idx, array + begin2, sizeof(int)*(end2 - begin2 + 1));
	memcpy(array + begin, tmp + begin, sizeof(int)*(end - begin + 1));
}
//利用递归分解
void mergeSortR(int* array, int begin, int end, int* tmp) {
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;
	mergeSortR(array, begin, mid, tmp);
	mergeSortR(array, mid + 1, end, tmp);
	merge(array, begin, mid, end, tmp);
}
void mergeSort(int* array, int n) {
	int* tmp = (int*)malloc(sizeof(int)*n);
	mergeSortR(array, 0, n - 1, tmp);
	free(tmp);
}
void mergeSortNor(int* array, int n) {
	int* tmp = (int*)malloc(sizeof(int)*n);
	int k = 1;
	while (k < n) {
		for (int i = 0; i < n; i +=2*k) {
			int begin = i;
			int mid = i + k - 1;
			if (mid >=n-1)
				continue;
			int end = i + 2 * k - 1;
			if (end > n - 1)
				end = n - 1;
			merge(array, begin, mid, end, tmp);
		}
		k *= 2;
	}
	free(tmp);
}
void test1() {
	int array[] = { 10, 6 ,9,4,2,4,3,6,8,5 };
	int size = sizeof(array) / sizeof(array[0]);
	//countSort(array, size);
	mergeSortNor(array, size);
	for (int i = 0; i < size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}
int main() {
	test1();
	return 0;
}