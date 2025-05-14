/*9.In any language program mostly syntax error occurs due to unbalancing delimiter such as (),{},[]. 
Write C++ program using stack to check whether given expression is well parenthesized or not*/

#include<iostream>
#include<string.h>
using namespace std;
#define size 30

class Stack
{
	private:
		int top;
	    char stack[size];
	    
	public:
		Stack()
		{
			top = -1;
		}
		
		void push(char temp)
		{
			top = top + 1;
			stack[top] = temp;
		}
		
		char top_()
		{
			char temp;
			if(top == -1)
			{
				
			}
			else
			{
				temp = stack[top];
			}
			return temp;
		}
		
		void pop_()
		{
			top = top - 1;
		}
		
		int empty_()
		{
			if(top == -1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
};

int main()
{
	char exp[30];
	char ch;
	int i = 0;
	
	Stack temp;
	
	cout<<"\nEnter the Expression  =  ";
	cin.getline(exp,30);
	
	if( (exp[i] == ')') || (exp[i] == '}') || (exp[i] == ']') )
	{
		cout<<"\nInvalid Expression\n";
		exit(1);
	}
	else
	{
		while(exp[i] != '\0')
		{
			ch = exp[i];
			
			switch(ch)
			{
				case '(' :
							temp.push(ch);
							break;
							
				case '[' :
							temp.push(ch);
							break;
							
				case '{' :
							temp.push(ch);
							break;
							
				case ')' :
							if(temp.top_() == '(' && exp[i] == ')')
							{
								temp.pop_();
							}
							else
							{
								temp.push(ch);
							}
							break;	
							
				case ']' :
							if(temp.top_() == '[' && exp[i] == ']')
							{
								temp.pop_();
							}
							else
							{
								temp.push(ch);
							}
							break;
							
				case '}' :
							if(temp.top_() == '{' && exp[i] == '}')
							{
								temp.pop_();
							}
							else
							{
								temp.push(ch);
							}
							break;				
			}
			
			i++;
		}
	}
	if(temp.empty_())
	{
        cout<<"\nExpression is well parenthesised...\n";
	}
	else
	{
        cout<<"\nExpression is not well parenthesized...\n";
	}

	return 0;
}

