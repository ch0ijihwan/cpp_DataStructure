
/*
인접 행렬을 이용한 그래프 클래스 프로그램
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#define MAX_VTXS 256 //표현 가능한 최대 정점의 개수

class AdjMatGraph
{
protected:
        int size;                    //정점의 개수
        char vertices[MAX_VTXS];     //정점의 이름
        int adj[MAX_VTXS][MAX_VTXS]; //인접 행렬
public:
        AdjMatGraph()
        {
                reset();
        }
        char getVertex(int i)
        {
                return vertices[i];
        }
        int getEdge(int i, int j)
        {
                return adj[i][j];
        }
        void setEdge(int i, int j, int val)
        {
                adj[i][j] = val;
        }
        bool isEmpty()
        {
                return size == 0;
        }
        bool isFull()
        {
                return size >= MAX_VTXS;
        }
        //그래프 초기화==>공백 상태의 그래프
        void reset()
        {
                size = 0;
                for (int i = 0; i < MAX_VTXS; i++)
                        for (int j = 0; j < MAX_VTXS; j++)
                                setEdge(i, j, 0);
        }
        //정점 삽입 연산
        void insertVertex(char name)
        {
                if (!isFull())
                        vertices[size++] = name;
                else
                        cout << "Error: 그래프 정점 개수 초과" << endl;
        }
        //간선 삽입 연산: 무방향 그래프의 경우
        void insertEdge(int u, int v)
        {
                setEdge(u, v, 1);
                setEdge(v, u, 1); //방향 그래프에서는 삭제
        }
        //무작위로 그래프를 발생시키는 함수
        void randomGraph(int numVtx, int numEdge)
        {
                for (int j = 0; j < numVtx; j++)
                        insertVertex('A' + j);

                int i = 0;

                while (i < numEdge)
                {
                        int count = 0;
                        do
                        {
                                int first = rand() % numVtx;
                                int second;
                                do
                                {
                                        second = rand() % numVtx;
                                } while (first == second);
                                
                                if (!adj[first][second])
                                {
                                        insertEdge(first, second);
                                        count++;
                                }
                        } while (!count);
                        i++;
                }
        }
        //모든 정점이 연결된 "연결 그래프"를 무작위로 발생시키는 함수
        void randomConnectedGraph(int numVtx)
        {
                for (int j = 0; j < numVtx; j++)
                        insertVertex('A' + j);
                for (int i = 0; i < numVtx; i++)
                        for (int j = 0; j < numVtx; j++)
                                if (i != j)
                                        insertEdge(i, j);
        }
        //그래프 정보 출력
        void display(FILE *fp = stdout)
        {
                fprintf(fp, "%d\n", size);
                for (int i = 0; i < size; i++)
                {
                        fprintf(fp, "%c ", getVertex(i));
                        for (int j = 0; j < size; j++)
                                fprintf(fp, " %3d", getEdge(i, j));
                        ;
                        fprintf(fp, "\n");
                }
        }
        //파일 입력 함수
        void load(char *filename)
        {
                FILE *fp = fopen(filename, "r");
                ;
                if (fp != NULL)
                {
                        int n, val;
                        fscanf(fp, "%d", &n); //정점의 전체 개수
                        for (int i = 0; i < n; i++)
                        {
                                char str[80];
                                fscanf(fp, "%s", str);
                                insertVertex(str[0]);
                                for (int j = 0; j < n; j++)
                                {
                                        int val;
                                        fscanf(fp, "%d", &val);
                                        if (val != 0)
                                                insertEdge(i, j);
                                }
                        }
                        fclose(fp);
                }
        }
        //파일 저장 함수
        void store(char *filename)
        {
                FILE *fp = fopen(filename, "w");
                if (fp != NULL)
                {
                        display(fp);
                        fclose(fp);
                }
        }
};

/*
탐색 기능을 가진 그래프 클래스(인접 행렬 사용)
*/
class CircularQueue
{

protected: //상속을 위한
        int front;
        int rear;
        int data[MAX_VTXS];

public:
        CircularQueue()
        {
                front = rear = 0;
        }

        bool isEmpty() { return front == rear; }
        bool isFull() { return (rear + 1) % MAX_VTXS == front; }

        void enqueue(int val)
        {
                if (isFull())
                {
                        cout << "큐가 포화상태입니다."
                             << "\n";
                }
                else
                {
                        rear = (rear + 1) % MAX_VTXS;
                        data[rear] = val;
                }
        }

        int dequeue()
        {
                if (isEmpty())
                {
                        cout << "큐가 공백상태이에요." << endl;
                        return 0;
                }
                else
                {
                        front = (front + 1) % MAX_VTXS;
                        return data[front];
                }
        }

