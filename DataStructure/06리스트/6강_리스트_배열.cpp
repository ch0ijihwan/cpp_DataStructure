#include <iostream>
#define MAX 100
using namespace std;

class ArrayList {
private:
	int data[MAX];
	int length;
public:
	ArrayList() { length = 0; }
	bool isFull() { return length == MAX; }
	bool isEmpty() { return length == 0; }

	
	void insert(int pos, int e) {
		if (!isFull() && pos >= 0 && pos <= length) {
			for (int i = length; i > pos; i--) { //length는 i//뒤에서 부터 한칸씩 뒤로 미뤄주고 i 가 Pos랑 같아지면 그 자리에 e를 넣어줌.
				data[i] = data[i - 1];
			}
			data[pos] = e;
			length++;
		}
		else {
			cout << "포화상태 오류 또는 삽입 위치 오류";
		}
	}
	void remove(int pos) {
		if (!isEmpty() && 0 <= pos && pos < length) { //isEmpty를 따져서 배열이 비어있는지 아닌지 확인
			for (int i = pos + 1; i < length; i++) {//max번째 인덱스는 없어서 length는 =<를 사용하지 않고 <를 사용함.
				data[i - 1] = data[i];
			}
			length--;
		}
		else {
			cout << "공백상태 오류 또는 삭제 위치 오류";
		}
	}

	int getEntry(int pos) {
		return data[pos];
	}
	
	bool find(int item) {
		for (int i = 0; i < length; i++) {
			if (data[i] == item) {
				return true;
			}
		}
		return false;
	}
	void replace(int pos, int e) {
		data[pos] = e;
	}
	int size() {
		return length;
	}
	void display() {
		cout << "[배열로 구현한 리스트 전체 항목수: " << size() << "] : ";
		for (int i = 0; i < size(); i++) { // == size()-1 까지임. <를 사용. 
			cout << "[" << data[i] << "]";
		}
		cout << endl;
	}
	void clear() { length = 0; }
};

int main() {
	ArrayList list;
	list.insert(0, 10);
	list.insert(0, 20);
	list.insert(1, 30);
	list.insert(list.size(), 40);
	list.insert(2, 50);
	list.display();
	list.remove(2);
	list.remove(list.size() - 1);
	list.remove(0);
	list.replace(1, 90);
	list.display();
	list.clear();
	list.display();
}