#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<iostream>
#include<iomanip>
using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix,*color,*parent,*dist,*f,time ; //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source);
    void dfs_visit(int source);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    color=0;
    parent=0;
    dist=0;
    f=0;
    time=0;
    directed = dir ;//set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];
    f=new int[nVertices];
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    else if(matrix[u][v]) return true;
    else return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int deg=0;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]==1) deg++;
    }
    return deg;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]&&matrix[v][i]) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u=q.dequeue();
        for(int i=0; i<nVertices; i++)
        {
            int v=i;
            if(matrix[u][v])
            {
                if(color[v]==WHITE)
                {
                    color[v]=GREY;
                    dist[v]=dist[u]+1;
                    parent[v]=u;
                    q.enqueue(v);
                }
            }
        }
        color[u]=BLACK;
    }
//    printf("\nColor\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",color[i]);
//    }
//    printf("\nParent\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",parent[i]);
//    }
//    printf("\nDist\n");
//    for(int i=0; i<nVertices; i++)
//   {
//        printf("%2d",dist[i]);
//    }
//    printf("\n");

}

void Graph::dfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
        f[i] = INFINITY ;
    }
    time=0;
    for(int u=0; u<nVertices; u++)
    {
        if(color[u]==WHITE)
            dfs_visit(u);
    }
//
//    printf("\nColor\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",color[i]);
//    }
//    printf("\nParent\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",parent[i]);
//    }
//    printf("\nDist\n");
//    for(int i=0; i<nVertices; i++)
//   {
//        printf("%2d",dist[i]);
//    }
//    printf("\n");
//    printf("\nf\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",f[i]);
//    }
//    printf("\n");
}

void Graph::dfs_visit(int source)
{
    int u=source;
    color[u]=GREY;
    time=time+1;
    dist[u]=time;

    for(int i=0; i<nVertices; i++)
    {
        int v=i;
        if(matrix[u][v])
        {
            if(color[v]==WHITE)
            {
                parent[v]=u;
                dfs_visit(v);
            }
        }
    }
    color[u]=BLACK;
    time=time+1;
    f[u]=time;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return dist[v];
    //return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{

    delete []color;
    delete []parent;
    delete []dist;
    delete []f;
    color=0;
    parent=0;
    dist=0;
    f=0;
    for(int i=0;i<nVertices;i++)
    {
        delete []matrix[i];
    }
    delete []matrix;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Run BFS 3. Run DFS\n");
        printf("4. isEdge(u,v) 5. Print Graph  6. Exit.\n");
        printf("7. removeEdge(u,v) 8.  getDegree(u)\n");
        printf("9. hasCommonAdjacent(u,v)  10. getDist(u,v)\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            g.bfs(0);
        }
        else if(ch==3)
        {
            g.dfs(0);
        }
        else if(ch==4)
        {
            int u,v;
            cin>>u>>v;
            cout<<boolalpha<<g.isEdge(u,v)<<endl;
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int u,v;
            cin>>u>>v;
            g.removeEdge(u,v);
        }
        else if(ch==8)
        {
            int u;
            cin>>u;
            cout<<"Degree of "<<u<<" is="<<g.getDegree(u)<<endl;
        }
        else if(ch==9)
        {
            int u,v;
            cin>>u>>v;
            cout<<g.hasCommonAdjacent(u,v)<<endl;
        }
        else if(ch==10)
        {
            int u,v;
            cin>>u>>v;
            cout<<"Distance between "<<u<<" and "<<v<<" is="<<g.getDist(u,v)<<endl;
        }
    }

}
