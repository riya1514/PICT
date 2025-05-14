/*7 B) Write C++ program for storing binary number using doubly linked lists. 
Write functions- a) To compute 1„s and 2„s complement b) Add two binary numbers*/


#include <iostream>
using namespace std;

class Node
{
	public:
		int bit;
		Node * next;
		Node * prev;

		Node()
		{
			next = NULL;
			prev = NULL;
		}
		Node(int x)
		{
			bit = x;
			next = NULL;
			prev = NULL;
		}
};

class DLL
{
	Node * head;
	public:
		

		Node * create()
		{
			int n=4,i,x;

			Node * temp;
			cout<<"Bit 1 : ";
			cin>>x;
			head = new Node(x);
			temp = head;
			for(i=1;i<=n-1;i++)
			{
				cout<<"Bit "<<i+1<<" : ";
				cin>>x;
				temp->next = new Node(x);
				temp->next->prev = temp;
				temp = temp->next;
			}
			return head;
		}

		void display()	
		{
			Node * temp;
			temp = head;

			while(temp!= NULL)
			{
				cout<<temp->bit;
				temp = temp->next;
			}
			cout<<"\n";
		}

		void complement()
		{
			Node * temp;

			//1's complement
			temp = head;
			while(temp!= NULL)
			{
				if(temp->bit == 0)
				{
					temp->bit = 1;
				}
				else if(temp->bit == 1)
				{
					temp->bit = 0;
				}
				temp = temp->next;
			}
			cout<<"1's complement : ";
			display();
			
			//2's complement
			temp = head;
			while(temp->next != NULL)
			{
				temp = temp->next;
			}
			while(temp->bit == 1)
			{
				temp->bit = 0;
				temp = temp->prev;
			}
			temp->bit = 1;
			cout<<"2's complement : ";
			display();
			cout<<"\n";
		}

		void add_Binary(DLL obj1,DLL obj2)
		{
			Node *temp1, *temp2,*temp3;
			DLL obj3;
			temp1 = obj1.head;
			temp2 = obj2.head;
			obj3.head = new Node();
			temp3 = obj3.head;
			for(int i=1;i<=3;i++)
			{
				temp3->next = new Node();
				temp3->next->prev = temp3;
				temp3 = temp3->next;
			}
			int carry = 0;
			//To reach last Node/LSB of List-1 & List-2
			while(temp1->next != NULL)
				temp1 = temp1->next;
			while(temp2->next != NULL)
				temp2 = temp2->next;
			while(temp3->next != NULL)
				temp3 = temp3->next;
			while(temp1 != NULL && temp2 != NULL)
			{
				if(temp1->bit == 0 && temp2->bit == 0)
				{
					if(carry == 0)
					{
						temp3->bit = 0;
					}	
					else if(carry == 1)
					{
						temp3->bit = 1;
						carry = 0;
					}
				}
				
				else if(temp1->bit == 1 && temp2->bit == 1 && temp3->prev == NULL)
				{
					if(carry == 0)
					{
						temp3->bit = 10;
					}	
					else if(carry == 1)
					{
						temp3->bit = 11;
					}
				}
				else if((temp1->bit == 1 || temp2->bit == 1 ) && temp3->prev == NULL)
				{
					if(carry == 0)
					{
						temp3->bit = 1;
					}	
					else if(carry == 1)
					{
						temp3->bit = 10;
					}
				}
				else if(temp1->bit == 0 && temp2->bit == 1)
				{
					if(carry == 0)
					{
						temp3->bit =1;
					}	
					else if(carry == 1)
					{
						temp3->bit = 0;
						carry = 1;
					}
				}
				else if(temp1->bit == 1 && temp2->bit == 0)
				{
					if(carry == 0)
					{
						temp3->bit = 1;
					}	
					else if(carry == 1)
					{
						temp3->bit = 0;
						carry = 1;
					}
				}
				else if(temp1->bit == 1 && temp2->bit == 1)
				{
					if(carry == 0)
					{
						temp3->bit = 0;
						carry = 1;
					}	
					else if(carry == 1)
					{
						temp3->bit = 1;
						carry = 1;
					}
				}
				temp1 = temp1->prev;
				temp2 = temp2->prev;
				temp3 = temp3->prev;
			}
			obj3.display();
		}

};



int main()
{
	DLL obj1,obj2,obj3,temp;

	cout<<"Enter 1st 4 bit(0/1) binary no :\n";
	obj1.create();
	cout<<"Binary no entered : ";
	obj1.display();

	cout<<"\nEnter 2nd 4 bit(0/1) binary no :\n";
	obj2.create();
	cout<<"Binary no entered : ";
	obj2.display();
	
	cout<<"\nAddition : ";
	temp.add_Binary(obj1,obj2);
	
	
	cout<<"\nEnter 3rd 4 bit(0/1) binary no :\n";
	obj3.create();
	cout<<"Binary no entered : ";
	obj3.display();
	
	cout<<"\nComplements of 3rd binary no : ";
	obj3.complement();

	return 0;
}
