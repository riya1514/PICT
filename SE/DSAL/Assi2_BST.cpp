#include<iostream>
#define size 10
using namespace std;

class Node
{
	public :
		Node *left;
		string word;
		string meaning;
		Node *right;
	
	public :
		Node()
		{
			word = meaning = "";
			left = right = NULL;
		}
		
		Node(string word, string meaning)
		{
			this->word = word;
			this->meaning = meaning;
			left = right = NULL;
		}
		
		friend class BST;
};

class Stack
{
	public :
		Node* stk[size];
		int top;
		
		Stack()
		{
			top = -1;
		}
		
		int isempty();
		void push(Node* temp);
		Node* pop();
};

class BST
{
	private :
		Node *root;
		
	public :
		BST()
		{
			root = NULL;
		}
		
		Node* getroot()
		{
			return root;
		}
		
		void create();
		void insert(string word, string meaning);
		void ascending(Node *temp);
		void descending(Node *temp);
		void non_rec_ascending();
		void non_rec_descending();
		void search(string key);
		void update(string key, string meaning);
		void find_max();
		void find_min();
		Node* delete_key(Node* root, string key);
};

int Stack::isempty()
{
	if(top==-1)
	{
		return 1;
	}
	return 0;
}

void Stack::push(Node *temp)
{
	top++;
	stk[top] = temp;
}

Node* Stack::pop()
{
	Node *curr = stk[top];
	top--;
	return curr;
}

//void BST::create()
//{
//	int n,i;
//	string word,meaning;
//	
//	cout<<"Enter no of nodes = ";
//	cin>>n;
//	cin.ignore(1);
//	
//	cout<<"Enter word = ";
//	getline(cin,word);
//	cout<<"Enter meaning = ";
//	getline(cin,meaning);
//	
//	Node *temp,*p;
//	root = new Node(word,meaning);
//	
//	for(i=1 ; i<=n-1 ; i++)
//	{
//		cout<<"Enter word = ";
//		getline(cin,word);
//		cout<<"Enter meaning = ";
//		getline(cin,meaning);
//		
//		p = new Node(word,meaning);
//		temp = root;
//		do
//		{
//			if(word < temp->word)
//			{
//				if(temp->left==NULL)
//				{
//					temp->left = p;
//					temp = p;
//				}
//				else
//				{
//					temp = temp->left;
//				}
//			}
//			else 
//			{
//				if(temp->right==NULL)
//				{
//					temp->right = p;
//					temp = p;
//				}
//				else
//				{
//					temp = temp->right;
//				}
//			}
//		}while(temp!=p);
//	}
//}

void BST::insert(string word, string meaning)
{
	if(root==NULL)
	{
		root = new Node(word,meaning);
	}
	else
	{
		Node *p = new Node(word,meaning);
		Node *temp = root;
		
		do
		{
			if(word < temp->word)
			{
				if(temp->left==NULL)
				{
					temp->left = p;
					temp = p;
				}
				else
				{
					temp = temp->left;
				}
			}
			else 
			{
				if(temp->right==NULL)
				{
					temp->right = p;
					temp = p;
				}
				else
				{
					temp = temp->right;
				}
			}
		}while(temp!=p);
	}
}

void BST::ascending(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	ascending(temp->left);
	cout<<temp->word<<" - "<<temp->meaning<<endl;
	ascending(temp->right);
}

void BST::descending(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	descending(temp->right);
	cout<<temp->word<<" - "<<temp->meaning<<endl;
	descending(temp->left);
}

void BST::non_rec_ascending()
{
	Node *curr = root;
	
	if(curr==NULL)
	{
		return;
	}
	
	Stack stk;
	
	while(curr!=NULL || stk.isempty()!=1)
	{
		while(curr!=NULL)
		{
			stk.push(curr);
			curr = curr->left;
		}
		
		curr = stk.pop();
		cout<<curr->word<<" - "<<curr->meaning<<endl;
		curr = curr->right;
	}
}

void BST::non_rec_descending()
{
	Node *curr = root;
	
	if(curr==NULL)
	{
		return;
	}
	
	Stack stk;
	
	while(curr!=NULL || stk.isempty()!=1)
	{
		while(curr!=NULL)
		{
			stk.push(curr);
			curr = curr->right;
		}
		
		curr = stk.pop();
		cout<<curr->word<<" - "<<curr->meaning<<endl;
		curr = curr->left;
	}
}

void BST::search(string key)
{
	Node *temp = root;
	
	if(temp==NULL)
	{
		return;
	}

	int cmp = 1;
	while(temp!=NULL)
	{
		if(temp->word == key)
		{
			break;
		}
		else if(temp->word > key)
		{
			temp = temp->left;
			cmp++;
		}
		else
		{
			temp = temp->right;
			cmp++;
		}
	}
	
	if(temp!=NULL)
	{
		cout<<"\nFound \nComparisions = "<<cmp;
		cout<<"\nWord = "<<temp->word;
		cout<<"\nMeaning = "<<temp->meaning<<endl;
	}
	else
	{
		cout<<"\nNot found \nComparisions = "<<cmp<<endl;
	}
}

