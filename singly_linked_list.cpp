#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999
struct listNode{
    int item;
    struct listNode * next;
};
struct listNode * list;

void initializeList(){
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	return SUCCESS_VALUE ;
}

int deleteItem(int item){
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0){
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{
		list = list->next ;
		free(temp) ;
	}
	else
	{
		prev->next = temp->next ;
		free(temp);
	}
	return SUCCESS_VALUE ;
}

struct listNode * searchItem(int item){
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0){
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	free(temp);
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList(){
    struct listNode * temp;
    temp = list;
    while(temp!=0){
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
    free(temp);
}

int insertLast(int item){
	struct listNode * temp ;
	struct listNode *newNode;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item=item;
	if(list==0){
		newNode->next=0;
		list=newNode;
		return SUCCESS_VALUE;
	}
    temp = list;
    
    while(temp->next!=0)
    {
        temp = temp->next;
    }
	temp->next=newNode;
	newNode->next=0;
	return SUCCESS_VALUE;
}

int insertBefore(int oldItem, int newItem){
	struct listNode * temp,*prev;
	struct listNode * newNode;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = newItem ;
	
	if(list==0){
		newNode->next=list;
		list=newNode;
		return SUCCESS_VALUE;
	}
    temp = list;
    while(temp!=0&&temp->item!=oldItem)
    {
    	prev=temp;
        temp = temp->next;
    }
    
    if(temp==list){
    	newNode->next=list;
    	list=newNode;
	}
	else if(temp==0){
		newNode->next=list;
    	list=newNode;
	}
	else{
		prev->next=newNode;
		newNode->next=temp;
	}
	return SUCCESS_VALUE;
}

int deleteAfter(int item){
	if(list==0) return NULL_VALUE;
	struct listNode *temp;
	temp = list ; //start at the beginning
	
	while (temp!=0&&temp->item != item){
		temp = temp->next ; //move to next node
	}
	
	if (temp == 0||temp->next==0){		
	 	return NULL_VALUE ;
	 } //item not found to delete
	else
	{
		temp->next = temp->next->next ;
		free(temp->next);
	}
	return SUCCESS_VALUE ;
}

int deleteLast(){
    struct listNode  *temp,*prev;
    if(list==0) return NULL_VALUE;
    temp=list;
    while(temp->next!=0) {
		prev=temp;		
		temp=temp->next;
	}
	if(temp==list){
		free(temp);
    	list=0;
    	return SUCCESS_VALUE;
	}
	prev->next=0;
	free(temp);
    return SUCCESS_VALUE;
}

int main(void){
    initializeList();
    while(1){
        printf("1. Insert new item.  2. Delete item.  3. Search item. \n");
        printf("4. Insert Last  5. Insert Before(Old,New)\n");
		printf("6. Delete After(item)  7.  Delete Last\n");  
        printf("8. Print. 9. exit.\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2){
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==3){
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
		else if(ch==4){
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch==5){
            int old,New;
            scanf("%d%d", &old,&New);
            insertBefore(old,New);
        }
        else if(ch==6){
			int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==7){
        	deleteLast();
        }
        else if(ch==8){
            printList();
        }
        else if(ch==9){
            break;
        }
    }
}
