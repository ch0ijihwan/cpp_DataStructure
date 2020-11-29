#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define MAX 256

class AdjMatGraph
{
protected:
    int size;
    char vertices[MAX];
    int adj[MAX][MAX];

public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }

    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX; }

    void reset()
    {
        size = 0;
        for (int i = 0; i < MAX; i++)
        {
            for (int j = 0; j < MAX; j++)
            {
                setEdge(i, j, 0);
            }
        }
    }

    void insertVertex(char name)
    {
        if (!isFull())
            vertices[size++] = name;
        else
            cout << "Error: 그래프 점점 개수 초과" << endl;
    }

    void insertEdge(int u, int v)
    {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }

   void display(FILE* fp = stdout) {
		fprintf(fp, "%d\n", size);
		for (int i = 0; i < size; i++) {
			fprintf(fp, "%c ", getVertex(i));
			for (int j = 0; j < size; j++) {
				fprintf(fp, "%3d", getEdge(i, j));
			}
			fprintf(fp, "\n");
		}
	}

    void load(char* filename) {
		FILE* fp = fopen(filename, "r");
		if (fp != NULL) {
			int n;
			fscanf(fp, "%d", &n);
			for (int i = 0; i < n; i++) {
				char str[80];
				fscanf(fp, "%s", str);
				insertVertex(str[0]);
				for (int j = 0; j < n; j++) {
					int val;
					fscanf(fp, "%d", &val);
					if (val != 0) {
						insertEdge(i, j);
					}
				}
			}
			fclose(fp);

		}
	}
    
    void store(char* filename){
        FILE* fp = fopen(filename, "W");
        if(fp!=NULL){
            display(fp);
            fclose(fp);
        }
    }
};

class SrchANGraph : public AdjMatGraph{
    bool visited[MAX];

public:
    void resetVsited(){
        for(int i = 0; i<size; i++){
            visited[i] = false;
        }
    }
    bool isLinked(int u, int v){ // 연결이 되어 있냐고 물어봄
        return getEdge(u,v)!=0; //연결이 되어있으면 1리턴
    }
    void DFS(int v) {
		visited[v] = true;
		cout << getVertex(v) << " ";

		for (int w = 0; w < size; w++) {
			if (isLinked(v,w) && visited[w] == false) {
				DFS(w);
			}
		}
	}

    
};


int main(){
    SrchANGraph g;
    g.display();
    g.load("11_graph/test_graph.txt");

    
    cout<<"그래프(test_graph.txt)"<< endl;
    g.display();

    cout<<"DFS======>";
    g.resetVsited();
    g.DFS(0);
    cout<<endl;


  

} 

