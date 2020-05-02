//Hash Function with chaining
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Node
{
    int key,index;
    Node* next;
    string meaning;
public:
    Node():key(-1),index(-1),next(NULL),meaning(""){}
    Node(int k):key(k),next(NULL),meaning(" "){}
    friend class Hash_link;
};
class Hash_link
{
    Node *arr[10],*table[10];
    int num,limit=10;
public:
    int key_hash(int p)
    {
        return (p%10);
    }
    void insert()
    {
        Node* p,*q;
        cout<<"Enter elements:\n";
        for(int i=0;i<10;i++)
        {
            cin>>num;
            arr[i] = new Node(num);
            table[i] = new Node();
        }
        for(int j=0;j<10;j++)
        {
            int k = key_hash(arr[j]->key);
            if(table[k]->key != -1)
            {
                p = table[k];
                while(p!= NULL)
                {
                    q=p;
                    p = p->next;
                }
                q->next = new Node(arr[j]->key);
            }
            else
                table[k]->key = arr[j]->key;
        }
    }
    void print()
    {
        Node* p;
        cout<<"Hash Table is:\n";
        for(int i=0;i<10;i++)
        {
            cout<<i<<" ";
            p = table[i];
            while(p!=NULL)
            {
                cout<<" "<<p->key;
                p = p->next;
            }
            cout<<endl;
        }
    }
    void delete_key(int key)
    {
        Node *p,*q;
        int k = key_hash(key);
        if(table[k]->key == key)
        {
            p = table[k]->next;
            if(p != NULL)
            {
                table[k]->key = p->key;
                table[k]->next = p->next;
                delete p;
            }
            else
                table[k]->key = -1;
        }
        else
        {
            q = table[k];
            p = q->next;
            while(p != NULL)
            {
                if(p->key == key)
                {
                    q->next = p->next;
                    q=p;
                    delete p;
                }
                p = p->next;
            }
        }
        print();
    }
    int traverse(int q)
	{
		//int n=q;
		while(table[q] != NULL && q <= limit)
		{
			if(q >= limit)
				q=0;
			else
				q++;
		}
		return q;
	}
    void insert_wchain()
    {
        cout<<"Enter elements:\n";
        for(int i=0;i<10;i++)
        {
            cin>>num;
            arr[i] = new Node(num);
            table[i] = new Node();
        }
        for(int j=0;j<10;j++)
        {
            int k = key_hash(arr[j]->key);
            if(table[k]->key != -1)
            {
                int t = traverse(k);
                table[t]= arr[j];
                table[k]->index = t;
            }
            else
                table[k]= arr[j];
        }
    }
    void print_wchain()
    {
        cout<<"Hash Table is:\n";
        cout<<"Array Index\tElements\tIndex";
        for(int i=0;i<10;i++)
        {
            cout<<i<<"\t"<<table[i]->key<<"\t"<<table[i]->index<<endl;
        }
    }
};
int main()
{
    Hash_link obj;
    int choice,choice1,del_key;
    char ch,ch1;
    do
    {
        cout<<"1.Linear Probing with chaining\n2.Linear Probing without chaining\n3.Exit\n";
		cout<<"Enter your choice:";
		cin>>choice;
		switch(choice)
		{
        case 1:
            do
            {
                cout<<"\n1.Insert\n2.Print\n3.Delete\n4.Search\n";
                cin>>choice1;
                switch(choice1)
                {
                case 1:
                    obj.insert();
                    break;
                case 2:
                    obj.print();
                    break;
                case 3:
                    cout<<"Enter key to be deleted:";
                    cin>>del_key;
                    obj.delete_key(del_key);
                    break;
                }
                cout<<"Do you want to continue chaining(Y/N):";
                cin>>ch;
            }while(ch=='y' || ch=='Y');
            break;
        case 2:
            do
            {
                cout<<"\n1.Insert\n2.Print\n3.Delete\n4.Search\n";
                cin>>choice1;
                switch(choice1)
                {
                case 1:
                    obj.insert_wchain();
                    break;
                case 2:
                    obj.print_wchain();
                    break;
                }
                cout<<"Do you want to continue linear probing without chaining(Y/N):";
                cin>>ch1;
            }while(ch=='y' || ch=='Y');
            break;
        case 3:
            exit(0);
            break;
		}
		cout<<"Do you want to continue(Y/N):";
		cin>>ch1;
    }while(ch1=='y' || ch1=='Y');
    return 0;
}

