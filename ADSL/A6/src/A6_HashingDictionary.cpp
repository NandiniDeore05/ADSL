

#include <iostream>
using namespace std;
int MAX=26;

class node
{
	string key;
	string value;
public:
	node()
	{
		key="n";
	}
	node(string key,string value)
	{
		this->key=key;
		this->value=value;
	}
	friend class DICT;
};


class DICT
{
	node Entry[26];
public:
	int HashFun(string);
	void insert_w(string,string);
	int find_w(string);
	void modify_w(string);
	void modify_r(string);
	void delete_w(string);
	void display_w();
	void insert_r(string,string);
	int find_r(string);
	void delete_r(string);
	void display_r();
};

int DICT::HashFun(string s){

	if(s=="n")
	{
		return -1;
	}

	int n=s.at(0);

	if(n>96)
	{
		n=n-32;
	}

	return n%MAX;
}

void DICT::insert_w(string key,string value){

	node p(key,value);

	int n=HashFun(key);

	if(Entry[n].key=="n")
	{
		Entry[n]=p;
	}
	else
	{
		int b=n;
		b++;
		b=b%MAX;

		while(b!=n)
		{
			if(Entry[b].key=="n")
			{
				Entry[b]=p;
				break;
			}

			if(Entry[b].key==key)
			{
				cout<<"Word already present.\n";
			}

			b++;
			b=b%MAX;
		}
	}
}

int DICT::find_w(string key)
{
	int n=HashFun(key);
	if(Entry[n].key==key)
	{
		cout<< "No. of comparison: 1\n";
		return n;
	}
	else
	{
		int count=1;
		int b=n;
		b++;
		b=b%MAX;
		while(b!=n)
		{
			if(Entry[b].key=="n")
			{
				return -1;
			}
			if(Entry[b].key==key)
			{
				count++;
				cout<< "No. of comparison:"<<count<<"\n";
				return b;
			}

			count++;
			b++;
			b=b%MAX;
		}
		return -1;
	}
}

void DICT::delete_w(string key)
{
    node a;
	int n=find_w(key);
	if(n==-1)
	{
		cout<<"Word not present\n";
		return;
	}

	int b=n,p=0;
	b=b%MAX;

	do
	{
		p=HashFun(Entry[b].key);
		if(p==n)
		{
			Entry[n]=Entry[b];
			Entry[b]=a;
			n=b;
		}
		b++;
		b=b%MAX;
	}while(b!=n );

	b=n+1;
	b=b%MAX;
	int x;

	while(b!=n)
	{
		p=HashFun(Entry[b].key);
		if(p==-1)
		{
			break;
		}
		else
		{
			x=p+1;
			x=x%MAX;
			while(x!=b)
			{
				if(HashFun(Entry[x].key)==-1)
				{
					Entry[x]=Entry[b];
					Entry[b]=a;
					n=b;
					b=n+1;
					b=b%MAX;
					while(b!=n )
					{

						p=HashFun(Entry[b].key);
						if(p==n)
						{
							Entry[n]=Entry[b];
							Entry[b]=a;
							n=b;
						}
						 b++;
						 b=b%MAX;
					}

				b=n;
				break;
			}
			x++;
			x=x%MAX;
		}
		b++;
		b=b%MAX;
		}
	}
}

void DICT::modify_w(string s)
{
	int n=find_w(s);

	if(n==-1)
	{
		cout<<"Word not present.\n";
	}
	else
	{
		cout<<"Enter changed Meaning:";
		cin>>Entry[n].value;
	}
}


void DICT::modify_r(string s)
{
	int n=find_w(s);
	if(n==-1)
	{
		cout<<"Word not present.\n";
	}
	else
	{
		cout<<"Enter changed Meaning:";
		cin>>Entry[n].value;
	}
}

void DICT::display_w()
{
	for(int i=0;i<MAX;i++)
	{
		if(Entry[i].key!="n")
		{
			cout<<i<<"->"<<Entry[i].key<<"\t ->"<<Entry[i].value<<"\n";
		}
	}
}

