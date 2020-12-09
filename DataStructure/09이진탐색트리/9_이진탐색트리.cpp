#include <iostream>
#define MAX 100
using namespace std;

class BinaryNode
{
protected:
    int data;
    BinaryNode *left;
    BinaryNode *right;

public:
    BinaryNode(int val = 0, BinaryNode *l = NULL, BinaryNode *r = NULL)
        : data(val), left(l), right(r) {}
    void setData(int val) { data = val; }
    void setLeft(BinaryNode *l) { left = l; }
    void setRight(BinaryNode *r) { right = r; }
    int getData() { return data; }
    BinaryNode *getLeft() { return left; }
    BinaryNode *getRight() { return right; }

    /*BinaryNode* search(int key) {
		if (key == data) {
			return this;
		}
		else if (key < data && left != NULL) {
			return left->search(key);
		}
		else if (key > data && right != NULL) {
			return right->search(key);
		}
		else {
			return NULL;
		}
	}*/
    bool isLeaf() { return left == NULL && right == NULL; }
};

class CircularQueue
{
private:
    int front;
    int rear;
    BinaryNode *data[MAX];

public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX == front; }
    void enqueue(BinaryNode *n)
    {
        if (isFull())
        {
            cout << "큐가 포화상태입니다." << endl;
        }
        else
        {
            rear = (rear + 1) % MAX;
            data[rear] = n;
        }
    }

    BinaryNode *dequeue()
    {
        if (isEmpty())
        {
            cout << "큐가 비어있습니다." << endl;
        }
        else
        {
            front = (front + 1) % MAX;
            return data[front];
        }
    }
};
class BinaryTree : public BinaryNode
{

protected:
    BinaryNode *root;

public:
    BinaryTree() : root(NULL) {}
    void setRoot(BinaryNode *node) { root = node; }
    BinaryNode *getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    void inorder()
    {
        cout << endl
             << " inorder: ";
        inorder(root);
    }
    void inorder(BinaryNode *node)
    {
        if (node != NULL)
        {
            inorder(node->getLeft());
            cout << " [ " << node->getData() << " ] ";
            inorder(node->getRight());
        }
    }

    void preorder()
    {
        cout << endl
             << " preorder: ";
        preorder(root);
    }
    void preorder(BinaryNode *node)
    {
        if (node != NULL)
        {
            cout << " [ " << node->getData() << " ] ";
            preorder(node->getLeft());
            preorder(node->getRight());
        }
    }

    void postorder()
    {
        cout << endl
             << " postorder: ";
        postorder(root);
    }
    void postorder(BinaryNode *node)
    {
        if (node != NULL)
        {
            postorder(node->getLeft());
            postorder(node->getRight());
            cout << " [ " << node->getData() << " ] ";
        }
    }

    void levelorder()
    {
        cout << endl
             << " levelorder: ";
        if (!isEmpty())
        {
            CircularQueue q;
            q.enqueue(root);
            while (!q.isEmpty())
            {
                BinaryNode *n = q.dequeue();
                if (n != NULL)
                {
                    cout << " [ " << n->getData() << " ] ";
                    q.enqueue(n->getLeft());
                    q.enqueue(n->getRight());
                }
            }
        }
        cout << endl;
    }

    //노드 개수 구하는 함수
    int getCount() { return isEmpty() ? 0 : getCount(root); }
    int getCount(BinaryNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return 1 + getCount(node->getLeft()) + getCount(node->getRight());//여기서 1을 더해주는 이유는, root노드의 개수도 포함시키기 위한 것.
    }

    //단말 노드 개수 구하는 함수
    int getLeafCount() { return isEmpty() ? 0 : getLeafCount(root); }
    int getLeafCount(BinaryNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        if (node->isLeaf())
        {
            return 1; //루트노드만 있을경우 1. 루트노드가 단말 노드이기 때문에
        }
        else
            return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
    }
 
    //높이 구하는 함수
    int getHeight() { return isEmpty() ? 0 : getHeight(root); }
    int getHeight(BinaryNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        int hLeft = getHeight(node->getLeft());
        int hRight = getHeight(node->getRight());
        return (hLeft > hRight) ? hLeft + 1 : hRight + 1;
    }

     int    calcSize()    { return calcSize(root); }
    int calcSize(BinaryNode *node)    {
        if( node == NULL ) return 0;
        return node->getData() + calcSize(node->getLeft()) + calcSize(node->getRight());
    }

    int evaluate() { return evaluate(root); }

    int evaluate(BinaryNode *node) {
        if( node == NULL ) return 0;
        if( node->isLeaf() ) return node->getData();
        else {
            int op1 = evaluate(node->getLeft());
            int op2 = evaluate(node->getRight());
            switch(node->getData()){
                case '+': return op1+op2;
                case '-': return op1-op2;
                case '*': return op1*op2;
                case '/': return op1/op2;
            }
            return 0;
        }
    }
};
//이진트리 탐색 시작.
class BinSrchTree : public BinaryTree{

public:
    BinSrchTree(void) {}
    ~BinSrchTree(void) {}

    BinaryNode *search(int key)
    {
        BinaryNode *node = searchRecur(root, key);
        if (node != NULL)
        {
            cout << "탐색성공: 키값이 " << node->getData() << "인 노드 = " << node << endl;
        }
        else
        {
            cout << "탐색실패: 키값이 " << key << "인 노드없음 " << endl;
        }
        return node;
    }

    BinaryNode *searchRecur(BinaryNode *n, int key)
    {
        if (n == NULL)
            return NULL;
        if (key == n->getData())
        {
            return n;
        }// 순환의 개념을 사용하여 key와 n을 비교함.
        else if (key < n->getData())
        {   //key값이 n보다 작으면 
            return searchRecur(n->getLeft(), key);
        }
        else
        {
            return searchRecur(n->getRight(), key);
        }
    }



