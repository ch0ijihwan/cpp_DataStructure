#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#define MAX 256

class AdjMatGraph
{
protected:
	int size;
	char vertices[MAX];
	int adj[MAX][MAX]; //정적으로 할당함.

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
		if (isFull() != true)
			vertices[size++] = name;
		else
			cout << "Error: 그래프 점점 개수 초가" << endl;
	}

	void insertEdge(int u, int v)
	{
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}

	void display(FILE *fp = stdout)
	{							   //Vertex 을 2차원 배열 형태로 출력해줌
		fprintf(fp, "%d\n", size); //문자열 %d에 size 저장 후 출력
		for (int i = 0; i < size; i++) // 가로줄 한줄 씩 출력하는 반복문
		{
			fprintf(fp, "%c ", getVertex(i)); // A,B,C,D 가 출력되는 부분
			for (int j = 0; j < size; j++)
			{
				fprintf(fp, "%3d", getEdge(i, j)); // 실질적으로 값이 출력 되는 부분
			}
			fprintf(fp, "\n");
		}
	}

	void load(char *filename)
	{
		FILE *fp = fopen(filename, "r");
		if (fp != NULL)
		{		   // 파일에 값이 있다면
			int n; //int형으로 한글자씩 받음
			fscanf(fp, "%d", &n);
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
					{
						insertEdge(i, j);
					}
				}
			}
			fclose(fp);
		}
	}

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

// int main()
// {
// 	AdjMatGraph g;
// 	for (int i = 0; i < 4; i++)
// 	{
// 		g.insertVertex('A' + i);
// 	}

// 	g.insertEdge(0, 1);
// 	g.insertEdge(0, 3);
// 	g.insertEdge(1, 2);
// 	g.insertEdge(1, 3);
// 	g.insertEdge(2, 3);

// 	cout << "인접 행렬로 표현한 그래프" << endl;
// 	g.display();
// 	g.store("graph.txt");

// 	g.reset();//그래프 내용을 비움
// 	g.display();

// 	g.load("graph.txt");//저장된 그래프를 불러옴
// 	cout << "인접행렬로 표현한 그래프 (파일: graph.txt)" << endl;
// 	g.display();//다시 출력
// }