        void display()
        {
                cout << "큐내용: ";
                int maxi = (front < rear) ? rear : rear + MAX_VTXS;
                for (int i = front + 1; i <= maxi; i++)
                {
                        cout << data[i % MAX_VTXS];
                }
                cout << "\n";
        }
};

class SrchAMGraph : public AdjMatGraph
{
protected:
        bool visited[MAX_VTXS]; //정점의 방문 정보
public:
        void resetVisited() //모든 정점을 방문하지 않았다고 설정
        {
                for (int i = 0; i < size; i++)
                        visited[i] = false;
        }
        bool isLinked(int u, int v)
        {
                return getEdge(u, v) != 0;
        }
        //모든 정점이 연결된 "연결 그래프"를 무작위로 발생시키는 함수
        void ConnectedGraph(int numVtx)
        {
                int cnt = rand() % ((numVtx * 2) - 1) + 1;
                cout << "랜덤 연결 그래프 생성" << endl;
                cout << "간선 수: " << cnt << endl;
                for (int j = 0; j < numVtx; j++)
                        insertVertex('A' + j);
                int first = rand() % numVtx;
                int second;
                do
                {
                        second = rand() % numVtx;
                } while (first == second);
                insertEdge(first, second);
                for (int i = 1; i < cnt; i++)
                {
                        int linked = 0;
                        do
                        {
                                first = rand() % numVtx;
                                do
                                {
                                        second = rand() % numVtx;
                                } while (first == second);
                                for (int j = 0; j < numVtx; j++)
                                        if (isLinked(first, j) || isLinked(second, j))
                                                linked++;
                        } while (getEdge(first, second) || linked == 0);
                        insertEdge(first, second);
                }
        }
        //깊이 우선 탐색 함수
        void DFS(int v)
        {
                visited[v] = true;
                cout << getVertex(v) << " ";
                for (int w = 0; w < size; w++)
                        if (isLinked(v, w) && visited[w] == false)
                                DFS(w); //연결+방문X=> 순환 호출로 방문
        }
        //인접행렬로 표현된 그래프에 대한 너비우선탐색 연산
        void BFS(int v)
        {
                visited[v] = true;
                cout << getVertex(v) << " "; //정점의 이름 출력

                CircularQueue que;
                que.enqueue(v); //시작 정점을 큐에 저장

                while (!que.isEmpty())
                {
                        int v = que.dequeue(); //큐에 정점 추출
                        for (int w = 0; w < size; w++)
                                if (isLinked(v, w) && visited[w] == false)
                                {
                                        visited[w] = true; //방문 표시
                                        cout << getVertex(w) << " ";
                                        que.enqueue(w);
                                }
                }
        }
};

/*
인접 배열을 이용한 그래프의 연결 성분 탐색 프로그램
*/

class ConnectedComponentGraph : public SrchAMGraph
{
private:
        int label[MAX_VTXS]; //정점의 색상 필드 추가
public:
        //깊이 우선 탐색
        void labelDFS(int v, int color)
        {
                visited[v] = true;
                label[v] = color;
                for (int w = 0; w < size; w++)
                        if (isLinked(v, w) && visited[w] == false)
                                labelDFS(w, color);
        }
        //그래프의 연결 성분 검출 함수
        void findConnectedComponent()
        {
                int count = 0;
                for (int i = 0; i < size; i++)
                        if (visited[i] == false)
                                labelDFS(i, ++count);
                cout << "그래프의 연결 성분 개수==" << count << endl;
                for (int i = 0; i < size; i++)
                        cout << getVertex(i) << "=" << label[i] << " ";
                cout << endl;
        }
};

int main(void)
{

        ConnectedComponentGraph g;
        int n;     //정점 함수 첫번째
        int n_, r; //두번째 함수
        int n_2;   //세번째 함수

        /*cout << "램덤 그래프의 정점의 개수는? ";
        cin >> n;
        g.ConnectedGraph(n);
        g.display();
        g.reset();*/

        cout << "램덤 그래프의 정점의 개수와 간선의 개수는?" << endl;
        cin >> n_;
        cin >> r;
        g.randomGraph(n_, r);
        g.display();

        /*cout << "모든정점이 램덤으로 연결된 그래프의 정점의 개수는?" << endl;
        cin >> r;
        g.randomConnectedGraph(r);
        g.reset();*/

        g.resetVisited();
        g.findConnectedComponent();
        cout << "DFS: ";
        g.resetVisited();
        g.DFS(0);
        cout << endl;
        return 0;
}

/*
n개의 정점을 갖는 연결 그래프를 발생시키고 깊이 우선 탐색을 적용하여 정점을 방문하는 순서를 출력한다
*/