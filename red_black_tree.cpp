#include <cstdlib>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;

template<typename Key, typename Value>
class RedBlack
{
public:
    RedBlack()
        : root(NULL)
    {
    }

    ~RedBlack()
    {
        DeleteNode(root);
    }

    void Insert(const Key& key, const Value& value)
    {
        Node *node, *parent, *z;

        parent = NULL;
        node = root;
        while (node)
        {
            parent = node;
            if (key < node->key)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        if (!parent)
        {
            z = root = new Node;
            z->key = key;
            z->value = value;
            z->colour = BLACK;
            z->parent = z->left = z->right = NULL;
        }
        else
        {
            z = new Node;
            z->key = key;
            z->value = value;
            z->colour = RED;
            z->parent = parent;
            z->left = z->right = NULL;

            if (z->key < parent->key)
            {
                parent->left = z;
            }
            else
            {
                parent->right = z;
            }
        }

        Node *uncle;
        bool side;
        while (z->parent && z->parent->colour == RED)
        {
            if ((side = (z->parent == z->parent->parent->left)))
            {
                uncle = z->parent->parent->right;
            }
            else
            {
                uncle = z->parent->parent->left;
            }

            if (uncle && uncle->colour == RED)
            {
                z->parent->colour = BLACK;
                uncle->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == (side ? z->parent->right : z->parent->left))
                {
                    z = z->parent;
                    side ? RotateLeft(z) : RotateRight(z);
                }

                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                side ? RotateRight(z->parent->parent) : RotateLeft(z->parent->parent);
            }
        }

        root->colour = BLACK;
    }

    int Find(const Key& key)
    {
        Node *node = root;
        while (node)
        {
            if (node->key >key)
            {
                node = node->left;
            }
            else if (node->key < key)
            {
                node = node->right;
            }
            else
            {
                return node->value;
            }
        }
        return -99999;
    }

    void Delete(const Key& key)
    {
        Node *node = root;
        while (node)
        {
            if (node->key > key)
            {
                node = node->left;
            }
            else if (node->key < key)
            {
                node = node->right;
            }
            else
            {
                break;
            }
        }

        if (!node || node->key != key)
        {
            return;
        }

        Colour original;
        Node *sub, *old;
        if (!node->left)
        {
            Transplant(node, sub = node->right);
        }
        else if (!node->right)
        {
            Transplant(node, sub = node->left);
        }
        else
        {
            old = Minimum(node->right);
            original = old->colour;
            sub = old->right;

            if (old->parent == node)
            {
                if(sub)
                    sub->parent = node;
            }
            else
            {
                Transplant(old, old->right);
                old->right = node->right;
                old->right->parent = old;
            }

            Transplant(node, old);
            old->left = node->left;
            old->left->parent = old;
            old->colour = node->colour;
        }

        delete node;
        if (original == BLACK)
        {
            bool side;
            Node *sibling;
            while (old != root && old->colour == BLACK)
            {
                if ((side = (old == old->parent->left)))
                {
                    sibling = old->parent->right;
                }
                else
                {
                    sibling = old->parent->left;
                }

                if (sibling->colour == RED)
                {
                    sibling->colour = BLACK;
                    old->parent->colour = RED;
                    side ? RotateLeft(old->parent) : RotateRight(old->parent);
                    sibling = side ? old->parent->right : old->parent->left;
                }

                if (sibling->left->colour == BLACK && sibling->right->colour == BLACK)
                {
                    sibling->colour = RED;
                    old = old->parent;
                }
                else
                {
                    if (BLACK == side ? sibling->right->colour : sibling->left->colour)
                    {
                        sibling->colour = RED;
                        if (side)
                        {
                            sibling->left->colour = BLACK;
                            RotateRight(sibling);
                            sibling = old->parent->right;
                        }
                        else
                        {
                            sibling->right->colour = BLACK;
                            RotateLeft(sibling);
                            sibling = old->parent->left;
                        }
                    }

                    sibling->colour = old->parent->colour;
                    old->parent->colour = BLACK;
                    if (side)
                    {
                        sibling->left->colour = BLACK;
                        RotateLeft(old->parent);
                    }
                    else
                    {
                        sibling->right->colour = BLACK;
                        RotateRight(old->parent);
                    }

                    old = root;
                }
            }
        }
        if(Find(key)!=-99999)
            Delete(key);
    }

