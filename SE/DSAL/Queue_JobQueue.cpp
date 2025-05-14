/*Queues are frequently used in computer programming, and a 
typical example is the creation of a job queue by an operating 
system. If the operating system does not use priorities, then 
the jobs are processed in the order they enter the system. 
Write C++ program for simulating job queue. Write 
functions to add job, display job and delete job from queue.*/

#include<iostream>
using namespace std;
#define size 5
class Queue
{
	private :
		int front,rear,queue[size];
	public :
		Queue()
		{
			front = rear = -1 ;
		}
		void insert()
		{
			int val;
			if(rear >= size-1)
			{
				cout<<"\nQueue overflow\n";
			}
			else
			{
				cout<<"\nEnter element to insert = ";
				cin>>val;
				if(front==-1)
				{
					front = 0;
				}
				rear++;
				queue[rear]=val;
			}
		}
		
		int deletes()
		{
			int val;
			if(front>rear || rear==-1)
			{
				cout<<"\nQueue underflow\n";
			}
			else
			{
				val = queue[front];
				front++;
			}
			return val;
		}
		
		void display()
		{
			if(rear == -1 || front == rear+1 )
			{
				cout<<"\nQueue is empty\n";
			}
			else
			{
				cout<<"\nQueue = ";
				for(int i=front ; i<=rear ; i++)
				{
					cout<<queue[i]<<" ";
				}
			}
			cout<<endl;
		}
};
int main()
{
	cout<<"------------Queue-------------\n";
	int choice,val;
	Queue obj;
	while(2)
	{
		cout<<"\nPress \n1.Insert element  \n2.Delete element  \n3.Display queue \n4.Exit \nEnter tour choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 : obj.insert();
					 break;
			case 2 : val = obj.deletes();
					 cout<<"\nDeleted element = "<<val<<endl;
					 break;
			case 3 : obj.display();
					 break;
			case 4 : cout<<"\nExit";
					 return 0;
			default : cout<<"\nWrong input\n";
		}
	}

}

