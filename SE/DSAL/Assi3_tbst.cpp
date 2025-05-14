#include<iostream>
using namespace std;

class Node
{
	public :
		int data;
		Node *left;
		Node *right;
		bool lthread;
		bool rthread;
		
	public :
		Node()
		{
			data = 0;
			left = right = NULL;
			lthread = rthread = 1;
		}
		
		Node(int x)
		{
			data = x;
			left = right = NULL;
			lthread = rthread = 1;
		}
};

class TBST
{
	private :
		Node *root,*head;
	
	public :
		TBST()
		{
			head = new Node(-9999);
			root = NULL;
			head->right = head;
		}
		
		Node* getroot()
		{
			return root;
		}
		
		void insert(int key);
		void inorder();
		void preorder();
		void search(int x);
		void delete_node(int x);
};

void TBST::insert(int x)
{
	if(root==NULL)
	{
		root = new Node(x);
		head->left = root;
		head->lthread = 0;
		root->left = head;
		root->right = head;
		return;
	}
	else
	{
		Node* par = root;
		Node *p = new Node(x);
		
		while(1)
		{
			if(x == par->data)
			{
				cout<<"\nDuplicate key"<<endl;
				delete p;
				return;
			}
			else if(x < par->data)
			{
				if(par->lthread == 0)
				{
					par = par->left;
				}
				else
				{
					p->left = par->left;
					p->right = par;
					par->left = p;
					par->lthread = 0;
					return;
				}
			}
			else
			{
				if(par->rthread == 0)
				{
					par = par->right;
				}
				else
				{
					p->right = par->right;
					p->left = par;
					par->right = p;
					par->rthread = 0;
					return;
				}
			}
		}
	}
}

void TBST::inorder()
{
	Node *temp = root;
	
	while(temp->lthread != 1)
	{
		temp = temp->left;
	}
	
	while(temp != head)
	{
		cout<<temp->data<<" "<<"lbit = "<<temp->lthread<<" rbit = "<<temp->rthread<<endl;
		
		
		if(temp->rthread == 0)
		{
			temp = temp->right;
			while(temp->lthread != 1)
			{
				temp = temp->left;
			}
		}
		else
		{
			temp = temp->right;
		}
	}
	
	cout<<endl;
}

void TBST::preorder()
{
	Node *temp = root;
	bool flag;
	
	while(temp != head)
	{
		if(flag==0)
		{
			cout<<temp->data<<" ";
		}
		if(flag==0 && temp->lthread==0)
		{
			temp = temp->left;
		}
		else
		{
			flag = temp->rthread==1 ? 1 : 0;
			temp = temp->right;
		}
	}
	cout<<endl;
}

void TBST::search(int x)
{
	Node *curr = root;
	int flag = 0;
	
	while(curr!=head)
	{
		if(curr->data == x)
		{
			flag = 1;
			break;
		}
		else
		{
			if(curr->data < x)
			{
				curr = curr->right;
			}
			else
			{
				curr = curr->left;
			}
		}
	}
	
	if(flag==1)
	{
		cout<<"\nFound"<<endl;
	}
	else
	{
		cout<<"\nNot found"<<endl;
	}
}

void TBST::delete_node(int x)
{
	Node *par,*curr;
	par = NULL;
	curr = root;
	
	while(curr!=head)
	{
		if(curr->data == x)
		{
			break;
		}
		else
		{
			par = curr;
			if(curr->data < x)
			{
				curr = curr->right;
			}
			else
			{
				curr = curr->left;
			}
		}
	}
	
	if(curr->lthread == 0 && curr->rthread == 0)
	{
		cout<<"\nNode of data = "<<curr->data<<" with 2 child replaced"<<endl;
		Node *succ = curr->right;
		par = curr;
		while(succ->lthread == 0)
		{
			par = succ;
			succ = succ->left;
		}
		curr->data = succ->data;
		curr = succ;
	}
	
	if(curr->lthread == 1 && curr->rthread == 1)
	{
		if(par->left == curr)
		{
			cout<<"\nLeft leaf node of data = "<<curr->data<<" deleted"<<endl;
			par->left = curr->left;
			par->lthread = 1;
			delete curr;
		}
		else
		{
			cout<<"\nRight leaf node of data = "<<curr->data<<" deleted"<<endl;
			par->right = curr->right;
			par->rthread = 1;
			delete curr;
		}
	}
	
	if(curr->lthread == 0 && curr->rthread == 1)
	{
		cout<<"\nNode of data = "<<curr->data<<" with left link only deleted"<<endl;
		Node *temp = curr->left;
		par->left = curr->left;
		while(temp->rthread != 1)
		{
			temp = temp->right;
		}
		temp->right = curr->right;
		delete curr;
	}
	
	if(curr->lthread == 1 && curr->rthread == 0)
	{
		cout<<"\nNode of data = "<<curr->data<<" with right link only deleted"<<endl;
		Node *temp = curr->right;
		par->right = curr->right;
		while(temp->lthread != 1)
		{
			temp = temp->left;
		}
		temp->left = curr->left;
		delete curr;
	}
}

int main()
{
	TBST tbst;

    int choice = -1;
    int temp;

    bool flag = true;

    while (flag)
    {
        cout << "\nPress \n1.Insert a Node \n2.In-Order Traversal \n3.Pre-Order Traversal \n4.Search a key \n5.Delete a key \n6.Exit \nEnter your choice = ";
        cin >> choice;
        
        int value;

        switch (choice)
        {
			case 1:
				cout << "\nEnter number of nodes = ";
				cin >> temp;
				for(int i=0 ; i<=temp-1 ; i++)
				{
					cout << "Enter data = ";
					cin >> value;
					tbst.insert(value);
				}
				break;

			case 2:
				cout << "\nInorder Taversal " << endl;
				tbst.inorder();
				break;

			case 3:
				cout << "\nPreorder Traversal = ";
				tbst.preorder();
				break;
				
			case 4 :
				cout<<"\nEnter key to find = ";
				cin>>value;
				tbst.search(value);
				break;

			case 5:
				cout << "\nEnter node to delete = ";
				cin >> temp;
				tbst.delete_node(temp);
				cout<<endl;
				break;

			case 6:
				cout << "\nExit" << endl;
				flag = false;
				break;

			default:
				cout << "Invalid Input" << endl;
				break;
        }
    }


	return 0;
}
