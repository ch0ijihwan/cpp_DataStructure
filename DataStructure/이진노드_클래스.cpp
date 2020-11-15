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
    int getData(){
        return data;
    }
    BinaryNode* getLeft(){return left;} //left포인터 변수가 가르키는 노드의 데이터를 리턴해주는 것이기 때문에 left가 가르키는 노드의 data를 불러옴
    BinaryNode* getRight(){return right;}
    bool isLeaf(){return left==NULL && right == NULL;}

};

class BinaryTree{ // 이진트리 구성
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
   
    void inorder(){//중위
        cout<<endl<<" inorder : ";
        inorder(root);
    }
    void inorder(BinaryNode* node){//root 노드를 받은 후의 중위 순회
        if(node != NULL){
            inorder(node-> getLeft());
            cout << " [ " <<(char) node ->getData() << " ] ";
            inorder(node->getRight());

        }
    }

    void preorder(){ //전위
        cout<< endl<<" preorde: ";
        preorder(root);
    }
    void preorder(BinaryNode* node){
        if(node != NULL){
            cout <<" [ " <<(char) node->getData() << " ] ";
            preorder(node -> getLeft());
            preorder(node-> getRight());
        }
    }

    void postorder(){//후위
        cout << endl << " postorder: ";
        postorder(root);
    }
    void postorder(BinaryNode* node){
        if(node != NULL){
            postorder(node->getLeft());
            postorder(node->getRight());
            cout<< " [ " <<(char)node-> getData() << " ] ";
        }
    }
};

int main(){
    BinaryTree tree;
    BinaryNode* g = new BinaryNode('G', NULL, NULL);
    BinaryNode* h = new BinaryNode('H', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', g, h);		
	BinaryNode* f = new BinaryNode('F', NULL, NULL);
	BinaryNode* c = new BinaryNode('C', e, f);
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* b = new BinaryNode('B', d, NULL);
	BinaryNode* a = new BinaryNode('A', b, c);
    tree.setRoot(a);
    tree.inorder();
	tree.preorder();
	tree.postorder();
	cout << endl;
}		