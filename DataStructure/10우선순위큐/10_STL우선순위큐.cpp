#include <queue>
#include <functional>
#include <iostream>
using namespace std;

void heapSortInc(int a[], int n){
	priority_queue< int, vector<int>, greater<int> > minHeap;
	for(int i=0 ; i<n ; i++){
		minHeap.push(a[i]);
	}

	//MinHeap을 이용해 오름차순으로 정렬하기 위한 반복문
	for(int i=0; i<n; i++){
		a[i] = minHeap.top();
		minHeap.pop();
	}

}


int main() {
	int data[10] = { 10,21,5,76,22,44,21,6,90,1 };
	heapSortInc(data, 10);
	for (int i = 0; i < 10; i++) {
		cout << data[i]<<" ";
	}

}