void BST::find_max()
{
	Node *temp = root;
	
	while(temp->right != NULL)
	{
		temp = temp->right;
	}
	cout<<"\nLargest word = "<<temp->word<<" meaning = "<<temp->meaning<<endl;
}

void BST::find_min()
{
	Node *temp = root;
	
	while(temp->left != NULL)
	{
		temp = temp->left;
	}
	cout<<"\nSmallest word = "<<temp->word<<" meaning = "<<temp->meaning<<endl;
}

void BST::update(string key, string meaning)
{
	Node *temp = root;
	
	if(temp==NULL)
	{
		return;
	}
	
	int cmp = 1;
	while(temp!=NULL)
	{
		if(temp->word == key)
		{
			temp->meaning = meaning;
			break;
		}
		else if(temp->word > key)
		{
			temp = temp->left;
			cmp++;
		}
		else
		{
			temp = temp->right;
			cmp++;
		}
	}
	
	if(temp!=NULL)
	{
		cout<<"\nUpdated";
		cout<<"\nComparisions to find "<<key<<" = "<<cmp<<endl;
		cout<<"\nWord = "<<temp->word;
		cout<<"\nMeaning = "<<temp->meaning<<endl;
	}
	else
	{
		cout<<"\nNot found \nComparisions to find = "<<key<<" = "<<cmp<<endl;
	}
}

Node* BST::delete_key(Node* root, string key)
{
	if(root==NULL)
	{
		return root;
	}
	
	if(root->word > key)
	{
		root->left = delete_key(root->left,key);
		return root;
	}
	else if(root->word < key)
	{
		root->right = delete_key(root->right,key);
		return root;
	}
	
	if(root->left == NULL)
	{
		Node* temp = root->right;
		root = NULL;
		return temp;
	}
	else if(root->right == NULL)
	{
		Node* temp = root->left;
		root = NULL;
		return temp;
	}
	else
	{
		Node* succ_parent = root;
		Node* succ = root->right;
		
		while(succ->left != NULL)
		{
			succ_parent = succ;
			succ = succ->left;
		}
		
		if(succ_parent != root)
		{
			succ_parent->left = succ->right;
		}
		else
		{
			succ_parent->right = succ->right;
		}
		
		root->word = succ->word;
		root->meaning = succ->meaning;
		
		succ = NULL;
		return root;
	}
}

int main()
{
	BST b1;

	int n,choice=0;
	string str,str2,word,meaning;;
	Node* temp;
	
	while(choice!=10)
	{
		cout<<endl<<"Press \n1.Create \n2.Show in ascending order \n3.Show in decending order \n4.Insert word \n5.Search \n6.Update meaning \n7.Find largest word \n8.Find smallest word \n9.Delete word \n10.Exit \nEnter your choice = ";
		cin>>choice;
		cout<<endl;
		switch(choice)
		{
		
			case 1:
				cout<<"Enter the no of nodes = ";
				cin>>n;
				cin.ignore(1);
				for(int i=0;i<n;i++)
				{
					cout<<endl<<"Enter the word = ";
					getline(cin,word);
					cout<<"Enter the meaning = ";
					getline(cin,meaning);
					b1.insert(word , meaning);
				}
				break;
				
			case 2 :
				if(b1.getroot()==NULL)
				{
					cout<<"\nDictionary not created";
					break;
				}
				cout<<endl<<"Words on ascending order"<<endl;
				b1.non_rec_ascending();
				cout<<endl;
				break;
				
			case 3 :
				if(b1.getroot()==NULL)
				{
					cout<<"\nDictionary not created";
					break;
				}
				cout<<endl<<"Words on decending order"<<endl;
				b1.non_rec_descending();
				cout<<endl;
				break;
				
			case 4 :
				cin.ignore();
				cout<<endl<<"Enter the word = ";
				getline(cin,word);
				cout<<"Enter the meaning = ";
				getline(cin,meaning);
				b1.insert(word , meaning);
				break;
				
			case 5 :
				if(b1.getroot()==NULL)
				{
					cout<<"\nDictionary not created";
					break;
				}
				cin.ignore();
				cout<<"Enter word to find = ";
				getline(cin,str);
				b1.search(str);
				break;
				
			case 6 :
				if(b1.getroot()==NULL)
				{
					cout<<"\nDictionary not created";
					break;
				}
				cin.ignore();
				cout<<"Enter word to update meaning = ";
				getline(cin,str);
				cout<<"Enter meaning = ";
				getline(cin,str2);
				b1.update(str, str2);
				break;
				
			case 7 :
				b1.find_max();
				break;
				
			case 8 :
				b1.find_min();
				break;
				
			case 9 :
				cin.ignore();
				cout<<"Enter word to delete = ";
				getline(cin,str);
				b1.delete_key(b1.getroot(),str);
				break;
				
			case 10 :
				cout<<"Exit"<<endl;
				break;
				
			default :
				cout<<"Invalid input"<<endl;	
		}
	}

	return 0;
}

