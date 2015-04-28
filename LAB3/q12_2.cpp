#include<iostream>
#include<cstring>
#include<fstream>
#include<iomanip>
#define MAX 20
using namespace std;

class stack
{
    private:
        string arr[MAX];
    	int top;
	public:
      	stack()
          {
			top = -1;
          }

        void push(string item)
        {
            if(top == MAX-1){
                cout<<"Stack is full"<<endl;
            }
			top++;
            arr[top] = item;
      	}

 		void pop()
        {
            if(top == -1){
                cout<<"Stack is empty"<<endl;
            }
            top--;
     	}

     	string returnTop()
        {
     		return arr[top];
     	}

     	void print()
         {
     		if(top == -1)
             {
     			cout<<"stack is empty"<<endl;
     		 }

     		else
             {

     			for(int i = 0;i<=top;i++)
                 {
     				cout<<arr[i]<<" ";
     			 }
     		}
     	}
};

string fetchInt(string s)
{
	int i = 1;
	string a ;
	while(i < s.length())
    {
		char b = s[i];
		a = a + b;
		i++;
	}

	return a;
}

string intToString(int a)
{
	string b ;
	int n;
	char c;
	if(a == 0) b = "0";

    else
    {
		while(a != 0)
        {
			n = a%10;
			a = a/10;
			c = '0' + n;
			b =  c + b;
		}
	}
	return b;
}

int stringToInt(string a)
{
	int i = 0;
	int b = 0;
	while(a[i] != '\0')
    {
		int c = a[i]-'0';
		b = b*10 + c;
		i++;
	}
	return b;
}

int main(){

	ifstream inputFile;
	inputFile.open("q12.txt");
	//Enter the no of production rules in the grammar

    int noProdRules;
	inputFile>>noProdRules;
	string prodRule[noProdRules];
	//Enter the production rules"

	for(int i = 0; i < noProdRules; i++)
	{
		inputFile >> prodRule[i];
	}

	int noStates,noGramSym;
	//Enter the no of states"
	inputFile >> noStates;
	//Enter the no of grammar symbols (assume $ is a grammar symbol)
	inputFile >> noGramSym;
	string LR_table[noStates+1][noGramSym+1] ;

	for(int i = 0; i < noStates;i++)
	{
		LR_table[i+1][0] = intToString(i);
	}

	//Enter the grammar symbols of the table
	for(int i = 0; i < noGramSym; i++)
	{
		inputFile >> LR_table[0][i+1];
	}

	//Enter  the table (for blank entry, enter 'b')
	for(int i = 1; i < noStates; i++)
	{
		for(int j = 1; j <= noGramSym; j++)
		{
			inputFile >> LR_table[i][j];
		}
	}

	cout << "Enter the input string" << endl;
	string inputString;
	cin >> inputString;

	stack stk;
	stk.push(LR_table[1][0]);
	stk.print();

	string buffer = inputString + '$';
	int index = 0;
	char ip = buffer[index];

	cout << setw(20) << buffer;

	while(true)
	{
		int s,a;
		string sTop = stk.returnTop();
		for(int i = 1; i < noStates;i++)
		{
			if(sTop == LR_table[i][0])
			{
				s = i;
				break;
			}
		}

		bool isValid = true;

		for(int i = 1; i <= noGramSym;i++)
		{

			if(ip == LR_table[0][i][0])
			{
				a = i;
				break;
			}

			if(LR_table[0][i] == "$")
			{
				isValid = false;
				break;
			}
		}

		if(!isValid)
		{
			cout << "\ninput string has invalid character" << endl;
			break;
		}

		string action = LR_table[s][a];

		if(action[0] == 's')
		cout << setw(20) << action << endl;

		else if(action[0] == 'r')
		{
			int rule = stringToInt(fetchInt(action));
			cout << setw(20) << action << "  ( " << prodRule[rule-1] << " )  " << endl;
		}

		if(action[0] == 's')
		{
			char ip_[2] ;
			ip_[0] = ip;
			ip_[1] = '\0';

			stk.push(ip_);
			stk.push(fetchInt(action));
			stk.print();

			index++;
			ip = buffer[index];

			cout << setw(20);

			for(int i = index; i < buffer.length(); i++)
			{
				cout << buffer[i];
			}
		}

		else if(action[0] == 'r')
		{
			int rule = stringToInt(fetchInt(action));
			int lenOfRuleOfRHS = ((prodRule[rule-1]).length()) - 3;

			for(int i = 0; i < lenOfRuleOfRHS; i++)
			{
				stk.pop();
				stk.pop();
			}

			sTop = stk.returnTop();
			int s0,A;

			for(int i = 1; i < noStates;i++)
			{
				if(sTop == LR_table[i][0])
				{
					s0 = i;
					break;
				}
			}

			char nonTer = prodRule[rule-1][0];

			for(int i = 1; i <= noGramSym;i++)
			{
				if(nonTer == LR_table[0][i][0])
				{
					A = i;
					break;
				}
			}

			char nonTer_[2];
			nonTer_[0] = nonTer;
			nonTer_[1] = '\0';

			stk.push(nonTer_);
			stk.push(LR_table[s0][A]);
			stk.print();

			cout<<setw(20);

			for(int i = index; i < buffer.length(); i++)
			{
				cout << buffer[i];
			}

		}

		else if(action == "acc")
		{
			cout << "input string is accepted" << endl;
			break;
		}

		else
		{
			cout << "Error in parsing" << endl;
			break;
		}
	}
	return 0;
}
