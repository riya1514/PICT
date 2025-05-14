#include<iostream>
#include<fstream>
#define size 5
using namespace std;

class Student
{
	private :
		int roll_no;
		string name;
		char division;
		string address;
		
	public :
		Student()
		{
			roll_no = 0;
			division = ' ';
			name = address = "";
		}
		
		Student(int r, string n, char d, string a)
		{
			roll_no = r;
			division = d;
			name = n;
			address = a;
		}
		
		void display(fstream &fobj);
		void search(fstream &fobj, string sname);
		void delete_std(fstream &fobj, string sname);
		friend fstream& operator<<(fstream &fobj, Student &std);
		friend fstream& operator>>(fstream &fobj, Student &std);
		friend ostream& operator<<(ostream &dout, Student &std);
};

void Student::display(fstream &fobj)
{
	fobj.open("sample.txt",ios::in);
	Student std;
	
	while(1)
	{
		fobj>>std;
		if(fobj.eof())
		{
			break;
		}
		cout<<std;
	}
	
	fobj.close();
}

void Student::search(fstream &fobj, string sname)
{
	fobj.open("sample.txt",ios::in);
	Student std;
	int flag;
	
	while(!fobj.eof())
	{
		fobj>>std;
		if(std.name==sname)
		{
			cout<<"\nInformation of "<<sname<<" is as follows \n";
			cout<<std;
			flag = 1;
			break;
		}
	}
	if(flag==0)
	{
		cout<<"\nNot found"<<endl;
	}
	
	fobj.close();
}

void Student::delete_std(fstream &fobj, string sname)
{
	Student arr[size],std;
	int c=0,i=0;
	
    fobj.open("sample.txt",ios::in);
    while(!fobj.eof())
    {
        fobj>>std;
        if(std.name!=sname)
        {
        	arr[i]=std;
        	c++;
        	i++;
		}
    }
    fobj.close();
    
    fobj.open("sample.txt",ios::out);
    
    for(int i=0 ; i<=c-1 ; i++)
    {
    	fobj<<arr[i];
    	cout<<arr[i];
	}
    
    fobj.close();
}

fstream& operator<<(fstream &fobj, Student &std)
{
	fobj<<std.roll_no<<endl;
    fobj<<std.name<<endl;
    fobj<<std.division<<endl;
    fobj<<std.address<<endl;
    fobj<<endl;
    return fobj;
}

fstream& operator>>(fstream &fobj, Student &std)
{
	fobj>>std.roll_no;
    fobj>>std.name;
    fobj>>std.division;
    fobj>>std.address;
    return fobj;
}

ostream& operator<<(ostream &dout, Student &std)
{
	dout<<"\nRoll no. = "<<std.roll_no<<endl;
    dout<<"Name = "<<std.name<<endl;
    dout<<"Division = "<<std.division<<endl;
    dout<<"Address = "<<std.address<<endl;
    dout<<endl;
    return dout;
}

int main()
{
	Student std;
    int choice=0;
    int n;
    fstream myfile;
    string path = "sample.txt";
    
    while(choice!=5)
    {
        cout<<endl<<"Press \n1.Add record to file \n2.Display all records \n3.Search by name \n4.Delete a record \n5.Exit \nEnter your choice = ";
        cin>>choice;
        if(choice==1)
        {
            myfile.open("sample.txt",ios::app);
            cout<<"\nEnter number of entries = ";
            cin>>n;
            for(int i=0 ; i<n ; i++)
            {
                int roll_no;
                string name;
                char div;
                string add;
                cout<<"\nEnter roll no = ";
                cin>>roll_no;
                cout<<"Enter name = ";
                cin>>name;
                cout<<"Enter division = ";
                cin>>div;
                cout<<"Enter address = ";
                cin>>add;
                Student s(roll_no,name,div,add);
                myfile<<s;
            }
            myfile.close();
        }
        else if(choice==2)
        {
            std.display(myfile);
        }
        else if(choice==3)
        {
            string sname;
            cin.ignore(1);
            cout<<"\nEnter the name to search:";
            getline(cin,sname);
            std.search(myfile,sname);
        }
        else if(choice==4)
        {
            string sname;
            cin.ignore(1);
            cout<<"\nEnter name to delete = ";
            getline(cin,sname);
            std.delete_std(myfile,sname);
        }
        else if(choice==5)
        {
        	cout<<endl<<"Exit";
        	break;
		}
		else
		{
			cout<<"\nInvalid choice \n";
		}
    }

	return 0;
}

