#include<stdio.h>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#include<iostream>
using namespace std;
class HeapItem{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap() //constructor
	{
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		heapLength=0;
	}

	~MinHeap() //destructor
	{
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n){
		heapLength = n;
		for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
		{
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key){
        heapLength++;
    	A[heapLength].data=data;
    	A[heapLength].key=key;
    	map[data]=heapLength;
    	buHeapify(heapLength);
    }
    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin(){
		    HeapItem ret=A[1];
		    A[1]=A[heapLength];
		    heapLength--;
		    map[A[1].data]=1;
		    heapify(1);
			return ret;
	}
	
    //The function updates the key value of an existing data
    //stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key){
		int index=map[data];
		bool x;
		if(A[index].key>key) x=true;
		else x=false;
		A[index].key=key;
		if(x)
		 	buHeapify(index);
		else 
			heapify(index);
	}


    //This function returns the key value of a data stored in heap
	float getKey(int data){
		int i = map[data];
		return A[i].key;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
	void heapify(int i){
		int l,r,smallest;
		while(1){
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;

			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}
		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
	void buHeapify(int i){
		int p,l,r,smallest;
		if(i==1) return;
		p=i/2;
		l=2*p;
		r=l+1;
		if(l<=heapLength&&r<=heapLength){
			smallest=(A[l].key<A[r].key)?l:r;
			smallest=(A[smallest].key<A[p].key)?smallest:p;
		}
		else if(l<=heapLength&&r>heapLength){
			smallest=A[p].key<A[l].key?p:l;
		}
		else if(r<=heapLength&&l>heapLength){
			smallest=A[p].key<A[r].key?p:r;
		}
		
		if(A[p].key<=A[smallest].key){
			return;
		}
		else{
			HeapItem temp;
			temp=A[p];
			A[p]=A[smallest];
			map[A[p].data]=p;
			A[smallest]=temp;
			map[A[smallest].data]=smallest;
			buHeapify(p);
		}
	}

    void printHeap(){
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty(){
		if(heapLength==0)return true;
		else return false;
	}
};

int main(){
    int choice;
    int data;
    float key;
    MinHeap heap;
    bool exit = false;
    while(!exit){
        printf("1. Insert 2. RemoveMin 3.Update 4. Print 5. Exit.\n");
        scanf("%d",&choice);
        switch(choice){
	        case 1:
	            scanf("%d%f",&data,&key);
	            heap.insertItem(data, key);
	            heap.printHeap();
	            break;
	        case 2:
	        	if(heap.Empty()){
	        		printf("Heap Empty\n");
				}
				else
				{
		            HeapItem item;
		            item = heap.removeMin();
		            printf("Removed: (%d,%.2f)\n", item.data, item.key);
		            heap.printHeap();
		        }
		        break;
	        case 3:
	            scanf("%d%f",&data,&key);
	            heap.updateKey(data,key);
	            heap.printHeap();
	            break;
	        case 4:
	            heap.printHeap();
	            break;
	        case 5:
	            exit = true;
	            break;
	    }
    }
    return 0;
}
/*

1 35
1 33
1 42
1 10
1 14
1 19
1 27
1 44
1 26
1 31

*/