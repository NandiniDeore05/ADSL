#include <iostream>
using namespace std;
class Node
{
        int data;
        Node *lc,*rc;
public:

        Node()
        {  data=0;
           lc=NULL;
           rc=NULL;
        }
        Node(int x)
        {
                data=x;
                lc=NULL;
                rc=NULL;
        }
 friend class Tree;
 friend class Node1;
 friend int equal1(Node *,Node *);
};
class Node1
{
        Node *data1;
        Node1 *next;
public:
        Node1()
        {
                data1=NULL;
                next=NULL;
        }
        Node1(Node *p)
        {
                data1=p;
                next=NULL;
        }
        friend class stack;

};
class stack
{
        Node1 *head;
public:
        stack()
        {
                head=NULL;
        }
        void push(Node *p)
        {
                if(head==NULL)
                {
                        Node1 *q=new Node1(p);
                        head=q;
                }
                else
                {
                        Node1 *q=new Node1(p);
                        q->next=head;
                        head=q;
                }
        }
        Node* pop()
        {   Node1 *q=head;
                Node *p=head->data1;
           head=head->next;
           delete q;
                return p;
        }
        int empty()
        {
                if(head==NULL)
                        return 1;
                else
                        return 0;
        }
        friend class Tree;
};
class Tree
{   int countl;
    int countint;
        Node *root;
public:
        Tree()
        { countl=0;
          countint=0;
          root=NULL;
        }
        Tree(Node *n)
        {
        	root=n;
        }
 void create(int x)
 {  if(root==NULL)
        root=new Node(x);
        else
                {cout<<"\n Tree already created, node will be inserted"<<endl;
                 root=insert(root,x); }
 }
 void insert1(int x)
 {
         insert(root,x);
 }
 Node* insert(Node *T,int x)
 {   char ans;
         if(T==NULL)
         {
           T=new Node(x);
           return T;
         }
   else
   {
           cout<<"\n Where do you want to insert, left/right? (l/r)";
           cin>>ans;
           if(ans=='l')
           {
                   T->lc=insert(T->lc,x);
           }
           else if(ans=='r')
           {
                   T->rc=insert(T->rc,x);
           }
           return T;
   }

 }
 void show1()
 {
         pre(root);
 }
 void pre(Node *p)
 {
         if(p==NULL)
                 return;
         else
         {   cout<<p->data<<endl;
                 pre(p->lc);
                 pre(p->rc);

         }
 }
 void show2()
  {
         in(root);
  }
  void in(Node *p)
  {
         if(p==NULL)
                 return;
         else
         {    in(p->lc);
                 cout<<p->data<<endl;
                 in(p->rc);

         }
  }
  void show3()
   {
         post(root);
   }
   void post(Node *p)
   {
         if(p==NULL)
                 return;
         else
         {
                 post(p->lc);
                 post(p->rc);
                cout<<p->data<<endl;
         }
   }
   void leaf()
   {
           cleaf(root);
   }
  void cleaf(Node*);
  void internal()
  {
          cinternal(root);
  }
  void cinternal(Node*);
  void mirror()
  {
          mirror1(root);
  }
  void mirror1(Node*);
  void operator =(Tree t);
  void neww(Node *T,Tree t);
  void nonrecin();
  void nonrecpre();
  void nonrecpost();
  void erase();
  void erase1(Node*);
  Node* ret_root();
  int  check(Node *,Node *);
  void copy(Node *,Node *);
  friend int equal1(Node *,Node *);
};
void Tree::cleaf(Node *T)
{

	if (T == NULL)
		return;

	else
	{
		if (T->lc == NULL && T->rc == NULL)
		{
			cout << T->data << endl;
		}

		if(T->lc)
		cleaf(T->lc);

		if(T->rc)
		cleaf(T->rc);
	}
}
void Tree::cinternal(Node *T)
{
       if (T == NULL)
		return;

	else
	{

		if (T->data != root->data && (T->lc!=NULL || T->rc!=NULL) )
		{
			cout << T->data << endl;
		}

		if(T->lc)
		cinternal(T->lc);

		if(T->rc)
		cinternal(T->rc);
	}
        }
void Tree::mirror1(Node *T)
{Node *p=NULL;
        if(T->lc!=NULL || T->rc!=NULL)
                {


                        if(T->lc!=NULL)
                        {
                                mirror1(T->lc);
                        }
                        if(T->rc!=NULL)
                        {
                                mirror1(T->rc);
                        }



                          p=T->lc;
                         T->lc=T->rc;
                         T->rc=p;


                }

}
void Tree::copy(Node *T,Node *T1)
{
	if(T->lc !=NULL)
    {
        T1->lc=new Node(T->lc->data);
        copy(T->lc,T1->lc);
    }
    if(T->rc !=NULL)
    {
        T1->rc=new Node(T->rc->data);
        copy(T->rc,T1->rc);
    }
}

