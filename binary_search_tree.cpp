#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1
#include<vector>
#include<bits/stdc++.h>
#include<iostream>
using namespace std;
struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;

void initializeTree(){
    root = 0;
}

struct treeNode * searchItem(struct treeNode * node, int item){
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};

struct treeNode * makeTreeNode(int item){
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item){
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}

int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}

int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node){
    if(node==0) return FALSE_VALUE;
    if(node->right==0&&node->left==0) return 1;

    return getSize(node->left)+getSize(node->right)+1;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    int depth=0;
    if(root==0) return -2;
    if(node==0) return -1;
    struct treeNode *temp=root;
    while(temp!=0&&temp!=node)
    {
        if(node->item<temp->item)
        {
            temp=temp->left;
        }
        else temp=temp->right;
        depth++;
    }
    return depth;
}

int calcDepth(int item)//return depth of an item in the tree
{
    if(root==0) return -2;
    struct treeNode *temp;
    temp=searchItem(root,item);
    if(temp==0) return -1;
    else return calcNodeDepth(temp);
}

int deleteItem(struct treeNode * node, int item){
    if(root==0) return -2;
    struct treeNode * temp=root,*temp_prev;
    while(temp!=0&&temp->item!=item)
    {
        if(item<temp->item)
        {
            temp_prev=temp;
            temp=temp->left;
        }
        else
        {
            temp_prev=temp;
            temp=temp->right;
        }
    }
    if(temp==0) return FALSE_VALUE;
    if(getSize(root)==1)
    {
        root=0;
        return TRUE_VALUE;
    }
    if(temp==root&&(root->right==0||root->left==0))
    {
        if(temp->right) root=temp->right;
        else root=temp->left;

    }
    else if(temp->right==0&&temp->left==0)
    {
        if(temp==temp_prev->right)
            temp_prev->right=0;
        else
            temp_prev->left=0;
        free(temp);
    }
    else if(temp->right==0)
    {
        if(temp==temp_prev->right)
            temp_prev->right=temp->left;
        else
            temp_prev->left=temp->left;
        free(temp);
    }
    else if(temp->left==0)
    {
        if(temp==temp_prev->right)
            temp_prev->right=temp->right;
        else
            temp_prev->left=temp->right;
        free(temp);
    }
    else
    {
        struct treeNode * temp1=temp->right,*temp1_prev;
        while(temp1->left!=0)
        {
            temp1_prev=temp1;
            temp1=temp1->left;
        }
        temp->item=temp1->item;
        if(temp1==temp->right)
            temp->right=temp1->right;
        else
            temp1_prev->left=temp1->right;
        free(temp1);


    }
    return TRUE_VALUE;
}

int getMinItem() //returns the minimum item in the tree
{
    if(root==0) return NULL;
    struct treeNode *temp=root;
    while(temp->left!=0)
    {
        temp=temp->left;
    }
    return temp->item;
}

int getMaxItem() //returns the maximum item in the tree
{
    if(root==0) return NULL;
    struct treeNode *temp=root;
    while(temp->right!=0)
    {
        temp=temp->right;
    }
    return temp->item;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    /*	if(root==0) return -2;

        if(node->item<leftBound&&node->right==0) return 0;
        if(node->item==leftBound&&node->right==0) return 1;

        if(node->item>rightBound&&node->left==0) return 0;
        if(node->item==rightBound&&node->left==0) return 1;

        if(node->item>=leftBound&&node->item<=rightBound&&node->left==0&&node->right==0) return 1;
        if((node->item<leftBound||node->item>rightBound)&&node->left==0&&node->right==0) return 0;

        if(node->item>leftBound&&node->item<rightBound&&node->right&&node->left)
         	return rangeSearch(node->right,leftBound,rightBound)+rangeSearch(node->left,leftBound,rightBound)+1;

        if(node->item==leftBound&&node->right!=0)
        	return rangeSearch(node->right,leftBound,rightBound)+1;
        if(node->item==rightBound&&node->left!=0)
        	return rangeSearch(node->left,leftBound,rightBound)+1;


        if(node->left->item<leftBound&&node->item>=leftBound&&node->right!=0)
        	return rangeSearch(node->right,leftBound,rightBound)+1;
        if(node->right->item>rightBound&&node->item<=rightBound&&node->left!=0)
        	return rangeSearch(node->left,leftBound,rightBound)+1;


        if(node->item<leftBound&&node->right!=0)
        	return rangeSearch(node->right,leftBound,rightBound)+1;
        if(node->item>rightBound&&node->left!=0)
        	return rangeSearch(node->left,leftBound,rightBound)+1;
    	if(root==0) return -2;
        if(node->item<leftBound||node->item>rightBound) return 0;
        if(node==0) return 0;
        return  rangeSearch(node->right,leftBound,rightBound)+rangeSearch(node->left,leftBound,rightBound)+1;
        */
    int nLeft,nRight;
    if(node==0) return 0;
    if(node->item>rightBound||node->item<leftBound)
        return rangeSearch(node->right,leftBound,rightBound)+rangeSearch(node->left,leftBound,rightBound);
    else
    {
        nLeft=rangeSearch(node->left,leftBound,rightBound)+1;
        nRight=rangeSearch(node->right,leftBound,rightBound)+1;
    }
    return nLeft+nRight-1;

}

