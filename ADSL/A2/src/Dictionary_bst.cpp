#include <iostream>
#include <cstring>
using namespace std;
class node{
	string keyword;
	string meaning;
	node * right;
	node * left;
public:
	node()
{
		right = left = NULL;
}
	node(string k,string m)
	{
		keyword = k;
		meaning = m;
		right = left = NULL;
	}
	friend class bst;
};
class bst{
	node * root;
public:
	bst()
{
		root = NULL;
}
	void create(string k,string m);
	node * insert(node * n,string k,string m);
	void inorder(node * n);
	void inorderD(node * n);
	void deleteTree(node * n);
	node *deleteNode(node * n,string k);
	void find(node * n,string k);
	int height(node * n,string k);
	node *inSucc(node *n);
	void update();
	int compare(node *n);
	void copy(node *,node *);
	void operator = (bst T);
	node *ret_root()
	{
		return root;
	}
	void outputD()
	{
		cout<<"Inorder(descending) : "<<endl;
		inorderD(root);
	}
	void erase(string k)
	{
		deleteNode(root,k);
	}
	void erase1()
	{
		deleteTree(root);
		cout<<"Tree deleted"<<endl;
	}
	void input(string k,string m)
	{
		if(root == NULL)
			create(k,m);
		else
		{
			insert(root,k,m);
		}
	}
	void output()
	{
		cout<<"Inorder : "<<endl;
		inorder(root);
	}
};
void bst::create(string k,string m)
{
	if(root == NULL)
	{
		root = new node(k,m);
	}
	else{
		root = insert(root,k,m);
	}
	cout<<"Tree created"<<endl;
}
node* bst::insert(node*n,string k,string m)
{
	int i;
	if(n ==  NULL)
	{
		n = new node(k,m);
		return n;
	}
	else
	{
		i = k.compare(n->keyword);
		if(i<0)
			n->left = insert(n->left,k,m);
		else if(i==0)
		{
			cout<<"Duplicate entries not allowed"<<endl;
			return n;
		}
		else
			n->right = insert(n->right,k,m);

		return n;
	}
}
void bst::inorder(node * n)
{
	if(n == NULL)
	{
		return;
	}
	else
	{
		inorder(n->left);
		cout<<n->keyword<<" : "<<n->meaning<<endl;
		inorder(n->right);
		return;
	}
}
void bst::update()
{
	string k,k1,m;
	cout<<"\nEnter the keyword to be updateted";
	cin>>k;
	root=deleteNode(root,k);
	cout<<"\nEnter the new keyword";
	cin>>k1;
	cout<<"\nEnter the new meaning";
	cin>>m;
	insert(root,k1,m);
}
void bst::deleteTree(node * n)
{
	if(n == NULL)
		return;
	else{
		deleteTree(n->left);
		deleteTree(n->right);

		cout<<n->keyword<<" : "<<n->meaning<<" node deleted"<<endl;
		delete n;
		return;
	}
}
void bst::copy(node *T,node *T1)
{
	if(T->left !=NULL)
    {
        T1->left=new node(T->left->keyword,T->left->meaning);
        copy(T->left,T1->left);
    }
    if(T->right !=NULL)
    {
        T1->right=new node(T->right->keyword,T->right->meaning);
        copy(T->right,T1->right);
    }
}

void bst::operator =(bst T)
{
     root=new node(T.root->keyword,T.root->meaning);
     copy(T.root,root);
}
node * bst::deleteNode(node * n,string k)
{
	node * temp = n;
	if(root==NULL)
	{
		return NULL;
	}
	else
	{
		if(k< n->keyword)
		{
			n->left=deleteNode(n->left,k);
			return n;
		}
		else if(k> n->keyword)
		{
			n->right=deleteNode(n->right,k);
			return n;
		}
		else
		{
		if(n->keyword == k)
		{
			if(n->left == NULL && n->right == NULL)
			{
				delete n;
				return NULL;
			}
			else if(n->left==NULL)
			{
				temp=n->right;
				delete n;
				return temp;
			}
			else if(n->right==NULL)
			{
				temp=n->left;
				delete n;
				return temp;
			}
			else
			{
				temp=inSucc(n->right);
				n->keyword=temp->keyword;
				n->meaning=temp->meaning;
				n->right=deleteNode(n->right,n->keyword);
				return n;
			}
		}

	}
}
}
	node * bst::inSucc(node *n)
	{
		while(n->left!=NULL)
		{
			n=n->left;
		}
		return n;
	}
void bst::inorderD(node *n)
{
	if(n == NULL)
		{
			return;
		}
		else
		{
			inorderD(n->right);
			cout<<n->keyword<<" : "<<n->meaning<<endl;
			inorderD(n->left);
			return;
		}
}
int bst::height(node* n,string  k)
{
    if(root==NULL)
    	return 0;
    else
    {
     if(n->keyword==k)
    {
    	return 1;
    }
     else if(n->keyword < k)
    	 return 1+ height(n->right,k);
     else if(n->keyword >k)
    	 return 1+ height(n->left,k);


}
}
int bst::compare(node* n)
{
	string k;
	cout<<"\nEnter the keyword to be searched";
	cin>>k;
	 return height(n,k);
}
int main() {
	string k,m;bst t,t1;
	int i;node* p;
	do{
		cout<<"Enter: \n1.For creating/inserting in a node in BST."<<endl;
		cout<<"2.For printing tree in ascending order."<<endl;
		cout<<"3.For deleting complete tree."<<endl;
		cout<<"4.Deleting a node."<<endl;
		cout<<"5.For printing tree in descending order."<<endl;
		cout<<"6.Update keyword and meaning."<<endl;
		cout<<"7.Copy the tree"<<endl;
		cout<<"8.Search a keyword"<<endl;
		cout<<"9. To exit"<<endl;
		cin>>i;
		switch(i)
		{
		case 1:
			cout<<"Enter keyword : "<<endl;
			cin>>k;
			cout<<"Enter meaning : "<<endl;
			cin>>m;
			t.input(k,m);
			break;
		case 2:
			t.output();
			break;
		case 3:
			t.erase1();
			break;
		case 4:
			cout<<"Enter keyword to be deleted :"<<endl;
			cin>>k;
			t.erase(k);
			t.output();
			break;
		case 5:
			t.outputD();
			break;
		case 6:
			t.update();
			cout<<"\nUpdated"<<endl;
			break;
		case 7:
			t1=t;
			cout<<"\nSuccessfully Copied"<<endl;
			break;
		case 8:
			p=t.ret_root();
            cout<<t.compare(p)<<endl;
            break;
		case 9:
			i=9;
			break;
		default:
			cout<<"Invalid option"<<endl;
		}
	}while(i != 9);
	return 0;
}
