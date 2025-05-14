#include<iostream>
using namespace std;

void downadjust(int *heap, int i)
{
	int n,temp,j;
	n = heap[0];
	
	while(2*i <= n)
	{
		j = 2*i;
		if(j+1 <= n)
		{
			if(heap[j] < heap[j+1])
			{
				j = j+1;
			}
		}
		if(heap[i] < heap[j])
		{
			temp = heap[i];
			heap[i] = heap[j];
			heap[j] = temp;
			i = j;
		}
		else
		{
			break;
		}
	}
} 

int main()
{
	int n,i,last,temp,total,ind,*heap;
	
	cout<<"Enter number of elements = ";
	cin>>n;
	
	heap = new int[n+1];
	
	cout<<"\nEnter elements \n";
	for(i=1 ; i<=n ; i++)
	{
		cout<<"Data = ";
		cin>>heap[i];
	}
	
	cout<<"\nGiven array = ";
	for(i=1 ; i<=n ; i++)
	{
		cout<<heap[i]<<" ";
	}
	
	heap[0] = n;
	total = heap[0];
	
	for(ind=total/2 ; ind>0 ; ind--)
	{
		downadjust(heap,ind);
	}
	
	while(heap[0]>1)
	{
		last = heap[0];
		temp = heap[1];
		heap[1] = heap[last];
		heap[last] = temp;
		heap[0]--;
		downadjust(heap,1);
	}
	
	cout<<"\n\nSorted array = ";
	for(i=1 ; i<=n ; i++)
	{
		cout<<heap[i]<<" ";
	}
	
	return 0;
}