void Tree::operator =(Tree T)
{
     root=new Node(T.root->data);
     copy(T.root,root);
}
void Tree::neww(Node *T,Tree t)
{
        if(T->lc!=NULL || T->rc!=NULL)
                {


                        if(T->lc!=NULL)
                        {
                                cinternal(T->lc);
                        }
                        if(T->rc!=NULL)
                        {
                                cinternal(T->rc);
                        }
                }

}
int equal1(Node *T,Node *T1)
{
	if(T==NULL && T1==NULL)
	{
		return 1;
	}
	if(T!=NULL && T1!=NULL)
	{
		return
		{
		    T->data==T1->data && equal1(T->lc,T1->lc) && equal1(T->rc,T1->rc)
		};
	}
		return 0;
}
void Tree::nonrecin()
{ stack s;
  Node *T=root;
        while(1)
        {
                while(T!=NULL)
                { s.push(T);
                  T=T->lc;
                }

                if(s.empty())
                {
                        return;
                }
                T=s.pop();
                cout<<T->data<<"\t";
                T=T->rc;
        }

}
void Tree::nonrecpost()
{
    stack s;
    Node *T=root;
    while(1)
    {
        while(T!=NULL)
        {
            s.push(T);
            if(T->rc !=NULL)
            {
                s.push(T->rc);
                Node *p=new Node(-1);
                s.push(p);
            }
            T=T->lc;
        }
        T=s.pop();
        while(T->data !=-1 || s.empty())
        {
            cout<<T->data<<"\t";
            if(s.empty())
            {
                return;
            }
            else
            {
                T=s.pop();
            }
        }
        if(T->data==-1)
        {

            T=s.pop();
        }

    }
}
void Tree::nonrecpre()
{  stack s;
Node *T=root;
        while(1)
        { while(T!=NULL)
                { cout<<T->data<<"\t ";
                  s.push(T);
                  T=T->lc;
                }

        if(s.empty())
        {
                return;
        }
        T=s.pop();
        T=T->rc;

        }

}
void Tree::erase()
{
     erase1(root);
}
void Tree::erase1(Node *T)
{
        if(T==NULL)
                         return;
                 else
                 {
                         erase1(T->lc);
                         erase1(T->rc);
                        cout<<T->data<<"deleted \t "<<endl;
                        delete T;
                 }

}
Node* Tree::ret_root()
{
	return root;
}
int main() {
Tree t,t1; stack s;
int choice,ele,no,n;
Node *p,*q;
do
{
cout<<"\n What do you want to do?: "
        <<"\n 1. Insert "
        <<"\n 2. Create "
        <<"\n 3. Preorder Traversal"
        <<"\n 4. Inorder Traversal "
        <<"\n 5. Postorder Traversal"
        <<"\n 6. Leaf"
        <<"\n 7. Internal nodes"
        <<"\n 8. Copy"
        <<"\n 9. Mirror"
        <<"\n10. Non-Rec Inorder"
        <<"\n11. Non-Rec Preorder"
        <<"\n12. Non-Rec Postorder"
        <<"\n13. Erase all nodes"
        <<"\n14.Equal"
        <<"\n 15. Exit"<<endl;
cin>>choice;
switch(choice)
{
case 1:  cout<<"\n Enter the element ";
                cin>>ele;
                t.insert1(ele);
                break;
case 2: cout<<"\n Enter the element ";
                cin>>ele;
                t.create(ele);
                break;
case 3: t.show1();
                break;
case 4: t.show2();
                break;
case 5: t.show3();
                break;
case 6: t.leaf();
                break;
case 7: t.internal();
                break;
case 8: t1=t;
                break;
case 9: t1=t;
    t1.mirror();
    cout<<"\nPreorder Traversal"<<endl;
    t1.show1();
    cout<<"\nInorder Traversal"<<endl;
    t1.show2();
    cout<<"\nPreorder Traversal"<<endl;
    t1.show3();
           break;
case 10: t.nonrecin();
             break;
case 11: t.nonrecpre();
             break;
case 12: t.nonrecpost();
             break;
case 13: t.erase();
                 break;
case 14:
	cout<<"\nEnter root of 2 tree";
	cin>>no;
	t1.create(no);
	cout<<"\nEnter no of elements";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"\nEnter element";
		cin>>no;
		t1.insert1(no);
	}
	p=t.ret_root();
	q=t1.ret_root();
	if(equal1(p,q))
	cout<<"\nTrees are Identical";
	else
        cout<<"\nTrees are Not identical";
	break;
case 15:
	break;

}
}while(choice!=15);

return 0;
}


