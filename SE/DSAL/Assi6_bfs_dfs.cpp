#include<iostream>
#include<queue>
#include<stack>
#define size 10
using namespace std;

class City
{
	public :
		int ind;
		string name;
		
		City()
		{
			name = "";
			ind = -1;
		}
		
		City(string name, int ind)
		{
			this->name = name;
			this->ind = ind;
		}
};

class Node
{
	public:
		City city;
		Node *next;
		
		Node()
		{
			city = City();
			next = NULL;
		}
		
		Node(string name, int ind)
		{
			city = City(name,ind);
			next = NULL;
		}
};

class Stack
{
	public :
		int stk[size];
		int top;
		
		Stack()
		{
			top = -1;
		}
		
		int isempty();
		void push(int temp);
		int pop();
};

class Queue
{
	public :
		int que[size];
		int front,rear;
		
		Queue()
		{
			front = rear = -1;
		}
		
		int isempty();
		void enqueue(int temp);
		int deque();
};

int Stack::isempty()
{
	if(top==-1)
	{
		return 1;
	}
	return 0;
}

void Stack::push(int temp)
{
	top++;
	stk[top] = temp;
}

int Stack::pop()
{
	int curr = stk[top];
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

void Queue::enqueue(int temp)
{
	if(front==-1)
	{
		front = 0;
	}
	rear = (rear+1)%size;
	que[rear] = temp;
}

int Queue::deque()
{
	int temp = que[front];
	front = (front+1)%size;
	return temp;
}

class graph
{
	private :
		City *list;
		Node **arr;
		int *visited;
		int n;
	
	public:
		graph()
		{
			string edge;
			cout<<"Enter the number of vertices = ";
			cin>>n;
			
			list = new City[n];
			arr = new Node*[n];
			
			cin.ignore(1);
			cout<<"\nEnter city names"<<endl;
			for(int i=0 ; i<=n-1 ; i++)
			{
				cout<<i+1<<" : ";
				getline(cin,edge);
				list[i].name = edge;
				list[i].ind = i;
			}
			
			visited = new int[n];
			
			for(int i=0; i<n; i++)
			{
				arr[i] = NULL;
				visited[i] = 0;
			}
		}
		
		int getindex(string city)
		{
			int i;
			for(i=0 ; i<=n-1 ; i++)
			{
				if(list[i].name == city)
				{
					return i;
				}
			}
		}
		
		void create()
		{
			int x,s,d;
			string source,desti;
			
			cout<<"Enter the no of edges = ";
			cin>>x;
			cin.ignore(1);
			
			for(int i=0; i<x; i++)
			{
				cout<<"Enter source = ";
				getline(cin,source);
				s = getindex(source);
				cout<<"Enter destination = ";
				getline(cin,desti);
				d = getindex(desti);
				
				if(arr[s] == NULL)
				{
					arr[s] = new Node(desti,d);
				}
				else
				{
					Node *p = arr[s];
					
					while(p->next != NULL)
					{
						p = p->next;
					}
					p->next = new Node(desti,d);
				}
				if(arr[d] == NULL)
				{
					arr[d] = new Node(source,s);
				}
				else
				{
					Node *p = arr[d];
					
					while(p->next != NULL)
					{
						p = p->next;
					}
					p->next = new Node(source,s);
				}
			}
		}
		
		void display()
		{
			for(int i=0; i<n; i++)
			{
				cout<<list[i].name<<" -> ";
				Node *p = arr[i];
				
				while(p->next != NULL)
				{
					cout<<(p->city).name<<", ";
					p = p->next;
				}
				cout<<(p->city).name;
				cout<<endl;
			}
		}
		
		void bfs(string source)
		{	
			int s = getindex(source);
			Queue que;
			
			que.enqueue(s);
			visited[s] = 1;
			
			while(!que.isempty())
			{
				int a;
				a = que.deque();
				cout<<list[a].name<<" ";
				
				Node *p = arr[a];
				
				while(p != NULL)
				{
					if(visited[(p->city).ind] == 0)
					{
						que.enqueue((p->city).ind);
						visited[(p->city).ind] = 1;
					}
					p = p->next;
				}
			}
		}
		
		void dfs(string source)
		{
			Stack stk;
			int s = getindex(source);
			
			for(int i=0 ; i<=n-1 ; i++)
			{
				visited[i] = 0;
			}
			
			stk.push(s);
			visited[s] = 1;
			
			while(!stk.isempty())
			{
				int a;
				a = stk.pop();
				cout<<list[a].name<<" ";
				
				Node *p = arr[a];
				
				while(p != NULL)
				{
					if(visited[(p->city).ind] == 0)
					{
						stk.push((p->city).ind);
						visited[(p->city).ind] = 1;
					}
					p = p->next;
				}
			}
		}
};

int main()
{
	graph g;
	string source;
	
	g.create();
	cout<<endl;
	g.display();
	cout<<endl;

	cout<<"Enter Source for BFS : ";
	getline(cin,source);
	cout<<"\nDFS traversal is : ";
	g.bfs(source);
	cout<<"\nDFS traversal is : ";
	g.dfs(source);
	cout<<endl;
	
	return 0;
}





/*#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class Node
{
	public:
		int data;
		Node *next;
		
		Node(int a)
		{
			data = a;
			next = NULL;
		}
};

class graph
{
	Node **arr;
	int *visited;
	int n;
	public:
		graph()
		{
			cout<<"Enter the no of vertices : ";
			cin>>n;
			
			visited = new int[n];
			arr = new Node*[n];
			for(int i=0; i<n; i++)
			{
				arr[i] = NULL;
				visited[i] = 0;
			}
		}
		
		void create()
		{
			int x,s,d;
			cout<<"Enter the no of edges : ";
			cin>>x;
			
			for(int i=0; i<x; i++)
			{
				cout<<"Enter source : ";
				cin>>s;
				cout<<"Enter destination : ";
				cin>>d;
				
				if(arr[s] == NULL)
				{
					arr[s] = new Node(d);
				}
				else
				{
					Node *p = arr[s];
					
					while(p->next != NULL)
					{
						p = p->next;
					}
					p->next = new Node(d);
				}
				if(arr[d] == NULL)
				{
					arr[d] = new Node(s);
				}
				else
				{
					Node *p = arr[d];
					
					while(p->next != NULL)
					{
						p = p->next;
					}
					p->next = new Node(s);
				}
			}
		}
		
		void display()
		{
			for(int i=0; i<n; i++)
			{
				cout<<i<<" -> ";
				Node *p = arr[i];
				
				while(p != NULL)
				{
					cout<<p->data<<", ";
					p = p->next;
				}
				cout<<endl;
			}
		}
		
		void bfs(int s)
		{
			queue <int> q;
			
			q.push(s);
			visited[s] = 1;
			
			while(!q.empty())
			{
				int a;
				a = q.front();
				cout<<a<<" ";
				q.pop();
				
				Node *p = arr[a];
				
				while(p != NULL)
				{
					if(visited[p->data] == 0)
					{
						q.push(p->data);
						visited[p->data] = 1;
					}
					p = p->next;
				}
			}
		}
		
		void dfs(int s)
		{
			stack <int> stk;
			
			stk.push(s);
			visited[s] = 1;
			
			while(!stk.empty())
			{
				int a;
				a = stk.top();
				cout<<a<<" ";
				stk.pop();
				
				Node *p = arr[a];
				
				while(p != NULL)
				{
					if(visited[p->data] == 0)
					{
						stk.push(p->data);
						visited[p->data] = 1;
					}
					p = p->next;
				}
			}
		}
};
int main()
{
	graph g;
	
	g.create();
	cout<<endl;
	g.display();
	cout<<endl;
	int p;
	cout<<"Enter Source for BFS : ";
	cin>>p;
	cout<<"BFS traversal is : ";
	g.dfs(p);
	cout<<endl;
	
	return 0;
}*/

