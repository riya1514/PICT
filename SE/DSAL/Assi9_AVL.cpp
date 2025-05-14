#include<iostream>
using namespace std;
class Node
{
	public:
		Node *left;
		string key;
		string meaning;
		Node *right;
		int height;
		
	public:
		Node()
		{
			left = NULL;
			key = "";
			meaning = "";
			right = NULL;
			height = 0;
		}
		
		Node(string key,string meaning)
		{
			left = NULL;
			this->key = key;
			this->meaning = meaning;
			right = NULL;
			height = 1;
		}
};

class AVL
{
	private:
		Node *root;
		
	public:
		AVL()
		{
			root = NULL;
		}
		
		Node* getroot()
		{
			return root;
		}
		
		void create();
		Node* insert(Node *T,string key,string meaning);
		Node* rotateright(Node* T);
		Node* rotateleft(Node* T);
		Node* rightleft(Node* T);
		Node* leftright(Node* T);
		void inorder(Node* curr);
		int balance_factor(Node* T);
		int height(Node* T);
};

void AVL::create()
{
	int n,value;
	string key,meaning;
	cout<<"\nEnter Number of Nodes = ";
	cin>>n;
	cin.ignore(1);
	if(n <= 0)
	{
		cout<<"\nInvalid";
		return;
	}
	
	for(int i = 0 ; i < n ; i++)
	{
		cout<<"\nEnter "<<i + 1<<" Data:";
		cout<<"\nEnter Key = ";
		getline(cin,key);
		
		cout<<"\nEnter Meaning = ";
		getline(cin,meaning);
		root = insert(getroot(),key,meaning);
	}
}

Node* AVL::rotateright(Node* T)
{
	Node* p = T->left;
	T->left = p->right;
	p->right = T;
	return p;
}

Node* AVL::rotateleft(Node* T)
{
	Node* p = T->right;
	T->right = p->left;
	p->left = T;
	return p;
}


Node* AVL::leftright(Node* T)
{
	T->left = rotateleft(T->left);
	T = rotateright(T);
	return T;
}


Node* AVL::rightleft(Node* T)
{
	T->right = rotateright(T->right);
	T = rotateleft(T);
	return T;
}


int AVL::height(Node* T)
{
	if(T == NULL)
	{
		return 0;
	}
	else
	{
		return (max(height(T->left),height(T->right))+1);
	}
}


int AVL::balance_factor(Node* T)
{
	if(T == NULL)
	{
		return 0;
	}
	int hl,hr;
	hl = height(T->left);
	hr = height(T->right);
	return hl-hr;
}
		
Node* AVL::insert(Node *T,string key,string meaning)
{
	if(T == NULL)
	{
		T = new Node(key,meaning);
		return T;
	}
	if(key < T->key)
	{
		T->left = insert(T->left,key,meaning);
		if(balance_factor(T) >=2)
		{
			if(key < T->left->key)
			{
				T = rotateright(T);
			}
			else
			{
				T = leftright(T);
			}
		}
		return T;
	}
	if(key > T->key)
	{
		T->right = insert(T->right,key,meaning);
		if(balance_factor(T) <= -2)
		{
			if(key > T->right->key)
			{
				T = rotateleft(T);
			}
			else
			{
				T = rightleft(T);
			}
		}
		return T;
	}
	cout<<"Duplicate keys\n";
	return T;	
}

void AVL::inorder(Node* curr)
{	
	if(curr == NULL)
	{
		return;
	}
	inorder(curr->left);
	cout<<"Key = "<<curr->key<<"    "<<"Meaning = "<<curr->meaning<<"Height = "<<height(curr)<<endl;
	inorder(curr->right);
}

int main()
{

	AVL t;
	t.create();
	t.inorder(t.getroot());
	cout<<"\nHeight = "<<t.height(t.getroot());

	return 0;
}