void DICT::insert_r(string key,string value)
{
	int n;
	n=HashFun(key);
	node p(key,value);
	if(Entry[n].key=="n")
	{
		Entry[n]=p;
	}
	else if(HashFun(Entry[n].key)==n)
	{
		int b=n+1;
		while(b!=n)
		{
			if(Entry[b].key=="n")
			{
				Entry[b]=p;
				break;
			}
			b++;
		}
	}
	else
	{
		int b=n+1;
		while(b!=n)
		{
			if(Entry[b].key=="n")
			{
				break;
			}
			b++;
			b=b%MAX;
		}
		Entry[b]=Entry[n];
		Entry[n]=p;
	}
}
void DICT::delete_r(string key)
{
	node a;
	int n=find_w(key);
	if(n==-1)
	{
		cout<<"Word not present\n";
		return;
	}

	int b=n,p=0;
	b=b%MAX;

	do
	{
		p=HashFun(Entry[b].key);
		if(p==n)
		{
			Entry[n]=Entry[b];
			Entry[b]=a;
			n=b;
			break;
		}
		b++;
		b=b%MAX;
	}while(b!=n );

	b=n+1;
	b=b%MAX;
	int x;

	while(b!=n)
	{
		p=HashFun(Entry[b].key);
		if(p==-1)
		{
			break;
		}
		else
		{
			x=p+1;
			x=x%MAX;
			while(x!=b)
			{
				if(HashFun(Entry[x].key)==-1)
				{
					Entry[x]=Entry[b];
					Entry[b]=a;
					n=b;
					b=n+1;
					b=b%MAX;
					break;
				}
				x++;
				x=x%MAX;
			}
			b++;
			b=b%MAX;
		}
	}
}


int main()
{
		int choice,choice1;
		char cont,cont1;
		char ww[10];
		string word,meaning;

		DICT obj,obj1;

		do
		{
			cout<<endl<<endl<<"MENU: "<<endl;
			cout<<"Hashing Function:\n1.Without Replacement\n2.With Replacement.\n\nEnter choice: ";
			cin>>choice;
			switch(choice)
			{
			case 1://Without Replacement
				do
				{
					cout<<endl<<endl<<"MENU:"<<endl;
					cout<<"1.Accept Entry.\n2.Display.\n3.Search for an entry.\n4.Modify."
							"\n5.Delete an entry.\n\n";
					cout<<"Enter choice:";
					cin>>choice1;
					switch(choice1)
					{
						case 1:
							cout<<endl<<endl<<"Enter word and meaning: ";
							cin>>word>>meaning;
							obj.insert_w(word,meaning);
							cout<<endl<<"Successfully added!"<<endl;
							break;

						case 2:
							obj.display_w();
							break;

						case 3:
							cout<<endl<<"Enter word to be searched: ";
							cin>>ww;

							if(obj.find_w(ww)!=-1)
								cout<<endl<<"Word Found!"<<endl;
							else
								cout<<endl<<endl<<"Word not found!"<<endl;

							break;

						case 4:
							cout<<endl<<"Enter word to be modified: ";
							cin>>ww;
							obj.modify_w(ww);
							break;

						case 5:
							cout<<endl<<"Enter word to be deleted: ";
							cin>>ww;
							obj.delete_w(ww);
							break;

					}
					cout<<endl<<endl<<"Do you wish to continue with without replacement operations(y/n)?";
					cin>>cont1;
				}

				while(cont1=='y');
				break;

			case 2:
				//With Replacement
				do
				{
					cout<<endl<<endl<<"MENU:"<<endl;
					cout<<"1.Accept Entry.\n2.Display.\n3.Search for an entry.\n4.Modify."
										"\n5.Delete an entry.\n\n";
					cout<<"Enter choice:";
					cin>>choice1;
					switch(choice1)
					{
						case 1:
							cout<<endl<<endl<<"Enter word and meaning: ";
							cin>>word>>meaning;
							obj1.insert_r(word,meaning);
							cout<<endl<<"Successfully added!"<<endl;
							break;

						case 2:
							obj1.display_w();
							break;

						case 3:
							cout<<endl<<"Enter word to be searched: ";
							cin>>ww;

							if(obj1.find_w(ww)!=-1)
								cout<<endl<<"Word Found!"<<endl;
							else
								cout<<endl<<endl<<"Word not found!"<<endl;
							break;

						case 4:
							cout<<endl<<"Enter word to be modified: ";
							cin>>ww;
							obj1.modify_r(ww);
							break;

						case 5:
							cout<<endl<<"Enter word to be deleted: ";
							cin>>ww;
							obj1.delete_r(ww);
							break;

					}
					cout<<endl<<endl<<"Do you wish to continue with replacement operations(y/n)?";
					cin>>cont1;
				}
				while(cont1=='y');
				break;

			}
			cout<<endl<<endl<<"Do you wish to continue(y/n)?";
			cin>>cont;
		}
		while(cont=='y');
		return 0;
}



