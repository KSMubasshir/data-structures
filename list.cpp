#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;

int shrink();

void initializeList()
{
    listMaxSize = LIST_INIT_SIZE;
    list = (int*)malloc(sizeof(int)*listMaxSize) ;
    length = 0 ;
}

int searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

int insertItem(int newitem)
{
    if(list==NULL)
    {
        initializeList();
    }
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    }
    list[length] = newitem ; //store new item
    length++ ;
    return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
    if ( position >= length ) return NULL_VALUE;
    list[position] = list[length-1] ;
    length-- ;
    shrink();
    return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return NULL_VALUE;
    deleteItemAt(position) ;
    shrink();
    return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("\n\nCurrent size: %d, current length: %d\n\n", listMaxSize, length);
}



// ===========================// My Implementations//===================================





int getLength()
{
    return length;
}

int insertItemAt(int pos, int item)
{
    if(pos<length)
    {
        if (length == listMaxSize)
        {
            int *tempList;
            //allocate new memory space for tempList
            listMaxSize = 2 * listMaxSize ;
            tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
            int i;
            for( i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
        }
        list[length] = list[pos];
        list[pos]=item;
        length++ ;
        return SUCCESS_VALUE ;
    }
    else
    {
        return NULL_VALUE;
    }
}

int shrink()
{
    if(length==LIST_INIT_SIZE)
    {
        return NULL_VALUE;
    }
    else
    {
        if(2*length==listMaxSize)
        {
            int *tempList;
            //allocate new memory space for tempList
            listMaxSize =  listMaxSize/2 ;
            tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
            int i;
            for( i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
            return SUCCESS_VALUE ;
        }
        else
        {
            return NULL_VALUE;
        }
    }
}

int deleteLast()
{
    if(length>0)
    {
        length--;
        shrink();
        return SUCCESS_VALUE;
    }
    else return NULL_VALUE;
}

int clear()
{
    if(list)
    {
        free(list);
        list=NULL;
        length=0;
        listMaxSize=0;
        return SUCCESS_VALUE;
    }
    else return NULL_VALUE;
}


int deleteAll()
{
    if(listMaxSize==LIST_INIT_SIZE)
    {
        list[0]=list[1]=NULL;
        length=0;
    }
    else
    {
        free(list);
        listMaxSize=LIST_INIT_SIZE;
        list = (int*)malloc(sizeof(int)*listMaxSize) ;
        length = 0 ;
    }
}

int removeDuplicate(int item)
{
    int found=0,index=0,i=0,j=0,count=0;
    for(i=0; i<length; i++)
    {
        if(list[i]==item)
        {
            found=1;
            index=i;
            //length--;
            break;
        }
    }
    if(found)
    {
        for(i=index+1; i<length; i++)
        {
            if(list[i]==item)
            {
                count++;
                for(j=i; j<length-1; j++)
                {
                    list[j]=list[j+1];
                }

            }
        }
    }
    //length-=count;
    //shrink();
    for(i=0;i<count;i++)
    {
        length--;
        shrink();
    }
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item.\n2. Delete item at.\n3. Delete item.\n");
        printf("4. Get Length.\n5. Insert Item at(Position,Item) \n6. Delete last item\n");
		printf("7. Clear\n8. Delete All\n9. Remove Duplicate\n10. Print. \n11.exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4){
        	printf("Length of the list is=%d\n",getLength());
		}
        else if(ch==5)
        {
        	int item,pos;
        	scanf("%d%d",&pos,&item);
        	insertItemAt(pos,item);
		}
        else if(ch==6)
         	deleteLast();

        else if(ch==7)
		{
			clear();
        }
		else if(ch==8)
			deleteAll();
        else if(ch==9)
        {
            int item;
            scanf("%d",&item);
            removeDuplicate(item);
        }
        else if(ch==10){
            printList();
        }
        else if(ch==11)
        {
            break;
        }
    }

}

