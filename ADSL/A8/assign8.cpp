#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Node
{
    int key,height;
    Node *left,*right;
    string meaning;
public:
    Node(int k):key(k),height(1),left(NULL),right(NULL),meaning(""){}
    friend class AVL;
};
class AVL
{
    Node* root=NULL;
public:
    Node* newNode(int k)
    {
        Node* node = new Node(k);
        return node;
    }
    int node_height(Node *p)
    {
        if(p == NULL)
            return 0;
        return (p->height);
    }
    int getBalance(Node* q)
    {
        if(q == NULL)
            return 0;
        return (node_height(q->left) - (node_height(q->right)));
    }
    Node* rightrotate(Node* p)
    {
        Node *x,*y;
        x = p->left;
        y = x->right;

        //Rotation
        x->right = p;
        p->left = y;

        p->height = 1 + max_node(node_height(p->left),node_height(p->right));  //updating height
        x->height = 1 + max_node(node_height(x->left),node_height(p->right));

        return x;
    }
    Node* leftrotate(Node* p)
    {
        Node *x,*y;
        x = p->right;
        y = x->left;

        //Rotate
        x->left = p;
        p->right = y;

        p->height = 1 + max_node(node_height(p->left),node_height(p->right));  //updating height
        x->height = 1 + max_node(node_height(x->left),node_height(x->right));

        return x;
    }
    int max_node(int a,int b)
    {
        return (a>b)? a:b;
    }
    Node* insert(Node* node, int key)
    {
        if (node == NULL)
            return(newNode(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(node_height(node->left),node_height(node->right));

        int balance = getBalance(node);
        if (balance > 1 && key < node->left->key)
            return rightrotate(node);

        if (balance < -1 && key > node->right->key)
            return leftrotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftrotate(node->left);
            return rightrotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightrotate(node->right);
            return leftrotate(node);
        }
        return node;
    }
    void create(int k)
    {
        if(root == NULL)
            root = new Node(k);
        else
            root = insert(root,k);
    }
    void inorder(Node *root)
    {
        if(root)
        {
            //inorder(root->left);
            cout<<root->key<<" ";
            inorder(root->left);
            inorder(root->right);
        }
    }
    Node* returnroot()
    {
        return root;
    }
};
int main()
{
    AVL obj;
    Node* r=NULL;
    int root,num,choice;
    char ch,ch1;
    do
    {
        cout<<"1.Create AVL Tree\n2.Insert Elements\n3.Inorder\n";
        cout<<"Enter your choice:";
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<"Enter root element:";
            cin>>root;
            obj.create(root);
            break;
        case 2:
            do
            {
                cout<<"Enter element:";
                cin>>num;
                obj.create(num);
                cout<<"Do you want to continue adding elements(Y/N):";
                cin>>ch1;
            }while(ch1 == 'y' || ch1 =='Y');
            break;
        case 3:
            obj.inorder(obj.returnroot());
            cout<<endl;
            break;
        }
        cout<<"Do you want to continue(Y/N):";
        cin>>ch;
    }while(ch == 'y' || ch == 'Y');
    return 0;
}

