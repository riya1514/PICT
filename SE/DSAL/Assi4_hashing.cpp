#include <iostream>
#include<iomanip>
#define size 10
using namespace std;

class Contact
{
    private :
        string name;
        long long int number;
       
    public :
        Contact()
        {
            name = "";
            number = -1;
        }
       
        Contact(string name, long long int number)
        {
            this->name = name;
            this->number = number;
        }
        friend class Hashing;
};

class Hashing
{
    private :
        Contact *clients;
       
    public :
        Hashing()
        {
            int i;
            clients = new Contact[size];
            for(i=0 ; i<=size-1 ; i++)
            {
                clients[i] = Contact();
            }
        }
       
        int gethash(long long int key);
        void hashing_without_replacement(string name, long long int number);
        void hashing_with_replacement(string name, long long int number);
        void search(long long int number);
        void print();
};

int Hashing::gethash(long long int key)
{
    return key%size;
}

void Hashing::hashing_without_replacement(string name, long long int number)
{
    int hash = gethash(number);
   
    while(clients[hash].number!=-1)
    {
        hash = (hash+1)%size;
    }
    clients[hash].name = name;
    clients[hash].number = number;
    cout<<"\nInserted!"<<endl;
}

void Hashing::hashing_with_replacement(string name, long long int number)
{
    int hash = gethash(number);
    string sname;
    long long int snumber;
   
    if(clients[hash].number==-1)
    {
        clients[hash].name = name;
        clients[hash].number = number;
    }
   
    if(clients[hash].number!=-1)
    {
        int prev = gethash(clients[hash].number);
        if(prev!=hash)
        {
            sname = clients[hash].name;
            snumber = clients[hash].number;
            clients[hash].name = name;
            clients[hash].number = number;
            name = sname;
            number = snumber;
        }
       
        while(clients[hash].number!=-1)
        {
            hash = (hash+1)%size;
        }
       
        clients[hash].name = name;
        clients[hash].number = number;
        cout<<"\nInserted!"<<endl;
    }
}

void Hashing::search(long long int number)
{
    int hash = gethash(number);
    int i=hash;
    int cmp=1,flag=0;
   
    do
    {
        if(clients[i].number==number)
        {
            flag = 1;
            break;
        }
        i = (i+1)%size;
        cmp++;
       
    }while(clients[i].number!=-1 && i!=hash);
   
    if(flag==1)
    {
        cout<<"\nFound \nComparisions = "<<cmp;
        cout<<"\n"<<i<<" : "<<clients[i].name<<" - "<<clients[i].number<<endl;
    }
    else
    {
        cout<<"\nNot found \nComparisions = "<<cmp<<endl;
    }
}

void Hashing::print()
{
    cout<<"\n*******Client's list*******"<<endl;
    cout<<"\nNo  Client name  Number"<<endl;
    int i;
    for(i=0 ; i<=size-1 ; i++)
    {
    	if(clients[i].number==-1)
        {
        	cout<<setw(4)<<left<<i<<setw(13)<<left<<"-"<<"-"<<endl;
		}
		else
		{
			cout<<setw(4)<<left<<i<<setw(13)<<left<<clients[i].name<<clients[i].number<<endl;
		}
    }
}

int main()
{
    string name;
    long long int number;
    Hashing hashmap;
    int choice=0;
   
    while(choice!=5)
    {
        cout<<"\nPress \n1.Insert data without replacement \n2.Insert data with replacement \n3.Display client's list \n4.Search number \n5.Exit \nEnter your choice = ";
        cin>>choice;
        cout<<endl;
       
        if(choice==1)
        {
            cin.ignore(1);
            cout<<"Enter name = ";
            getline(cin,name);
            cout<<"Enter number = ";
            cin>>number;
           
            hashmap.hashing_without_replacement(name,number);
        }
        else if(choice==2)
        {
            cin.ignore(1);
            cout<<"Enter name = ";
            getline(cin,name);
            cout<<"Enter number = ";
            cin>>number;
           
            hashmap.hashing_with_replacement(name,number);
        }
        else if(choice==3)
        {
            hashmap.print();
        }
        else if(choice==4)
        {
            cout<<"Enter number to find = ";
            cin>>number;
            hashmap.search(number);
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

