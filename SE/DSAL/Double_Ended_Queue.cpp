/*A double-ended queue (deque) is a linear list in which additions and deletions may bemade at either end. 
Obtain a data representation mapping a deque into a onedimensional array. Write C++ program to simulate 
deque with functions to add anddelete elements from either end of the deque*/

#include<iostream>
using namespace std;
#define size 3
class Deque
{
	private :
		
		int front,rear,arr[size];
	public :
		
		init()
		{
			front = rear = -1;
		}
		
		int isempty()
		{
			if(rear==-1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
		int isfull()
		{
			if((rear+1)%size==front)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		
		void display()
		{
			int i;
			i = front;
			cout<<"\nQueue = ";
			while(i != rear)
			{
				cout<<arr[i]<<" ";
				i = (i+1)%size;
			}
			cout<<arr[rear];
			cout<<endl;
		}
		
		void add_front(int data)
		{
			if(isempty()==1)
			{
				front = rear = 0;
				arr[front] = data;
			}
			else
			{
				front = (front-1+size)%size ;
				arr[front] = data;
			}
		}
		
		void add_rear(int data)
		{
			if(isempty()==1)
			{
				front = rear = 0;
				arr[rear] = data;
			}
			else
			{
				rear = (rear+1)%size ;
				arr[rear] = data;
			}
		}
		
		int delete_front()
		{
			int data;
			data = arr[front];
			if(front == rear)
			{
				init();
			}
			else
			{
				front = (front+1)%size;
			}
			return data;
		}
		
		int delete_rear()
		{
			int data;
			data = arr[rear];
			if(front == rear)
			{
				init();
			}
			else
			{
				rear = (rear-1+size)%size;
			}
			return data;
		}
};

int main()
{
	Deque que;
	int val,choice;
	que.init();
	
	while(2)
	{
		cout<<"\t\n1.Insert front \n2.Insert rear \n3.Delete front \n4.Delete rear \n5.Print \n6.Exit \nEnter your choice : ";
        cin>>choice;
        switch(choice)
        {
        	case 1 :
        			 if(que.isfull()==1)
        			 {
        			 	cout<<"\nQueue is full"<<endl;
					 }
					 else
					 {
					 	cout<<"\nEnter data to insert = ";
					 	cin>>val;
					 	que.add_front(val);
					 }
					 break;
					 
			case 2 :
        			 if(que.isfull()==1)
        			 {
        			 	cout<<"\nQueue is full"<<endl;
					 }
					 else
					 {
					 	cout<<"\nEnter data to insert = ";
					 	cin>>val;
					 	que.add_rear(val);
					 }
					 break;
					 
			case 3 :
        			 if(que.isempty()==1)
        			 {
        			 	cout<<"\nQueue is empty"<<endl;
					 }
					 else
					 {
					 	val = que.delete_front();
					 	cout<<"\nDeleted element = "<<val<<endl;
					 }
					 break;
					 
			case 4 :
        			 if(que.isempty()==1)
        			 {
        			 	cout<<"\nQueue is empty"<<endl;
					 }
					 else
					 {
					 	val = que.delete_rear();
					 	cout<<"\nDeleted element = "<<val<<endl;
					 }
					 break;
					 
			case 5 :
					 que.display();
					 break;
					 
			case 6 : 
					 cout<<"\nExit";
					 exit(0);
					 break;
					 
			default :
					 cout<<"\nInvalid input"<<endl;
		}
	}

	return 0;
}

