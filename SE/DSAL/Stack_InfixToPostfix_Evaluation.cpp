#include <iostream>
#include<string.h>
using namespace std;
#define size 20

class stackexp;
int pre(char x);
int isOperand(char x);
char * InToPost(char * infix,stackexp & obj);
int Eval(char *postfix,stackexp & obj);

class stackexp
{
	    int top;
	    char stk[size];
	public:
	    stackexp()
	    {
	    	top=-1;
	    }
	    void push(char);
	    char pop();
	    int isfull();
	    int isempty();
	    char top_();
	    
};

void stackexp::push(char x)
{
    top=top+1;
    stk[top]=x;
}

char stackexp::pop()
{
    char s;
    s=stk[top];
    top=top-1;
    return s;
}

int stackexp::isfull()
{
    if(top==size-1)
        return 1;
    else
        return 0;
}

int stackexp::isempty()
{
    if(top==-1)
        return 1;
    else
        return 0;
}

char stackexp::top_()
{
    char s=0;
    if(isempty())
    {
    	
	}
	else
	{
		s=stk[top];
		
	}
    return s;
}

int pre(char x)
{
	if(x=='+' || x=='-')
	 	return 1;
	else if(x=='*' || x=='/')
	 	return 2;
	return 0;
}
 
int isOperand(char x)
{
	if(x=='+' || x=='-' || x=='*' || x=='/' 
	|| x=='(' or x=='{' or x=='['
	|| x==')' or x=='}' or x==']')
		return 0;
	else
		return 1;
 
}

char * InToPost(char * infix,stackexp & obj)
{
	int i=0,j=0;
	char * postfix;
	char c;
	int len = strlen(infix);
	postfix = new char[len+1];
	while(infix[i]!='\0')
	{
		c = infix[i];
		if(isOperand(infix[i]))
			postfix[j++]=infix[i++];
		else
		{
			if(pre(infix[i])>pre(obj.top_()))
				obj.push(infix[i++]);
			else if(c=='(' or c=='{' or c=='[')
			{
                obj.push(c);
                i++;
			}
			else if(c==')')
            {
                while(obj.top_()!='(')
                    postfix[j++] = obj.pop();
                obj.pop();
                i++;
            }
            else if(c=='}')
            {
                while(obj.top_()!='{')
                    postfix[j++] = obj.pop();
                obj.pop();
                i++;
            }
            else if(c==']')
            {
                while(obj.top_()!='[')
                    postfix[j++] = obj.pop();
                obj.pop();
                i++;
            }
			else
			{
				postfix[j++]=obj.pop();
			}
		}
	}
	while(!obj.isempty())
		postfix[j++]=obj.pop();
	postfix[j]='\0';
	return postfix;
}

int Eval(char *postfix,stackexp & obj)
{
	int i=0;
	int x1,x2,r=0 ;
	 
	for(i=0;postfix[i]!='\0';i++)
	{
		if(isOperand(postfix[i]))
		{
			obj.push(postfix[i]-'0');
		}
		else
		{
			x2=obj.pop();
			x1=obj.pop();
			switch(postfix[i])
			{
				case '+':
					r=x1+x2; 
					break;
				case '-':
					r=x1-x2; 
					break;
				case '*':
					r=x1*x2; 
					break;
				case '/':
					r=x1/x2; 
					break;
			}
			obj.push(r);
		}
	}
	return obj.pop();
}

int main()
{
	stackexp obj;
	
    char infix[] = "a+((b*c)-d)/e"; 
	char * postfix = InToPost(infix,obj);
 	cout<<"\nPostfix expression : "<<postfix;
 	
 	char postfix_[] = "234*+82/-";
	cout<<"\nResult is : "<<Eval(postfix_,obj);
 	
    return 0;
}



