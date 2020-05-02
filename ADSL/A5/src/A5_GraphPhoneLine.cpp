#include <iostream>
using namespace std;

class Graph
{
	int **G;
	string cityNames[20];
	int v;
	int e;
public:
	Graph(int n)
	{
		v=n;
		e=0;

		G=new int*[n];
		for(int i=0;i<n;i++)
		{
			G[i]=new int[n];
		}

		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				G[i][j]=0;
	}

	int getIndex(string);
	void readGraph();
	void printGraph();
	void prims();
	void kruskal();
	void sort(int [][3]);
};

void Graph::readGraph()
{
	int p=0;
	int q=0;
	int w=0;
	string s,d;

	string city;

	for(int i=0;i<v;i++)
	{
		cout<<endl<<"Enter city name: ";
		cin>>city;

		cityNames[i]=city;
	}

	while(1)
	{
		cout<<endl<<"Enter source city,destination city and cost of phone line to connect them or 's' to stop: ";
		cin>>s;
		if(s=="s")
			break;
		cin>>d;
		cin>>w;

		p=getIndex(s);
		q=getIndex(d);

		G[p][q]=w;

		G[q][p]=w;
		e++;
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

void Graph::printGraph()
{
	cout<<endl<<endl<<"ADJACENCY MATRIX:"<<endl<<endl;
	cout<<"   ";
	for(int i=0;i<v;i++)
		cout<<cityNames[i]<<"  ";

	cout<<endl<<endl;
	for(int i=0;i<v;i++)
	{	cout<<cityNames[i]<<"  ";
		for(int j=0;j<v;j++)
		{
			cout<<G[i][j]<<"  ";
		}
		cout<<endl<<endl;
	}
}

void Graph::prims()
{
	cout<<endl<<endl<<"BY PRIMS MATHOD:"<<endl;

	cout<<endl<<endl<<"Edges in minimum spanning tree are: "<<endl;

	int *reachSet,*unreachSet;
	int **C;

	C=new int *[v];

	for(int i=0;i<v;i++)
	{
		C[i]=new int[v];
	}

	for(int i=0;i<v;i++)
	{
		for(int j=0;j<v;j++)
		{
			if(G[i][j]==0)
				C[i][j]=-1;
			else
				C[i][j]=G[i][j];
		}
	}


	reachSet=new int[v];
	unreachSet=new int[v];

	for(int i=0;i<v;i++)
	{
		reachSet[i]=0;
		unreachSet[i]=1;
	}

	int count=0;

	int mini=0;
	int minj=0;
	int i=0;
	int j=0;

	int cost=0;

	reachSet[0]=1;
	unreachSet[0]=0;

	while(count<v-1)
	{
		int min=99999;
		for(i=0;i<v;i++)
		{
			for(j=0;j<v;j++)
			{
				if(reachSet[i]==1 && unreachSet[j]==1 && C[i][j]!=-1 && C[i][j]<min)
				{
					min=C[i][j];
					mini=i;
					minj=j;
				}
			}
		}

		cout<<cityNames[mini]<<" "<<cityNames[minj]<<endl;

		cost=cost+C[mini][minj];

		C[mini][minj]=-1;

		reachSet[minj]=1;
		unreachSet[minj]=0;

		count++;
	}

	cout<<endl<<endl<<"Minimum cost= "<<cost<<endl;

}

void Graph::kruskal()
{
	cout<<endl<<endl<<"BY KRUSKAL'S METHOD:"<<endl;

	cout<<endl<<endl<<"Edges in minimum spanning tree are: "<<endl;


	int list1[e][3];      //Storing edge in form (u,v,w)

	int p=0;

	//Creation of list1 containing all edges in the graph
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<i;j++)
		{
			if(G[i][j]!=0)              //Non-zero entry from adjacency matrix is taken as edge
			{
				list1[p][0]=i;
				list1[p][1]=j;
				list1[p][2]=G[i][j];
				p++;
			}
		}
	}

	//Sorting edge list in ascending order according to weight
	sort(list1);

	int *parent;

	parent=new int[v];        //Parent array to check cycles

	for(int i=0;i<v;i++)
	{
		parent[i]=i;
	}

	int count=0;
	int ki=0;
	int kj=0;
	int minCost=0;
	int a=0;
	int b=0;

	while(count<e-1)
	{
		a=list1[count][0];         //Considering an edge from the edge list
		b=list1[count][1];

		if(parent[a]!=parent[b])   //Parent of a if equal to b then it forms a cycle
		{
			cout<<cityNames[b]<<"  "<<cityNames[a]<<endl;
			minCost=minCost+list1[count][2];

			//Updating parent array
			int c=parent[b];
			for(int i=0;i<v;i++)
			{
				if(parent[i]==c)
					parent[i]=parent[a];
			}

		}
		count++;
	}

	cout<<endl<<endl<<"Minimum cost= "<<minCost<<endl;

}

void Graph::sort(int arr[][3])
{
	int temp=0;
	for(int i=0;i<e;i++)
	{
		for(int j=i+1;j<e;j++)
		{
			if(arr[i][2]>arr[j][2])
			{
				//swap
				for(int k=0;k<3;k++)
				{
					temp=arr[i][k];
					arr[i][k]=arr[j][k];
					arr[j][k]=temp;
				}
			}
		}

	}

}

int main() {

	int vertices;

	cout<<endl<<"Enter no. of cities available: ";
	cin>>vertices;

	Graph obj(vertices);

	obj.readGraph();
	obj.printGraph();

	obj.prims();
	obj.kruskal();

	return 0;
}