    void insert(BinaryNode *n)
    {
        if (n == NULL)
            return;
        if (isEmpty())
            root = n;
        else
            insertRecur(root, n);
    }

    void insertRecur(BinaryNode *r, BinaryNode *n)
    {
        if (n->getData() == r->getData())//root의 값과 n의 값이 값으면 인서트를 해줄 필요가 없어서 바로 리턴해준다. [예외처리]
        {
            return;
        }
        else if (n->getData() < r->getData())//Root의 값과 N의 값을 비교.  즉 넣을려는 값이 작으면 코드 진행
        
        {
            if (r->getLeft() == NULL)//root가  비어있으면 루트에 n을 바로 넣어줌.
            
            {
                r->setLeft(n);
            }
            else  // 이때 root가 비어있지 않다면 그 하위 왼쪽 자식노드에 n을 넣어주고 순환 반복.
            {
                insertRecur(r->getLeft(), n);
            }
        }
        else// 반대로 root 값이 n보다 큰경우 위와 같이 오른쪽 노드로 순환 반복.
        {
            if (r->getRight() == NULL)
            {
                r->setRight(n);
            }
            else
            {
                insertRecur(r->getRight(), n);
            }
        }
    }

    void remove(int key)
    {
        if (isEmpty())
            return;
        BinaryNode *parent = NULL;
        BinaryNode *node = root;
        while (node != NULL && node->getData() != key)
        {
            parent = node;
            node = (key < node->getData()) ? node->getLeft() : node->getRight();
        }

        if (node == NULL)
        {
            cout << "Error: key is not in the tree!" << endl;
            return;
        }
        else
        {
            remove(parent, node);
        }
    }

    void remove(BinaryNode *parent, BinaryNode *node)
    {
        if (node->isLeaf())
        {
            if (parent == NULL)
            {
                root = NULL;
            }

            else
            {
                if (parent->getLeft() == node)
                {
                    parent->setLeft(NULL);
                }
                else
                {
                    parent->setRight(NULL);
                }
            }
        }
        else if (node->getLeft() == NULL || node->getRight() == NULL) // 자식노드가 하나만 있는 경우
        {
            BinaryNode *child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();
            if (node == root)
            {
                root = child;
            }
            else
            {
                if (parent->getLeft() == node)//삭제하려는 노드가 부모노드의 오른쪽 자식이라면
                {
                    parent->setLeft(child);//자신의 자식을  자신의 부모노드의 왼쪽 자식으로  우선 연결.
                }
                else
                    parent->setRight(child);// 그렇지 않다면 오른쪽에 연결
            }
        }
        else// 그외 자식노드가 왼쪽 오른쪽 다 있다면.
        {
            BinaryNode *succp = node;
            BinaryNode *succ = node->getRight();
            while (succ->getLeft() != NULL)
            {
                succp = succ;
                succ = succ->getLeft();
            }

            if (succp->getLeft() == succ)
            {
                succp->setLeft(succ->getRight());
            }
            else
            {
                succp->setRight(succ->getRight());
            }
            node->setData(succ->getData());
            node = succ;
        }

        delete node;//제일 밑에 있던 후계자 노드의 값을 위로 올려줬기 때문에 마지막 단말 노드인 succ를 지워버림.
    }
};


int main()
{
     BinSrchTree tree;

    // tree.insert(new BinaryNode(35));
    // tree.insert(new BinaryNode(18));
    // tree.insert(new BinaryNode(7));
    // tree.insert(new BinaryNode(26));
    // tree.insert(new BinaryNode(12));
    // tree.insert(new BinaryNode(3));
    // tree.insert(new BinaryNode(68));
    // tree.insert(new BinaryNode(22));
    // tree.insert(new BinaryNode(30));
    // tree.insert(new BinaryNode(99));

    // cout << "노드의 개수 = " << tree.getCount() << endl;
    // cout << "단말의 개수 = " << tree.getLeafCount() << endl;
    // cout << "트리의 높이 = " << tree.getHeight() << endl;

    // tree.inorder();
    // tree.preorder();
    // tree.postorder();
    // tree.levelorder();

   
    // tree.search(25);
    // cout << "CASE1 ==> 노드 3 삭제" << endl;
    // tree.remove(3);
    // tree.levelorder();
    // cout << "CASE2 ==> 노드 68 삭제" << endl;
    // tree.remove(68);
    // tree.levelorder();
    // cout << "CASE3 ==> 노드 18 삭제" << endl;
    // tree.remove(18);
    // tree.levelorder();
    // cout << "CASE3 ==> 노드 35 삭제" << endl;
    // tree.remove(35);
    // tree.levelorder();

    // cout << "노드의 개수 = " << tree.getCount() << endl;
    // cout << "단말의 개수 = " << tree.getLeafCount() << endl;
    
    // cout << "트리의 높이 = " << tree.getHeight() << endl;

    // tree.calcSize();
    tree.insert(new BinaryNode(5));
	tree.insert(new BinaryNode(3));
	tree.insert(new BinaryNode(7));
	tree.insert(new BinaryNode(1));
	tree.insert(new BinaryNode(4));
	tree.insert(new BinaryNode(2));
	tree.insert(new BinaryNode(9));
	tree.insert(new BinaryNode(6));
	tree.insert(new BinaryNode(8));
	

	cout << "노드의 개수 = " << tree.getCount() << endl;
	cout << "단말의 개수 = " << tree.getLeafCount() << endl;
	cout << "트리의 높이 = " << tree.getHeight() << endl;

	tree.levelorder();


}