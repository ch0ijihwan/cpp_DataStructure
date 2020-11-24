#include <iostream>
#define MAX 200
using namespace std;

class HeapNode
{
private:
	int key;

public:
	HeapNode(int k = 0)
	{
		key = 0;
	}
	void setKey(int k)
	{
		key = k;
	}
	int getKey() { return key; }
	void display() { cout << " " << key; }
};

class MaxHeap
{
private:
	HeapNode node[MAX];
	int size;

public:
	MaxHeap() : size(0) {} //일단 size를 0으로 초기화 하고 인덱스 0번째에 값을 안넣어줌.
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX - 1; }
	HeapNode &getParent(int i) { return node[i / 2]; }
	HeapNode &getLeft(int i) { return node[i * 2]; }
	HeapNode &getRight(int i) { return node[i * 2 + 1]; }
	
	void insert(int key){
		if(isFull()) return;
		int i = ++size;//꼭 전위 증가를 해야함.사이즈를 늘려놓고 값을 i에 넣어야 정상 작동
		while(i != 1 && key > getParent(i).getKey()){// i!=1 은 루트노드를 제외한 나머지 노드 일 때.
			node[i] = getParent(i);
			i /= 2;
		}
		node[i].setKey(key);
	}

	HeapNode remove(){
		if(isEmpty()) return NULL;
		HeapNode item = node[1];
		HeapNode last = node[size-1];
		int parent = 1; //부모 1
		int child = 2; //자식 2
		while(child<=size){
			if(child < size && getLeft(parent).getKey() < getRight(parent).getKey()){//자식 둘의 대소비교를 해서 누가 부모가 될지 판별
				child++;
			}
			if(last.getKey()>= node[child].getKey()) break;//예외처리
			node[parent] = node[child];//두 자식중 큰 값이 부모가 됨.
			parent = child; 
			child *= 2;
		}
		node[parent] = last; // 맨 마지막 배열의 값을 앞으로 한칸 옮김. 코드가 돌면서 parent의 값은 마지막의 바로 앞의 값이 됨.
		return item;

	}
	
	HeapNode find() {return node[1];} //제일 큰 값을 반환.

	void display(){
		for(int i = 1, level = 1; i<=size; i++){
			if(i==level){
				cout<<endl;
				level *= 2;//level이 바뀌는 지점
			}
			node[i].display();//오버라이딩
		}
		cout << endl << "--------------------------";
	}
};
int main(){
	MaxHeap heap;

	/*heap.insert(10);
	heap.insert( 5); 
	heap.insert(30); 
	heap.insert( 8);
	heap.insert( 9);
	heap.insert( 3);
	heap.insert( 7);*/
	heap.display();
	//여기서 순서를 바꿔보면 다르게 출력된다는 걸 알 수 있다.
	heap.insert(10);
	heap.insert(5);
	heap.insert(30);
	heap.insert(3);
	heap.insert(7);
	heap.insert(9);
	heap.insert(8);
	heap.display();
	
	//함수 작동
	heap.remove();
	heap.display();
	heap.remove();
	heap.display();

	heap.insert(2);
	heap.insert( 5);
	heap.insert(6);
	heap.insert( 8);
	heap.insert( 9);
	heap.insert( 10);
	heap.display();
	cout << endl;
}