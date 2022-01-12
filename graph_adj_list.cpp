#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<iostream>
#include<iomanip>
struct edge{
    int u;
    int v;
};
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

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}

void ArrayList::removeItem(int item){
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position){
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength(){
    return length ;
}

bool ArrayList::empty(){
    if(length==0)return true;
    else return false;
}

void ArrayList::printList(){
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList(){
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList;
    int *color,*parent,*dist,*f,time ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int  getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int  getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source); //will run dfs in the graph
    void dfs_visit(int source);
    void printBridges(void);
};


Graph::Graph(bool dir){
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    color=0;
    parent=0;
    dist=0;
    f=0;
    time=0;
    directed = dir ;
    //set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n){
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];
    f=new int[nVertices];
}

void Graph::addEdge(int u, int v){
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v){
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v){
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    else if(adjList[u].searchItem(v)==NULL_VALUE) return false;
    else return true;
}

int Graph::getDegree(int u){
    if(u<0||u>=nVertices) return NULL_VALUE;

    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v){
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

    int lengthu=adjList[u].getLength();
    int lengthv=adjList[v].getLength();

    for(int i=0; i<lengthu; i++)
    {
        int itemu=adjList[u].getItem(i);
        for(int j=0; j<lengthv; j++)
        {
            if(itemu==adjList[v].getItem(j))
                return true;
        }
    }
    return false;
}

void Graph::bfs(int source){
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
        int lengthadju=adjList[u].getLength();
        for(int i=0; i<lengthadju; i++)
        {
            int v=adjList[u].getItem(i);
            if(color[v]==WHITE)
            {
                color[v]=GREY;
                dist[v]=dist[u]+1;
                parent[v]=u;
                q.enqueue(v);
            }
        }
        color[u]=BLACK;
    }


//    printf("\nColor\n");
//    for(int i=0;i<nVertices;i++)
//    {
//    	printf("%2d",color[i]);
//	}
//	printf("\nParent\n");
//	for(int i=0;i<nVertices;i++)
//    {
//    	printf("%2d",parent[i]);
//	}
//	printf("\nDist\n");
//	for(int i=0;i<nVertices;i++)
//    {
//    	printf("%2d",dist[i]);
//	}
//	printf("\n");


}

void Graph::dfs(int source){
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
//    {
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

void Graph::dfs_visit(int source){
    int u=source;
    color[u]=GREY;
    time=time+1;
    dist[u]=time;

    int lengthadju=adjList[u].getLength();
    for(int i=0; i<lengthadju; i++)
    {
        int v=adjList[u].getItem(i);
        if(color[v]==WHITE)
        {
            parent[v]=u;
            dfs_visit(v);
        }
    }
    color[u]=BLACK;
    time=time+1;
    f[u]=time;
}

int Graph::getDist(int u, int v){
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return dist[v];
    //return INFINITY ;
}

void Graph::printGraph(){
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph(){
    delete []adjList;
    delete []color;
    delete []parent;
    delete []dist;
    delete []f;
    adjList=0;
    color=0;
    parent=0;
    dist=0;
    f=0;
}
void Graph::printBridges(void){
    bool x;

    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(isEdge(i,j))
            {
                removeEdge(i,j);

                bfs(0);
                for(int k=0;k<nVertices;k++)
                {
                    if(color[k]==WHITE){
                        printf("(%d,%d) is a bridge\n",i,j);
                        break;
                    }
                }
                addEdge(i,j);
            }
        }
    }
}
//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void){
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
        printf("11. PrintBridges\n");
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
        else if(ch==11)
        {
            g.printBridges();
        }
    }
}