    void Dump()
    {
        Dump(root, 0);
    }
    int Max()
    {
        Node *temp=root;
        while (temp->right)
        {
            temp = temp->right;
        }

        return temp->key;
    }

    int Min()
    {
        Node *temp=root;
        while (temp->left)
        {
            temp = temp->left;
        }

        return temp->key;
    }

    void printInOrder()
    {
        printInOrderHelper(root);
    }

private:
    enum Colour
    {
        RED,
        BLACK
    };

    struct Node
    {
        Colour colour;
        Key key;
        Value value;
        Node *parent;
        Node *left;
        Node *right;
    };

    Node *root;
    void printInOrderHelper(Node *node)
    {
        if(!node)
            return ;
        printInOrderHelper(node->left);
        cout<<node->key<<(node->colour?"B":"R")<<" ";
        printInOrderHelper(node->right);
    }
    void RotateLeft(Node *x)
    {
        Node *y;

        y = x->right;
        x->right = y->left;
        if (y->left)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;
        y->left = x;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        x->parent = y;
    }

    void RotateRight(Node *y)
    {
        Node *x;

        x = y->left;
        y->left = x->right;
        if (x->right)
        {
            x->right->parent = y;
        }

        x->parent = y->parent;
        x->right = y;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }

        y->parent = x;
    }

    void Transplant(Node *dest, Node *src)
    {
        if (dest->parent == NULL)
        {
            root = src;
        }
        else if (dest == dest->parent->left)
        {
            dest->parent->left = src;
        }
        else
        {
            dest->parent->right = src;
        }

        if (src)
        {
            src->parent = dest->parent;
        }
    }

    Node *Minimum(Node *tree)
    {
        while (tree->left)
        {
            tree = tree->left;
        }

        return tree;
    }

    void Dump(Node *node, int tabs)
    {
        if (!node)
        {
            return;
        }

        Dump(node->left, tabs + 1);

        for (int i = 0; i < tabs; ++i)
        {
            std::cout << "\t\t";
        }
        std::cout << node->key << (node->colour ? "B" : "R") << std::endl;

        Dump(node->right, tabs + 1);
    }

    void DeleteNode(Node *node)
    {
        if (!node)
        {
            return;
        }

        if (node->left)
        {
            DeleteNode(node->left);
        }

        if (node->right)
        {
            DeleteNode(node->right);
        }

        delete node;
    }
};

int main()
{
    RedBlack<int, int> rbt;
    while(1)
    {
        cout<<1<<". Insert(key,value)"<<endl;
        cout<<2<<". Delete(key)"<<endl;
        cout<<3<<". LookUp(key)"<<endl;
        cout<<4<<". Max"<<endl;
        cout<<5<<". Min"<<endl;
        cout<<6<<". PrintInOrder"<<endl;
        cout<<7<<". Exit"<<endl;
        int choice;
        int key;
        int value;
        cin>>choice;
        if(choice==1)
        {
            cin>>key>>value;
            rbt.Insert(key,value);
        }

        else if(choice==2)
        {
            cin>>key;
            rbt.Delete(key);
        }
        else if(choice==3)
        {
            cin>>key;
            if(rbt.Find(key)!=-99999)
                cout<<"Found"<<endl;
            else
                cout<<"Not Found"<<endl;
        }
        else if(choice==4)
        {
            cout<<rbt.Max()<<endl;
        }
        else if(choice==5)
        {
            cout<<rbt.Min()<<endl;
        }
        else if(choice==6){
            rbt.printInOrder();
            cout<<endl;
        }
        else if(choice==7)
            return 0;
    }
}
