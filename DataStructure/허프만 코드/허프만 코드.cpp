#include<iostream>
using namespace std;
	@Override
	public void add(T value) {
		// overflow 방지를 위한 size 재정의
		if(size >= array.length) {
			grow();
		}
		
		array[++size] = value;
		upHeap(size);
	}


	@Override
	public void upHeap(int idx) {
		int nodeIndex = idx;
		T value = this.array[nodeIndex];
		
		if(value == null) return;	// 해당 인덱스의 데이터가 없을 경우
		
		// 루트 노드가 아니면서 부모노드가 자식노드보다 클 경우에
		while(idx > 1 && greater(idx/2,idx)) {
			swap(idx/2,idx);
			idx = idx/2;
		}
	}
@Override
	public T remove() {
		T value = array[1];	
		swap(1,size--);		// size 1 감소 및 마지막 노드와 부모노드 스왑
		array[size+1] = null;
		
		downHeap(1);
		return value;
	}


	@Override
	public void downHeap(int idx) {
		T value = array[idx];
		if (value == null) return;
		
		int leftIdx = 2 * idx;
		int rightIdx = 2 * idx + 1;
		
		T left = (leftIdx != Integer.MIN_VALUE && leftIdx < this.size) ? this.array[leftIdx] : null;
		T right = (rightIdx != Integer.MIN_VALUE && rightIdx < this.size) ? this.array[rightIdx] : null;
		
		T nodeToMove = null;
		int nodeToMoveIdx = -1;
		
		// 두 자식 노드가 모두 크거나 같을 때
		if((type == Type.MIN && left != null && right != null && value.compareTo(left) > 0 && value.compareTo(right) > 0) 
			|| (type == Type.MAX && left != null && right != null && value.compareTo(left) < 0 && value.compareTo(right) < 0)) {
			
			// 오른쪽 자식노드가 왼쪽 자식노드보다 크거나 작을 때
			if((right != null) &&
				((type == Type.MIN && (right.compareTo(left) < 0)) || ((type == Type.MAX && right.compareTo(left) > 0)))) {
				nodeToMove = right;
				nodeToMoveIdx = rightIdx;
			}
			
			// 왼쪽 자식노드가 오른쪽 자식노드보다 크거나 작을 때
			else if((left != null) && 
				((type == Type.MIN && left.compareTo(right) < 0)) || (type == Type.MAX && left.compareTo(right) > 0)) {
				nodeToMove = left;
				nodeToMoveIdx = leftIdx;
			}
			
			// 두 자식노드가 같을 때
			else {
				nodeToMove = right;
				nodeToMoveIdx = rightIdx;
			}
		}
		
		// 오른쪽 자식 노드가 부모노드보다 크거나 같을 때
		else if((type == Type.MIN && right != null && value.compareTo(right) > 0)
				|| (type == Type.MAX && right != null && value.compareTo(right) < 0)) {
			nodeToMove = right;
			nodeToMoveIdx = rightIdx;
		}
		
		// 왼쪽 자식 노드가 부모노드보다 크거나 같을 때
		else if((type == Type.MIN && left != null && value.compareTo(left) > 0) 
			|| (type == Type.MAX && left != null && value.compareTo(left) < 0)) {
				nodeToMove = left;
				nodeToMoveIdx = leftIdx;
		}
		
		// 교환할 노드가 없을 경우
		if(nodeToMove == null) return;
		
		// 스왑
		this.array[nodeToMoveIdx] = value;
		this.array[idx] = nodeToMove;
		
		downHeap(nodeToMoveIdx);
	}

public class Entry {
	private int frequency;	//  빈도 수
	private String word; 	// 노드의 문자 또는 내부노드의 합성된 문자열
	private Entry left;		// 왼쪽 자식
	private Entry right;	// 오른쪽 자식
	private String code;	// 허프만 코드
	public Entry (int newFreq, String newVal, Entry l, Entry r, String newCode) {
		frequency = newFreq;
		word = newVal;
		left = l;
		right = r;
		code = newCode;
	}
	public int getFrequency() {
		return frequency;
	}
	public void setFrequency(int frequency) {
		this.frequency = frequency;
	}
	public String getWord() {
		return word;
	}
	public void setWord(String word) {
		this.word = word;
	}
	public Entry getLeft() {
		return left;
	}
	public void setLeft(Entry left) {
		this.left = left;
	}
	public Entry getRight() {
		return right;
	}
	public void setRight(Entry right) {
		this.right = right;
	}
	public String getCode() {
		return code;
	}
	public void setCode(String code) {
		this.code = code;
	}

    public class Huffman {
	private Entry[] harray;	// a[0]은 사용안함 (트리이기때문)
	private int size;		// 힙 사이즈
	public Huffman(Entry[] heapArray, int initialSize) { 	// 생성자
		harray = heapArray;
		size = initialSize;
	}
	
	private boolean greater(int i, int j) {
		return harray[i].getFrequency() > harray[j].getFrequency();
	}
	
	public Entry createTree() {
		while(size() > 1) {
			Entry e1 = deleteMin();		// 힙에서 최소 빈도수를 가진 노드 제거
			Entry e2 = deleteMin();		// 힙에서 최소 빈도수를 가진 노드 제거
			
			Entry temp = new Entry(e1.getFrequency() + e2.getFrequency(),	// 빈도수 합
								e1.getWord() + e2.getWord(),				// 단어 이어붙이기
								e1,e2," ");						//	e1,e2가 각각 새로운 노드의 오른쪽,왼쪽 자식노드로 붙기
			insert(temp);	// 새 노드를 힙에 삽입
		}
		
		return deleteMin();	// 1개 남은 노드(루트 노드)를 힙에서 제거하며 리턴
	}
}
