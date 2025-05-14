#include<iostream>
#include<iomanip>
#define INF 99999
using namespace std;

class City
{
	public :
		string name;
		int ind;
		
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

class Graph
{
	private :
		City *arr;
		
	public :
		int n;
		
		Graph()
		{
			int i;
			string edge;
			cout<<"Enter number of city names = ";
			cin>>n;
			arr = new City[n];
			cin.ignore(1);
			cout<<"\nEnter city names"<<endl;
			for(i=0 ; i<=n-1 ; i++)
			{
				cout<<i+1<<" : ";
				getline(cin,edge);
				arr[i].name = edge;
				arr[i].ind = i;
			}
		}
		
		void insert(int graph[10][10])
		{
			int e,i,s,d,dis;
			string source,desti;
			
			cout<<"\nEnter no of edges = ";
			cin>>e;
			
			cout<<"\nEnter edges"<<endl;
			
			for(i=0 ; i<=e-1 ; i++)
			{
				cin.ignore(1);
				cout<<"\nEnter source = ";
				getline(cin,source);
				cout<<"Enter destination = ";
				getline(cin,desti);
				cout<<"Enter distance = ";
				cin>>dis;
				s = getindex(source);
				d = getindex(desti);
				graph[s][d] = dis;
				graph[d][s] = dis;	
			}
		}
		
		void adj_matrix(int graph[10][10])
		{
			int i,j;
			for(i=0 ; i<=n-1 ; i++)
			{
				for(j=0 ; j<=n-1 ; j++)
				{
					cout<<setw(4)<<left<<graph[i][j];
				}
				cout<<endl;
			}
		}
		
		void adj_list(int graph[10][10])
		{
			int i,j;
			for(i=0 ; i<=n-1 ; i++)
			{
				cout<<arr[i].name<<" : ";
				for(j=0 ; j<=n-1 ; j++)
				{
					if(graph[i][j]!=0)
					{
						cout<<arr[j].name<<"  ";
					}
				}
				cout<<endl;
			}
		}
		
		int getindex(string city)
		{
			int i;
			for(i=0 ; i<=n-1 ; i++)
			{
				if(arr[i].name == city)
				{
					return i;
				}
			}
		}
		
		void prims(int cost[10][10])
		{
			int *visited,*distance,*from;
			string source,desti;
			int i,j,s,d,ne,v,u,mindist,sum=0;
			
			visited = new int[n];
			distance = new int[n];
			from = new int[n];
			
			cout<<"\nEnter source = ";
			cin.ignore(1);
			getline(cin,source);
			s = getindex(source);
			
			for(i=0 ; i<=n-1 ; i++)
			{
				visited[i] = 0;
				distance[i] = cost[s][i];
				from[i] = s;
			}
			
			visited[s] = 1;
			distance[s] = 0;
			
			cout<<"\nEdges of minimum spanning tree are\n";
			ne = n-1;
			while(ne>0)
			{
				mindist = INF;
				for(i=0 ; i<=n-1 ; i++)
				{
					if(visited[i]==0)
					{
						if(mindist>distance[i])
						{
							mindist = distance[i];
							v = i;
						}
					}
				}
				
				desti = arr[v].name;
				visited[v] = 1;
				u = from[v];
				source = arr[u].name;
				
				cout<<endl<<source<<" -> "<<desti;
				sum = sum + cost[u][v];
				
				for(i=0 ; i<=n-1 ; i++)
				{
					if(visited[i]==0)
					{
						if(distance[i]>cost[v][i])
						{
							distance[i] = cost[v][i];
							from[i] = v;
						}
					}
				}
				ne--;
			}
			
			cout<<"\n\nCost of minimum spanning tree = "<<sum;
		}
};		

int main()
{
	int i,j;
	
	int graph[10][10],cost[10][10];
	Graph gph;
	
	for(i=0 ; i<=(gph.n)-1 ; i++)
	{
		for(j=0 ; j<=(gph.n)-1 ; j++)
		{
			graph[i][j] = 0;
		}
	}
	
	gph.insert(graph);
	
	for(i=0 ; i<=(gph.n)-1 ; i++)
	{
		for(j=0 ; j<=(gph.n)-1 ; j++)
		{
			if(graph[i][j]==0)
			{
				cost[i][j] = INF;
			}
			else
			{
				cost[i][j] = graph[i][j];
			}
		}
	}
	
	cout<<"\nAdjacency matrix"<<endl;
	gph.adj_matrix(graph);
	
	cout<<"\nAdjacency list"<<endl;
	gph.adj_list(graph);
	
	gph.prims(cost);	
	
	return 0;
}



/*#include<iostream>
#define INF 99999
using namespace std;

int main()
{
	int n,ne,i,j,k,source,u,v,sum=0,mindist;
	int *visited,*distance,*from;
	int graph[10][10],cost[10][10];
	
	cout<<"Enter no of nodes = ";
	cin>>n;
	
	cout<<"\nEnter adjacency matrix\n";
	for(i=0 ; i<=n-1 ; i++)
	{
		for(j=0 ; j<=n-1 ; j++)
		{
			cout<<"Distance of "<<i<<"->"<<j<<" = ";
			cin>>graph[i][j];
		}
	}
	
	for(i=0 ; i<=n-1 ; i++)
	{
		for(j=0 ; j<=n-1 ; j++)
		{
			if(graph[i][j]==0)
			{
				cost[i][j] = INF;
			}
			else
			{
				cost[i][j] = graph[i][j];
			}
		}
	}
	
	visited = new int[n];
	distance = new int[n];
	from = new int[n];
	
	cout<<"\nEnter source = ";
	cin>>source;
	
	for(i=0 ; i<=n-1 ; i++)
	{
		visited[i] = 0;
		distance[i] = cost[source][i];
		from[i] = source;
	}
	
	visited[source] = 1;
	distance[source] = 0;
	
	cout<<"\nEdges o minimum spanning tree are\n";
	ne = n-1;
	while(ne>0)
	{
		mindist = INF;
		for(i=0 ; i<=n-1 ; i++)
		{
			if(visited[i]==0)
			{
				if(mindist>distance[i])
				{
					mindist = distance[i];
					v = i;
				}
			}
		}
		
		visited[v] = 1;
		u = from[v];
		
		cout<<endl<<u<<" -> "<<v;
		sum = sum + cost[u][v];
		
		for(i=0 ; i<=n-1 ; i++)
		{
			if(visited[i]==0)
			{
				if(distance[i]>cost[v][i])
				{
					distance[i] = cost[v][i];
					from[i] = v;
				}
			}
		}
		ne--;
	}
	
	cout<<"\n\nCost of minimum spanning tree = "<<sum;
	
	return 0;
}
*/



