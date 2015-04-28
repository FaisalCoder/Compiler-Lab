#include<iostream>
#include<new>
#include<string>
#include<map>
using namespace std;

struct input_state{
   int input;
   char new_state;
};

int main()
{
   string input_string;
   multimap<char,input_state> sparse_state_table;    //sparse matrix

   int input_n,state_n;
   cout << "Enter number of inputs" << endl;    //0,1,2
   cin >> input_n;

   cout << "Enter number of states" << endl;   //a,b,c..
   cin >> state_n;

   char curr_state,new_state;
   int * input_temp = new int[input_n];  //temporary array delete after taking input
   input_state temp;                    // variable to store in map

   for( int i=0 ; i < input_n ; i++)
   {
       cout << "ENTER INPUT VALUE" << endl;
       cin >> input_temp[i];
   }

   for( int i=0; i< state_n; i++)
   {
       cout << "ENTER CURRENT STATE " << endl;
       cin >> curr_state;

       for( int j=0; j< input_n; j++)
       {
           cout << "ENTER NEW STATE FOR INPUT " << input_temp[j] << " (for blank state press '-') "  <<  endl;
           cin >> new_state;

           temp.input = input_temp[j];
           temp.new_state = new_state;

           if( new_state != '-')            //accepted form, store in sparse matrix
           {
               sparse_state_table.insert(pair<char,input_state>(curr_state,temp));
           }
       }

   }


   char initial;
   //Enter initial state
   cout << "ENTER INITIAL STATE" << endl;
   cin >> initial;

   int final_state_n;
   //final states array
   cout << "ENTER NO OF FINAL STATES" << endl;
   cin >> final_state_n;

   char * final = new char[final_state_n];

   for( int i=0; i<final_state_n; i++)
   {
      cout << "ENTER FINAL STATE" << endl;
      cin >> final[i];
   }

   cout << "ENTER INPUT SEQUENCE" << endl;
   cin >> input_string;

   int m=0,curr_input;
   curr_state = initial;
   char next_state;


    multimap<char,input_state>::iterator it = sparse_state_table.begin();    //iterartor

   //logic
   while( m < input_string.length() )
   {
       bool found = false;
       curr_input = (input_string[m])-'0';

      for( it=sparse_state_table.begin(); it != sparse_state_table.end(); it++)
      {
        if( it->first == curr_state )
        {
            input_state dummy = it->second;
            if ( (it->second).input == curr_input )
            {
                    next_state = (it->second).new_state;
                    found = true;
                    break;
            }
        }
      }

      cout << "Current state : " << curr_state ;
      cout << " Input symbol : " << curr_input ;

      if ( found == true)
      cout << " New state : " << next_state << endl;

      else
      {
          cout << " New state : EMPTY " << endl;
          cout << "Input is rejected" << endl;           //terminate here
          break;
      }

      bool accept = false;

      if ( m == input_string.length()-1)
      {
          for( int k=0; k<final_state_n; k++)
            {
                if ( next_state == final[k] )
                {
                   accept = true;
                   break;
                }
            }


      if ( accept ) cout << "Input is accepted" << endl;
      else cout << "Input is rejected" << endl;
      }


      curr_state = next_state;
      m++;

   }


   return 0;
}
