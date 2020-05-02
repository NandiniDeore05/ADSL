#include <iostream>
using namespace std;

class GNode
{
	string city;
	int cost;
	GNode *next;
public:
	GNode(string c,int w)
	{
		city=c;
		cost=w;
		next=NULL;
	}
	friend class Graph;
};

class node{
	string data;
	node* next1;
public:
	node(string x){
		data =x;
		next1=NULL;
	}
	friend class Stack;
	friend class Queue;
};

class Queue{
	node* front,*rear;
public:
	Queue(){
		front=rear=NULL;
	}
	void enqueue(string x){
			if(front==NULL && rear==NULL){
				rear=new node(x);
				front=rear;
			}
			else{
				node* p=new node(x);
				rear->next1=p;
				rear=p;
			}
		}
	void dequeue(){
			if(rear==NULL && front==NULL){
				cout<<"Stack empty.\n";
				return;
			}
			else if(rear==front){
				node* p=rear;
				rear=front=NULL;
				delete p;
				return;
			}
			node* p=front;
			front=front->next1;
			delete p;
		}
	string Top(){
			return front->data;
		}
	int isEmpty(){
		if(front==NULL)
				return 1;
		return 0;
	}
};


class Stack
{
	string stk[100];
	int top;
public:
	Stack()
	{
		top=-1;
	}
	void push(string);
	string pop();
	bool isEmpty();
	bool isFull();
	friend class Graph;
};

bool Stack::isEmpty()
{
	if(top==-1)
		return true;
	else
		return false;
}

bool Stack::isFull()
{
	if(top==99)
		return true;
	else
		return false;
}

void Stack::push(string p)
{
	if(isFull())
		cout<<"OverFlow!"<<endl;
	else
	{
		stk[++top]=p;
	}
}

string Stack::pop()
{
	if(isEmpty())
	{
		cout<<"UnderFlow!"<<endl;
		return NULL;
	}
	else
	{
		string t=stk[top--];
		return t;
	}
}


class Graph
{
	int v,e;
	string cityNames[10];
	GNode *G[10];
public:
	Graph(int n)
	{
		v=n;
		e=0;
		for(int i=0;i<10;i++)
		{
			G[i]=NULL;
		}
	}


	void create();
	void addCity(string);
	void addPath(string,string,int);
	int getIndex(string);
	void display();
	int getVertices();
	int getEdges();
	void delPath(string,string);
	void delCity(string);
	int outdegree(string);
	int indegree(string);
	void BFSTraversal(string);
	void DFSTraversal();
	void BFSTraversal();
	int checkAvailable(string);
};

int Graph::checkAvailable(string c)
{
	int i=0;
	for(i=0;i<v;i++)
	{
		if(cityNames[i]==c)
		{
			return 1;
		}
	}
	return 0;
}

int Graph::getVertices()
{
	return v;
}

int Graph::getEdges()
{
	return e;
}

void Graph::create()
{
	string city;

	for(int i=0;i<v;i++)
	{
		cout<<endl<<"Enter city name: ";
		cin>>city;

		cityNames[i]=city;
	}

	string desCity;
	int cost;

	for(int i=0;i<v;i++)
	{
		cout<<endl<<endl;
		while(1)
		{
			cout<<endl<<"Enter paths for "<<cityNames[i]<<" or 's' to stop: ";
			cin>>desCity;

			if(desCity=="s")
				break;

			cout<<endl<<"Enter cost of flight between "<<cityNames[i]<<" and "<<desCity<<" :";
			cin>>cost;

			addPath(cityNames[i],desCity,cost);
		}
	}
}

void Graph::addPath(string source,string destination,int weight)
{
	e++;
	int si=0;

	si=getIndex(source);

	if(G[si]==NULL)
		G[si]=new GNode(destination,weight);
	else
	{
		GNode *p=G[si];
		while(p->next!=NULL)
			p=p->next;
		p->next=new GNode(destination,weight);
	}
}

