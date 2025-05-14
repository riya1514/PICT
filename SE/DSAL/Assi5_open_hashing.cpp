#include<iostream>
#include<iomanip>
#define size 10
using namespace std;

class Node
{
	public :
		int key;
		string meaning;
		Node* next;
		
	public :
		Node()
		{
			key = 0;
			meaning = " ";
			next = NULL;
		}
		
		Node(int key, string meaning)
		{
			this->key = key;
			this->meaning = meaning;
			next = NULL;
		}
		
};

class Hashing
{
	private :
		Node* list[size];
		
	public :
		Hashing()
		{
			int i;
			for(i=0 ; i<=size-1 ; i++)
			{
				list[i] = NULL;
			}
		}
		
		int gethash(int key);
		void hashing_fun(int key, string meaning);
		void search(int key);
		void delete_word(int key);
		void print();
};

int Hashing::gethash(int key)
{
	return key%size;
}

void Hashing::hashing_fun(int key, string meaning)
{
	int hash = gethash(key);
	
	Node *p = new Node(key,meaning);
	
	if(list[hash]==NULL)
	{
		list[hash] = p;
	}
	else
	{
		Node *temp = list[hash];
		while(temp->next!=NULL)
		{
			temp = temp->next;
		}
		temp->next = p;
	}
}

void Hashing::search(int key)
{
	int hash = gethash(key);
	int cmp=1,flag=0;
	Node* temp = list[hash];
	
	while(temp!=NULL)
	{
		if(temp->key==key)
		{
			flag = 1;
			break;
		}
		temp = temp->next;
		cmp++;
	}
	
	if(flag==1)
    {
        cout<<"\nFound \nComparisions = "<<cmp;
        cout<<"\nKey = "<<temp->key<<"\nMeaning = "<<temp->meaning<<endl;
    }
    else
    {
        cout<<"\nNot found \nComparisions = "<<cmp<<endl;
    }
}

void Hashing::delete_word(int key)
{
	int hash = gethash(key);
	int cmp=1,flag=0;
	Node* temp = list[hash];
	Node* prev = NULL;
	
	if(temp->key==key && temp->next==NULL)
	{
		flag = 1;
		list[hash] = NULL;
		delete temp;
	}
	else if(temp->key==key && temp->next!=NULL)
	{
		flag = 1;
		list[hash] = temp->next;
		delete temp;
	}
	else
	{
		while(temp!=NULL)
		{
			prev = temp;
			temp = temp->next;
			if(temp->key==key)
			{
				flag = 1;
				prev->next = temp->next;
				delete temp;
				break;
			}
		}
	}
	
	if(flag==1)
    {
        cout<<"\nDeleted \nComparisions = "<<cmp;
    }
    else
    {
        cout<<"\nNot found to delete \nComparisions = "<<cmp<<endl;
    }
}

void Hashing::print()
{
    cout<<"\n*******Dictionary*******"<<endl;
    int i;
    for(i=0 ; i<=size-1 ; i++)
    {
    	if(list[i]==NULL)
    	{
    		cout<<i<<" : "<<endl;
		}
		else
		{
			cout<<i<<" : ";
			Node* temp = list[i];
			while(temp->next!=NULL)
			{
				cout<<temp->key<<"-"<<temp->meaning<<" , ";
				temp = temp->next;
			}
			cout<<temp->key<<"-"<<temp->meaning<<endl;
		}
    }
}

int main()
{
	int key;
	string meaning;
    Hashing hashmap;
    int choice=0;
   
    while(choice!=5)
    {
        cout<<"\nPress \n1.Insert data \n2.Display Dictionary \n3.Search key \n4.Delete key \n5.Exit \nEnter your choice = ";
        cin>>choice;
        cout<<endl;
       
        if(choice==1)
        {
            cout<<"Enter key = ";
            cin>>key;
            cin.ignore(1);
            cout<<"Enter meaning = ";
            getline(cin,meaning);
           
            hashmap.hashing_fun(key,meaning);
        }
        else if(choice==2)
        {
            hashmap.print();
        }
        else if(choice==3)
        {
            cout<<"Enter key to find = ";
            cin>>key;
            hashmap.search(key);
        }
        else if(choice==4)
        {
         	cout<<"Enter key to delete = ";
            cin>>key;
            hashmap.delete_word(key);   
        }
        else if(choice==5)
        {
            cout<<"\nExit"<<endl;
        }
        else
        {
            cout<<"\nInvalid choice"<<endl;
        }
    }

	return 0;
}

