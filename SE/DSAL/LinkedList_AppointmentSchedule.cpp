/*Write C++ program for storing appointment schedule for day. Appointments 
are booked randomly using linked list. Set start and end time and min and 
max duration for visit slot. Write functions for- a) Display free slots b) Book 
appointment c) Cancel appointment (check validity, time bounds, 
availability) d) Sort list based on time e) Sort list based on time using 
pointer manipulation*/

#include <iostream>
using namespace std;
class Node 
{
        int id,start,end,min_duration,max_duration;
        bool status;
        Node *next;
		static int count;
	public:
        Node() 
		{  
                next = NULL;
                count ++;
		        id = count;
		        status = false;
		        cout << "\nEnter start time:";
		        cin >> start;
		        cout << "Enter End Time:";
		        cin >> end;
		        cout << "Enter Max Time: ";
		        cin >> max_duration;
		        cout << "Enter Min Time: ";
		        cin >> min_duration;
        }
    friend class Appointment;

};
int Node::count = 0;

class Appointment 
{
        Node *head;
        
	public:
        Appointment() 
		{
            head = NULL;
        }
        Node * create(int n);
        void display();
        void bookSlot(int id);
        void cancelSlot(int id);

};

Node * Appointment::create(int n) 
{
		int i;
		cout<<"\nEnter data for slot 1 :";
		head = new Node();
		Node *temp = head;
        for(i=1;i<=n-1;i++)
        {
        	cout<<"\nEnter data for slot : "<<i+1;
        	temp->next = new Node();
            temp = temp->next;
        }
		return head;

}

void Appointment::display() 
{

        Node *temp = head;

        if (head == NULL) 
		{
                cout << "No Appointments are created!!!!" << endl;
                return;
        }

        cout << "Id.\tStart\tEnd\tMax\tMin\tStatus" << endl;
        while (temp != NULL) 
		{
                cout << temp->id << "\t" << temp->start << "\t  " << temp->end << "\t"
					<< temp->max_duration << "\t  " << temp->min_duration << "\t";
                if (temp->status) 
				{
                        cout << " Booked" << endl;
                } 
				else 
				{
                        cout << " Free" << endl;
                }
                temp = temp->next;

        }

}

void Appointment::bookSlot(int id) 
{
        Node *temp = head;

        while (temp != NULL) {
                if (temp->id == id) 
				{
					if (temp->status == true)
					{
						cout << "Appointment already booked for id :" << id << endl;
						return;	
					}
					else
					{
						temp->status = true;
                        cout << "Appointment booked for id :" << id << endl;
                        return;	
					}
                }
                temp = temp->next;
        }
        cout << "No such id!!" << endl;

}
void Appointment::cancelSlot(int id) 
{
        Node *temp = head;

        while (temp != NULL) 
		{
                if (temp->id == id) 
				{
                        if (temp->id)
						{
                                temp->status = false;
                                cout << "Appointment canceled for id:" << id << endl;
                                return;
                        }
                        cout << "Appointment not booked yet!" << endl;

                }
                temp = temp->next;
        }
        cout << "No such id!!" << endl;

}

int main() 
{
        cout << "!!!Appointment Booking System!!!" << endl; 

        int choice=0, id, slots;

        Appointment obj;

        while (choice!=5) 
		{
                cout << "\n\t\t Appointment Booking System\n" << endl;

                cout<< "1.Create a Schedule\n2.Show Available Slots\n3.Book a Slot\n4.Cancel Appointment\n5.Exit"
					<< endl;
                cout << "Enter Your Choice: ";
                cin >> choice;

                switch (choice) 
				{
                case 1:
                        cout << "\nCreating Appointment schedule" << endl;
                        cout << "Enter the No of slots for today : ";
                        cin >> slots;
						obj.create(slots);
                        break;
                case 2:
                        cout << "\nAvailable Slots are: " << endl;

                        obj.display();
                        break;

                case 3:
                        cout << "\nBook Slot Facility" << endl;
                        cout << "Enter Id to Book Slot: ";
                        cin >> id;
                        obj.bookSlot(id);
                        break;
                case 4:
                        cout << "\nCancel Slot Facility" << endl;
                        cout << "Enter Id to Cancel Slot: ";
                        cin >> time;
                        obj.cancelSlot(time);
                        break;
                case 5:
                        cout << "\n!!Exit!!" << endl;
                        break;
                default:
                        cout << "Wrong Input" << endl;

                }
        }

        return 0;
}