void Graph::addCity(string c)
{
	cityNames[v]=c;
	v++;
}

void Graph::display()
{
	cout<<endl<<endl;
	cout<<endl<<"AVAILABLE PATHS: "<<endl<<endl;
	string sCity;

	for(int i=0;i<v;i++)
	{

		GNode *p=G[i];
		sCity=cityNames[i];

		cout<<sCity<<" : ";
		while(p!=NULL)
		{
			cout<<"("<<p->city<<","<<p->cost<<")";
			if(p->next!=NULL)
				cout<<"  ,  ";
			p=p->next;
		}

		cout<<endl;
	}

}

int Graph::getIndex(string c)
{
	int i=0;
	for(i=0;i<v;i++)
	{
		if(cityNames[i]==c)
			break;
	}

	if(i==v)
		return -1;
	else
		return i;
}

void Graph::delPath(string source,string destination)
{
	e--;
	int si=getIndex(source);
	GNode *p=G[si];
	GNode *prev;

	if(p->city==destination)
	{
		G[si]=p->next;
		delete p;
	}
	else
	{
		while(p->city!=destination)
		{
			prev=p;
			p=p->next;
		}

		prev->next=p->next;
		delete p;
	}
}

void Graph::delCity(string c)
{
	int ci=getIndex(c);
	GNode *next,*curr,*p;

	curr=G[ci];

	while(curr!=NULL)
	{
		p=curr;
		next=curr->next;
		delete p;
		e--;
		curr=next;
	}

	G[ci]=NULL;

	for(int i=0;i<v;i++)
	{
		GNode *temp=G[i];

		while(temp!=NULL)
		{
			if(temp->city==c)
			{
				delPath(cityNames[i],c);
				break;
			}
			temp=temp->next;
		}
	}

	int k=ci;
	while(k<v)
	{
		G[k]=G[k+1];
		cityNames[k]=cityNames[k+1];
		k++;
	}
	v--;

}

int Graph::outdegree(string c)
{
	int counter=0;

	int ci=getIndex(c);

	GNode* temp=G[ci];

	while(temp!=NULL)
	{
		counter++;
		temp=temp->next;
	}

	return counter;
}

int Graph::indegree(string c)
{
	int counter=0;

	for(int i=0;i<v;i++)
	{
		GNode *temp=G[i];

		while(temp!=NULL)
		{
			if(temp->city==c)
			{
				counter++;
			}
			temp=temp->next;
		}
	}

	return counter;

}

void Graph::DFSTraversal()
{
	string city;
	string c;
	cout<<endl<<endl;
	int *visited;
	Stack S;
	visited=new int[v];

	for(int i=0;i<v;i++)
		visited[i]=0;

	cout<<endl<<"Enter city with which you want to start DFS traversal: ";
	cin>>c;
	cout<<endl<<endl<<"DFS Traversal is: ";

	S.push(c);

	while(!S.isEmpty())
	{
		city=S.pop();

		if(visited[getIndex(city)]==0)
		{
			cout<<city<<" ";
			visited[getIndex(city)]=1;
		}

		int ci=getIndex(city);

		GNode* temp=G[ci];

		while(temp!=NULL)
		{
			if(visited[getIndex(temp->city)]==0)
				S.push(temp->city);
			temp=temp->next;
		}
	}
}

void Graph::BFSTraversal()
{
	string city;
	string c;
	Queue Q;

	cout<<endl<<endl;
	int *visited;
	Stack S;
	visited=new int[v];

	for(int i=0;i<v;i++)
		visited[i]=0;

	cout<<endl<<"Enter first city for BFS Traversal: ";
	cin>>c;

	cout<<endl<<endl<<"BFS Traversal is: ";

	Q.enqueue(c);

	while(!Q.isEmpty())
	{
		city=Q.Top();
		Q.dequeue();

		if(visited[getIndex(city)]==0)
		{
			cout<<city<<" ";
			visited[getIndex(city)]=1;
		}

		int ci=getIndex(city);

		GNode* temp=G[ci];

		while(temp!=NULL)
		{
			if(visited[getIndex(temp->city)]==0)
				Q.enqueue(temp->city);
			temp=temp->next;
		}
	}

}

