/*
Title : Binary Tree
Problem Statement : Beginning with an empty binary tree, Construct binary tree byinsertingthe values in the order given. 
After constructing a binary tree performfollowing operations on it-
1.Perform in order / pre order and post order traversal
2.Change a tree so that the roles of the left and right pointers are swapped at every node
3.Find the height of tree
4.Copy this tree to another [ operator =]
5.Count number of leaves, number of internal nodes.
6.Erase all nodes in a binary tree.
(implement both recursive and non-recursive methods)*/

#include<iostream>
#define size 20
using namespace std;

class Node
{
	public :
		Node *left;
		int data;
		Node *right;
		
		Node()
		{
			data = 0;
			left = right = NULL;
		}
		
		Node(int x)
		{
			data = x;
			left = right = NULL;
		}
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

class Queue
{
	public :
		Node* que[size];
		int front,rear;
		
		Queue()
		{
			front = rear = -1;
		}
		
		int isempty();
		void enqueue(Node* temp);
		Node* deque();
};

class Binary_tree
{
	private :
		Node *root;
		
	public :
		Binary_tree()
		{
			root = NULL;
		}
		
		Node *getroot()
		{
			return root;
		}
		
		void setroot(Node *temp)
		{
			root = temp;
		}
		
		void create();
		void inorder(Node *temp);
		void preorder(Node *temp);
		void postorder(Node *temp);
		void non_rec_inorder(Node *temp);
		void non_rec_preorder(Node *temp);
		void non_rec_postorder(Node *temp);
		void bfs();
		void mirror(Node *temp);
		int height(Node *temp);
		void int_ext_nodes(Node *temp, int &int_count, int &ext_count);
		void delete_tree(Node *temp);
		Node* copy_tree(Node* temp);
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

int Queue::isempty()
{
	if(front==-1 || front==rear+1)
	{
		return 1;
	}
	return 0;
}

void Queue::enqueue(Node* temp)
{
	if(front==-1)
	{
		front = 0;
	}
	rear = (rear+1)%size;
	que[rear] = temp;
}

Node* Queue::deque()
{
	Node* temp = que[front];
	front = (front+1)%size;
	return temp;
}

void Binary_tree::create()
{
	int x,n,i;
	
	cout<<"Enter no of nodes = ";
	cin>>n;
	
	cout<<"\nEnter data of root node = ";
	cin>>x;
	Node *temp,*p;
	root = new Node(x);
	
	for(i=1 ; i<=n-1 ; i++)
	{
		cout<<"\nEnter data of next node = ";
		cin>>x;
		p = new Node(x);
		temp = root;
		do
		{
			char ch;
			cout<<"Where you want to insert the new node (L/R) of "<<temp->data<<" = ";
			cin>>ch;
			
			if(ch=='L' || ch=='l')
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
			else if(ch=='R' || ch=='r')
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
			else
			{
				cout<<"Wrong choice";
			}
		}while(temp!=p);
	}
}

void Binary_tree::inorder(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	inorder(temp->left);
	cout<<temp->data<<" ";
	inorder(temp->right);
}

void Binary_tree::preorder(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	cout<<temp->data<<" ";
	preorder(temp->left);
	preorder(temp->right);
}

void Binary_tree::postorder(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	postorder(temp->left);
	postorder(temp->right);
	cout<<temp->data<<" ";
}

void Binary_tree::non_rec_inorder(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	Stack stk;
	Node *curr = temp;
	
	while(curr!=NULL || stk.isempty()!=1)
	{
		while(curr!=NULL)
		{
			stk.push(curr);
			curr = curr->left;
		}
		
		curr = stk.pop();
		cout<<curr->data<<" ";
		curr = curr->right;
	}
}

void Binary_tree::non_rec_preorder(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	Stack stk;
	Node *curr = temp;
	
	while(curr!=NULL || stk.isempty()!=1)
	{
		while(curr!=NULL)
		{
			cout<<curr->data<<" ";
			stk.push(curr);
			curr = curr->left;
		}
		
		curr = stk.pop();
		curr = curr->right;
	}
}

void Binary_tree::non_rec_postorder(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	
	Stack stk1,stk2;
	Node *curr;
	
	stk1.push(temp);
	
	while(stk1.isempty()!=1)
	{
		curr = stk1.pop();
		stk2.push(curr);
		if(curr->left)
		{
			stk1.push(curr->left);
		}
		if(curr->right)
		{
			stk1.push(curr->right);
		}
	}
	
	while(stk2.isempty()!=1)
	{
		curr = stk2.pop();
		cout<<curr->data<<" ";
	}
}

void Binary_tree::bfs()
{
	Node* temp = root;
	Queue que;
	
	que.enqueue(temp);
	
	while(que.isempty()!=1)
	{
		temp = que.deque();
		cout<<temp->data<<" ";
		if(temp->left != NULL)
		{
			que.enqueue(temp->left);
		}
		if(temp->right != NULL)
		{
			que.enqueue(temp->right);
		}
	}
}

int Binary_tree::height(Node *temp)
{
	int l_height=0,r_height=0;
	
	if(temp==NULL)
	{
		return 0;
	}
	else
	{
		l_height = height(temp->left);
		r_height = height(temp->right);
		
		if(l_height > r_height)
		{
			return l_height+1;
		}
		else
		{
			return r_height+1;
		}
	}
}

void Binary_tree::mirror(Node *temp)
{
	Node *swap;
	
	if(temp==NULL)
	{
		return;
	}
	else
	{
		mirror(temp->left);
		mirror(temp->right);
		
		swap = temp->left;
		temp->left = temp->right;
		temp->right = swap;
	}
}

void Binary_tree::int_ext_nodes(Node *temp, int &int_count, int &ext_count)
{	
	if(temp==NULL)
	{
		return;	
	}
	else
	{
		int_ext_nodes(temp->left,int_count,ext_count);
		int_ext_nodes(temp->right,int_count,ext_count);
		
		if(temp->left || temp->right)
		{
			int_count++;
		}
		else
		{
			ext_count++;
		}
	}
}

Node* Binary_tree::copy_tree(Node* temp)
{
    if(temp==NULL)
	{
		return NULL;
	} 
    Node* newnode= new Node(temp->data);
    newnode->left=copy_tree(temp->left);
    newnode->right=copy_tree(temp->right);
    return newnode;
}

void Binary_tree::delete_tree(Node *temp)
{
	if(temp==NULL)
	{
		return;
	}
	else
	{
		delete_tree(temp->left);
		delete_tree(temp->right);
		cout<<temp->data<<" ";
		delete temp;
	}
}

int main()
{
	Binary_tree tree,copied;
	Node *temp;
	int int_nodes=0,ext_nodes=0,choice=0;

	tree.create();
	
	cout<<"\nInorder = ";
	tree.inorder(tree.getroot());
	cout<<"\nInorder (non recursive) = ";
	tree.non_rec_inorder(tree.getroot());
	cout<<endl;
	
	cout<<"\nPreorder = ";
	tree.preorder(tree.getroot());
	cout<<"\nPreorder (non recursive) = ";
	tree.non_rec_preorder(tree.getroot());
	cout<<endl;
	
	cout<<"\nPostorder = ";
	tree.postorder(tree.getroot());
	cout<<"\nPostorder (non recursive) = ";
	tree.non_rec_postorder(tree.getroot());
	cout<<endl;
	
	cout<<"\nLevel wise order = ";
	tree.bfs();
	cout<<endl;
	
	cout<<"\nHeight = "<<tree.height(tree.getroot());
	cout<<endl;
	
	tree.int_ext_nodes(tree.getroot(),int_nodes,ext_nodes);
	cout<<"\nInternal nodes = "<<int_nodes;
	cout<<"\nLeaf nodes = "<<ext_nodes;
	cout<<endl;
	
	cout<<"\nInorder of original tree = ";
	tree.inorder(tree.getroot());
	tree.mirror(tree.getroot());
	cout<<"\nInorder of mirror tree = ";
	tree.inorder(tree.getroot());
	cout<<endl;
	
	cout<<"\nAddress of original tree = ";
	cout<<tree.getroot();
	cout<<"\nOriginal tree inorder = ";
	tree.inorder(tree.getroot());
	cout<<endl;
	temp = tree.copy_tree(tree.getroot());
	copied.setroot(temp);
	cout<<"\nAddress of copied tree = ";
	cout<<copied.getroot();
	cout<<"\nCopied tree inorder = ";
	copied.inorder(tree.getroot());
	cout<<endl;
	
	cout<<"\nDeleting nodes = ";
	tree.delete_tree(tree.getroot());

	return 0;
}

