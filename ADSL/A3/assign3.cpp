#include <iostream>
#include <stdlib.h>
using namespace std;

class node
{
	bool lbit,rbit;
	node*lc,*rc;
	int data;
public:
	node(int x)
{
		lbit=rbit=0;              //1 or 0
		lc=rc=NULL;
		data=x;
}
	friend class TBT;
};

class TBT
{
public:
	node *root;
	TBT()
{
		root = new node(-1);
		root->lbit =0; root->rbit = 1;
		root->lc = root;
		root->rc =root;
}
	void create(int x)
	{
		node *head=root->lc;
		if(head == root)
		{
			head =new node(x);
			head->lc = root;
			head-> rc = root;
			head->lbit = 0;
			head->rbit = 0;
			root->lc=head;
			root->lbit=1;
		}
		else
		{
			insert(head,x);
		}
	}
	void insert(node *t, int x)
	{
		if(t==root)
		{
			t=t->lc;
		}
		if(t->data > x)
		{
			if(t->lbit == 0)                        // SLIGHT CHANGE
				Linsert(t,x);
			else
				insert(t->lc,x);
		}
		else
		{
			if(t->rbit == 0)                         // SLIGHT CHANGE
				Rinsert(t,x);
			else
				insert(t->rc,x);
		}
	}
	void Linsert(node *p,int x)
	{
		node *c=new node(x);

		c->lc = p->lc;
		c->lbit = p->lbit;
		c->rc = p;
		c->rbit=0;

		p->lc = c;
		p->lbit=1;
	}
	void Rinsert(node *p,int x)
	{
		node *c=new node(x);

		c->rc = p->rc;
		c->rbit = p->rbit;
		c->lc = p;
		c->lbit=0;

		p->rc = c;
		p->rbit=1;
	}
	node* in_succ(node* x)
	{
		node* s= x->rc;

		if(x->rbit == 1)
		{
			while(s->lbit == 1)
				s=s->lc;
		}
		return s;
	}

	void inorder(node *t)
	{
		while(1)
		{
			t=in_succ(t);
			if(t == root)
				break;
			cout<<t->lbit<<"   "<<t->data<<"   "<<t->rbit<<endl;
		}
	}
	void preorder(node *t)
	{
		t=t->lc;
		while(1)
		{
			if(t==root)
				return ;

			cout<<t->lbit<<"   "<<t->data<<"   "<<t->rbit<<endl;

			if(t->lbit == 1)
			{
				t=t->lc;
			}
			else
			{
				if(t->rbit == 1)
				{
					t=t->rc;
				}
				else
				{
					while(t->rbit != 1)
					{
						t=t->rc;
					}
					t=t->rc;
				}
			}
		}
	}
	void Delete(node *p , node*t)                 // PROBLEM
	{
		cout<<"pt in delete"<<p->data<<t->data<<endl;
		if( t->lbit==1  &&  t->rbit==1 )
		{
			cout<<"1"<<t->data<<p->data;
			p=t;
			node *c_s=t->rc;
			while( c_s->lbit != 0)
			{
				p=c_s;
				c_s=c_s->lc;
			}
			t->data = c_s->data;
			t = c_s;
		}
		if(t->lbit==0  &&  t->rbit==0 )
		{
			cout<<"2"<<t->data<<p->data;
			if(p->lc == t)
			{
				p->lc=t->lc;
				p->lbit=0;
			}
			else
			{
				p->rc = t->rc;
				p->rbit = 0;
			}
			delete t;
			return;
		}

		if(t->lbit ==0  &&  t->rbit==1 )
		{
			cout<<"3"<<t->data<<p->data<<endl;
			node *t1 = t->rc;
			cout<<"t1"<<t1->data<<endl;
			if(p->rc == t)
				p->rc=t1;
			else
				p->lc = t1;
			while(t1->lbit!=0)
				t1=t1->lc;
			t1->lc =t->lc;
			delete t;
			return;
		}

		if(t->lbit ==1  &&  t->rbit==0 )
		{
			cout<<"4"<<t->data<<p->data;
			node *t1 = t->lc;
			if(p->rc == t)
				p->rc=t1;
			else
				p->lc = t1;
			while(t1->rbit!=0)
				t1=t1->rc;
			t1->rc =t->rc;
			delete t;
			return;
		}
		inorder(root);
	}
	void search_for_del(int x)
	{
		node *p,*q;
		p=root->lc;
		q=p;
		while(p!= root)
		{
			if(p->data > x)
			{
				cout<<"p data"<<p->data;
				q=p;
				p=p->lc;
			}
			else if(p->data < x)
			{
				q=p;
				p=p->rc;
			}
			else
			{
				cout<<"pq"<<p->data<<q->data<<endl;
				Delete(q,p);
				break;
			}
		}
	}
};

int main()
{
	TBT t;
	int ch;
	int x;
	do
	{
		cout<<"1. CREATE"<<endl;
		cout<<"2. INSERT"<<endl;
		cout<<"3. INORDER"<<endl;
		cout<<"4. PREORDER"<<endl;
		cout<<"5. DELETE"<<endl;
		cout<<"6. EXIT"<<endl;
		cin>>ch;
		switch(ch)
		{
		case 1:
		{
			cout<<"ENTER VALUE TO BE ADDED "<<endl;
			cin>>x;
			t.create(x);
			break;
		}
		case 2:
		{
			cout<<"ENTER VALUE TO BE INSERTED"<<endl;
			cin>>x;
			t.insert(t.root,x);
			break;
		}
		case 3:
		{
			cout<<"THE INORDER IS "<<endl;
			t.inorder(t.root);
			break;
		}
		case 4:
		{
			cout<<"THE PREORDER IS "<<endl;
			t.preorder(t.root);
			break;
		}
		case 5:
		{
			cout<<"ENTER THE NUMBER TO BE DELETED "<<endl;
			cin>>x;
			t.search_for_del(x);    // WHICH INTERNALLY CALLS DELETE
			break;
		}
		case 6:
		{
			exit(1);
			break;
		}
		default:
			cout<<"INVALID INPUT "<<endl;
		}
	}while(1);
}


