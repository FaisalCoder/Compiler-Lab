#include<iostream>
#include<cstring>
#include<fstream>
#include<iomanip>
#include<vector>
#include <algorithm>
#define MAX 30

using namespace std;

//stack class
class stack{

	public:
      	stack()
      	{
			top = -1;
     	}

       	void push(char item)
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

     	char returnTop()
     	{
     		return arr[top];
     	}

     	void print()
     	{
     		if(top == -1){
     			cout<<"stack is empty"<<endl;
     		}
     		else{

     			for(int i = 0;i<=top;i++){
     				cout<<arr[i]<<" ";
     			}
     		}
     	}

     	private:
        char arr[MAX];
    	int top;
};

int main()
{
	ifstream in;
	in.open("q11.txt");           //input file

	int noProductionRules;
	in >> noProductionRules;

	cout << noProductionRules << endl;

	string cfg[noProductionRules];             // cfg stored in string array

	//Enter the production rules"
	for(int i = 0; i < noProductionRules; i++)
	{
		in >> cfg[i];                  //Extracting cfg
	}
	cout << "...........Context Free Grammar ..................\n";

	for(int i = 0; i < noProductionRules; i++)
	{
		cout << cfg[i] << endl;           //Displaying
	}

	vector<char> nonTerminal;

	for(int i = 0; i < noProductionRules; i++)
	{
		bool isPresent = false;
		for(int j = 0; j < nonTerminal.size(); j++)
		{
			if(cfg[i][0] == nonTerminal[j])
			{
				isPresent = true;
				break;
			}
		}

		if(!isPresent)
		nonTerminal.push_back(cfg[i][0]);       //this pushes all terminals from the cfg
	}

	vector<char>prodTerInRule[noProductionRules];

	for(int i = 0;i<noProductionRules;i++)
	{
		for(int j = 3;j <(cfg[i]).length(); j++)      //starting from 3 because rhs starts from 3
		{
			bool isnonTerminal = false;
			for(int k = 0; k < nonTerminal.size(); k++)
			{
				if(cfg[i][j] == nonTerminal[k])
				{
					isnonTerminal = true;
					break;
				}
			}

			if(!isnonTerminal)
			(prodTerInRule[i]).push_back(cfg[i][j]);       //extracts all terminals from cfg order wise
		}
	}

    cout << "Terminals: ";
	for(int i = 0; i < noProductionRules; i++)             //displaying all terminals from cfg orderwise
	{
		for(int j = 0; j<(prodTerInRule[i]).size();j++ )
		{
			cout << prodTerInRule[i][j];
		}
	}
	cout << endl;

	int no_of_terminals;          //number of terminals

	in >> no_of_terminals;
	cout << no_of_terminals << endl;

	char opPreMatrix[no_of_terminals+1][no_of_terminals+1] ;        //operator precedence matrix

	for(int i = 0; i <= no_of_terminals; i++)
	{
		for(int j = 0; j <= no_of_terminals; j++)
		{
			in >> opPreMatrix[i][j];
		}
	}

    cout << "...........Operator Precedence Matrix ..................\n";
	for(int i = 0; i <= no_of_terminals; i++)
	{
		for(int j = 0; j <= no_of_terminals; j++)
		{
			cout << opPreMatrix[i][j] << " ";
		}

		cout << endl;
	}

	string input_string;
	cout << "Enter the input string" << endl;
	cin >> input_string;

	stack parserStack;

	parserStack.push('$');
	parserStack.print();

	string inputString = input_string + '$';

	int index = 0;
	char ip = inputString[index];

	cout << "\t\t" << "<";
	cout << "\t\t" << inputString;
	cout << "\t\t" << "Shift" << endl;
	//cout << "------------------------------------------------------------------------" << endl;

	while(true)
	{

		char sTop = parserStack.returnTop();

		if(sTop == '$' && ip == '$')
		{
			cout << "\n.....Input string is accepted..." << endl;
			break;
		}

		else
		{
			int i,j, s,a;

            //getting position of stack top and input symbol
			for(i = 1; i <= no_of_terminals;i++)
			{
				if(sTop == opPreMatrix[i][0])
				{
					s = i;                        //s row index is position of terminal on top
					break;
				}
			}

			bool isValid = true;

			if(i > no_of_terminals+1)
			isValid = false;

			for(j = 1; j <= no_of_terminals; j++)
			{
				if( ip == opPreMatrix[0][j])
				{
					a = j;                      // a is column index
					break;
				}
			}

			if(j > no_of_terminals+1)           //if input is some other symbol
			isValid = false;

			if(!isValid)
			{
				cout << "Input string has invalid character.Error" << endl;
				break;
			}
			//rule starts

			if(opPreMatrix[s][a] == '<' || opPreMatrix[s][a] == '=')
			{
				parserStack.push(ip);
				parserStack.print();
				index++;
				ip = inputString[index];

				int k,l;

				for(k = 1; k <= no_of_terminals;k++)
				{
					if(parserStack.returnTop() == opPreMatrix[k][0]){
						break;
					}              //row of stack top
				}

				for(l = 1; l <= no_of_terminals; l++)
				{
					if(ip == opPreMatrix[0][l]){
						break;               //column of input symbol
					}
				}

				cout << "\t\t" << opPreMatrix[k][l];          //displaying the relation between the two
				cout << "\t\t";

				for(int i = index; i < inputString.length(); i++)
				{
					cout << inputString[i];
				}

				if( opPreMatrix[k][l] == '>')
				cout << "\t\t" << "Reduce" << endl;

				else
				cout << "\t\t" << "Shift" << endl;
				//cout<<"------------------------------------------------------------------------"<<endl;
			}

			else if(opPreMatrix[s][a] == '>')
			{
				int k,l;
				vector <char> sym;            //reverse of sym_
				vector <char> sym_;               // correct order of popped terminals to find production used

				do
				{
					char stackTop = parserStack.returnTop();
					sym.push_back(stackTop);
					parserStack.pop();

					for(int i = 1; i <= no_of_terminals;i++)
					{
						if(parserStack.returnTop() == opPreMatrix[i][0])
						{
                            k = i;                  //row index of stack top
                            break;
						}
					}
					for(int i = 1; i <= no_of_terminals;i++)
					{
						if(stackTop == opPreMatrix[0][i])
						{
                            l = i;             //column index of most recently popped
                            break;
						}
					}
				}
				while(opPreMatrix[k][l] != '<');

				for(int i = sym.size()-1;i >=0 ; i--)
				{
					sym_.push_back(sym[i]);               //constructing sym_
				}

				int a;
				for( a = 0; a<noProductionRules; a++)
				{
					bool isEqual = false;

					if(sym_.size() == (prodTerInRule[a]).size())     //matching the production for reduced reduction
					{
						isEqual = equal(sym_.begin(),sym_.end(),(prodTerInRule[a]).begin());
					}

					if(isEqual) break;
				}

				if(a < noProductionRules)
				{
					cout << "\n	....Reduced by the production: " << cfg[a] << "....\n" << endl;
					//cout << "------------------------------------------------------------------------" << endl;
				}

				parserStack.print();
				int m,n;
				for(m = 1; m <= no_of_terminals; m++)
				{
					if(parserStack.returnTop() == opPreMatrix[m][0])
					{
						break;
					}
				}

				for(n = 1; n <= no_of_terminals; n++)
				{
					if(ip == opPreMatrix[0][n])
					{
						break;               //finding index for giving the relation
					}
				}

				if(opPreMatrix[m][n] != 'b')
				cout << "\t\t" << opPreMatrix[m][n];

				else
				cout <<"\t\t";

				cout << "\t\t";

				for(int i = index; i < inputString.length(); i++)
				{
					cout << inputString[i];
				}

				if(opPreMatrix[m][n] == '>')
				{
					cout << "\t\t" << "Reduce" << endl;

				}

				else if(opPreMatrix[m][n] == 'b')
				cout << endl;

				else
				cout << "\t\t" << "Shift" << endl;
				//cout << "------------------------------------------------------------------------" << endl;
			}

			else
			cout << "Error" << endl;
		}
	}
	return 0;
}