int main() {

	int vertices;

	cout<<": INITIAL CREATION :"<<endl<<endl;

	cout<<endl<<"Enter no. of cities available initially: ";
	cin>>vertices;

	Graph obj(vertices);

	obj.create();
	obj.display();

	int choice;
	char cont;
	string c;
	string s,d;
	int w;
	do
	{
		cout<<endl<<"MENU:"<<endl;
		cout<<"1.Add city.\n2.Add Path.\n3.Display No.of cities present.\n4.Display No. of paths Available."
				"\n5.Display Paths Available.\n6.Delete Path.\n7.Delete City.\n8.Display no.of "
				"flights from a particular city(outdegree).\n9.Display no.offlights coming to a particular "
				"city(indegree).\n10.DFS Traversal.\n11.BFS Traversal.\n"<<endl;
		cin>>choice;

		switch(choice)
		{
			case 1:
				cout<<endl<<"Enter city name to be added: ";
				cin>>c;
				obj.addCity(c);
				cout<<c<<" city added successfully!"<<endl;
				obj.display();
				break;

			case 2:
				cout<<endl<<"Enter source city:";
				cin>>s;
				while(!obj.checkAvailable(s))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid source city:";
					cin>>s;
				}
				cout<<endl<<"Enter destination city: ";
				cin>>d;
				while(!obj.checkAvailable(d))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid destination city:";
					cin>>d;
				}

				cout<<endl<<"Enter cost of flight between "<<s<<" and "<<d<<" :";
				cin>>w;

				obj.addPath(s,d,w);
				obj.display();
				break;

			case 3:
				cout<<endl<<"No. of cities present: "<<obj.getVertices()<<endl;
				break;

			case 4:
				cout<<endl<<"No. of paths available: "<<obj.getEdges()<<endl;
				break;

			case 5:
				obj.display();
				break;

			case 6:
				cout<<endl<<"For deleting path: "<<endl;
				cout<<endl<<"Enter source city: ";
				cin>>s;
				while(!obj.checkAvailable(s))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid source city:";
					cin>>s;
				}
				cout<<endl<<"Enter destination city: ";
				cin>>d;
				while(!obj.checkAvailable(d))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid destination city:";
					cin>>d;
				}
				obj.delPath(s,d);
				cout<<endl<<"Path deleted successfully!"<<endl;
				obj.display();
				break;

			case 7:
				cout<<endl<<"Enter city to be deleted:";
				cin>>c;
				while(!obj.checkAvailable(c))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid city name :";
					cin>>c;
				}
				obj.delCity(c);
				obj.display();
				break;

			case 8:
				cout<<endl<<"Enter city name for counting its outgoing paths: ";
				cin>>c;
				while(!obj.checkAvailable(c))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid city name :";
					cin>>c;
				}
				cout<<endl<<"No. of paths from "<<c<<" : "<<obj.outdegree(c)<<endl;
				break;

			case 9:
				cout<<endl<<"Enter city name for counting its incoming paths: ";
				cin>>c;
				while(!obj.checkAvailable(c))
				{
					cout<<endl<<"City not present!\n";
					cout<<endl<<"Enter valid city name :";
					cin>>c;
				}
				cout<<endl<<"No. of paths to "<<c<<" : "<<obj.indegree(c)<<endl;
				break;

			case 10:
				obj.DFSTraversal();
				break;

			case 11:
				obj.BFSTraversal();
				break;

		}

		cout<<endl<<endl<<"Do you wish to continue(y/n)?";
		cin>>cont;
	}
	while(cont=='y');




	return 0;
}



