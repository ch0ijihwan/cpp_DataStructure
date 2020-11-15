#include<iostream>
using namespace std;

class BinaryNode{
    protected:
        int data;
        BinaryNode* left;
        BinaryNode* right;

    public:
     BinaryNode(int val = 0, BinaryNode* l =NULL, BinaryNode* r = NULL){
         data = val;
         left = l;
         right = r;
     }
    void setData(int val){ 
        data = val;
    }
    void setLeft(BinaryNode* l){
        left = l;
    }
    void setRight(BinaryNode* r){
        right = r;
    }
    int getdata(){
        return data;
    }
    BinaryNode* getleft(){return left;} //left포인터 변수가 가르키는 노드의 데이터를 리턴해주는 것이기 때문에 left가 가르키는 노드의 data를 불러옴
    BinaryNode* getRight(){return right;}
    bool isLeaf(){return left==NULL && right == NULL;}

};

class BinaryTree{
    private:
    BinaryNode* root;

    public:
    BinaryTree(){
         root = NULL;
     }
    void setRoot(BinaryNode* node){
        root = node;
    }

    BinaryNode* getRoot(){
        return root;
        };

    bool isEmpty(){
        return root==NULL;
    }
   
    
};