void printInOrder(struct treeNode * node, int height){
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}

int printDist(int a,int b){
    vector<int> arra,arrb;
    struct treeNode *tempa=root,*tempb=root;
    while(tempa->item!=a&&tempa!=0)
    {
        arra.push_back(tempa->item);
        if(a<tempa->item)
            tempa=tempa->left;
        else if(a>tempa->item)
            tempa=tempa->right;
    }
    arra.push_back(tempa->item);
    while(tempb->item!=b&&tempb!=0)
    {
        arrb.push_back(tempb->item);
        if(b<tempb->item)
            tempb=tempb->left;
        else if(b>tempb->item)
            tempb=tempb->right;
    }

    arrb.push_back(tempb->item);
    for(int i=0; i<arra.size(); i++)
    {
        for(int j=0; j<arrb.size(); j++)
        {
            if(arra[i]==arrb[j])
            {
                arra.erase(arra.begin()+i);
                arrb.erase(arrb.begin()+j);

            }
        }
    }

    return arra.size()+arrb.size();

}

int main(void){
    initializeTree();
    while(1){
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. exit.\n");
        printf("8. Max Item   9. Min Item\n");
        printf("10. Get Size  11. CalcDepth(Item)  12.Delete Item\n");
        printf("13. Range Search 14.  Print Distance(a,b) \n");
        int ch;
        scanf("%d",&ch);
        if(ch==1){
            int item;
            scanf("%d", &item);
            insertItem(root, item);
        }
        else if(ch==2){
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
        }
        else if(ch==3){
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4){
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
        }
        else if(ch==5){
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6){
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==7){
            break;
        }
        else if(ch==8){
            if(getMaxItem()!=NULL)
                printf("Max Item is=%d\n",getMaxItem());
            else
                printf("Tree Empty\n");
        }
        else if(ch==9){
            if(getMinItem()!=NULL)
                printf("Min Item is=%d\n",getMinItem());
            else
                printf("Tree Empty\n");
        }
        else if(ch==10){
            printf("Size of tree is=%d\n",getSize(root));
        }
        else if(ch==11){
            int item;
            scanf("%d",&item);
            if(calcDepth(item)==-2) printf("Tree Empty\n");
            else if(calcDepth(item)==-1) printf("Item not in the tree\n");
            else printf("Depth of %d is =%d\n",item,calcDepth(item));
        }
        else if(ch==12){
            int item;
            scanf("%d",&item);
            int ret=deleteItem(root,item);
            if(ret==-2) printf("Tree Empty\n");
            else if(ret==FALSE_VALUE) printf("Item is not in the tree\n");
            else if(ret==TRUE_VALUE) printf("Deleted\n");
        }
        else if(ch==13){
            int leftBound,rightBound;
            scanf("%d%d",&leftBound,&rightBound);
            int ret=rangeSearch(root,leftBound,rightBound);
            if(ret==-2)
                printf("Tree Empty\n");
            else
                printf("Items in range=%d\n",ret);
        }
        else if(ch==14){
            int a,b;
            scanf("%d%d",&a,&b);
            printf("%d",printDist(a,b));
        }
        printInOrder(root,calcNodeHeight(root));
    }
}
