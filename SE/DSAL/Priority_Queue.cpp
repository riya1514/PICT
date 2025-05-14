#include <iostream>
#include <string.h>
using namespace std;
#define size 3

class Priority_que;

template <class T>
class Item
{
    public :
	    int priority;
	    T data;

    bool operator <= (Item<T> item)
    {
       return(priority<=item.priority);
    }

    friend class Priority_que;
};

class Priority_que
{
    int front, rear;
    Item<string> que[size];

    public : 

    Priority_que()
    {
        front = 0;
        rear = -1;
    }

    int qFull()
    {
        if(rear == size-1)
            return 1;
        else
            return 0;
    }

    int qEmpty()
    {
        if(front == rear+1)
            return 1;
        else
            return 0;
    }

    void add();
    void del();
    void disp();
};

void Priority_que:: add()
{
    if (qFull())
    {
        cout<<"\nQueue Overflow."<<endl;
    }

    else
    {
        rear++;
        Item<string> I;
        cout << "\nEnter data : ";
        cin >> I.data;
        cout << "Enter priority : ";
        cin >> I.priority;

        int i;
        for (i = rear; i > front && I <= que[i-1]; i--)
        {
            que[i].data = que[i-1].data;
            que[i].priority = que[i-1].priority;
        }
        que[i].data = I.data;
        que[i].priority = I.priority;

    }
}

void Priority_que:: del()
{
    if(qEmpty())
    {
        cout<<"\nQueue Underflow."<<endl;
    }
    
    else
    {
        cout<<"\n"<<que[front].data<<" is deleted."<<endl;
        front++;
    }
}

void Priority_que :: disp()
{
    if(qEmpty())
    {
        cout<<"\nQueue Underflow."<<endl;
    }
    
    else
    {
        int i;
        cout<<endl<<"Queue = ";
        for(i=front; i<rear; i++)
        {
            cout<<que[i].data<< "  ";
        }
        cout<<que[i].data<<endl;
    }
}

int main()
{
    Priority_que Q;
    int ch;
    
    while(2)
    {
        cout<<"\n1.Add \n2.Delete \n3.Display \n4.Exit";
        cout<<"\nEnter your choice : ";
        cin>>ch;
        switch(ch)
        {
	        case 1 : 
					 Q.add();
					 break;
					 
	        case 2 : 
					 Q.del();
					 break;
					 
	        case 3 : 
					 Q.disp();
					 break;
					 
	        case 4 : 
					 cout<<"\nExiting.";
					 break;
					 exit(0);
					 
	        default : 
					 cout<<"\nWrong choice."<<endl;
        }
    } 
    
    return 0;
}
