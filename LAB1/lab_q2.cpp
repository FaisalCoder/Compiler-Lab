#include<iostream>
#include<new>
#include<string>
using namespace std;

int main()
{
   string input_string;

   int input_n,state_n,final_state_n;
   cout << "Enter number of inputs" << endl;    //0,1,2
   cin >> input_n;

   cout << "Enter number of states" << endl;   //a,b,c..
   cin >> state_n;

   char ** state_table = new char*[state_n+1];   //make first element null it is index of inputs
   for(int i = 0; i < state_n+1; i++ )
   {
      state_table[i] = new char[input_n+1];

   }

   state_table[0][0] = '-';   // first one is default
  //input values
   for( int i=1 ; i < input_n+1 ; i++)
   {
       cout << "ENTER INPUT VALUES" << endl;
       cin >> state_table[0][i];
   }

   // states and new states
   for( int i=1 ; i< state_n+1 ; i++)
   {
       cout << "ENTER CURRENT STATE " << endl;
       cin >> state_table[i][0];

       for( int j=1; j< input_n+1 ; j++)
       {
          cout << "ENTER NEW STATE FOR INPUT " << state_table[0][j] << endl;
          cin >> state_table[i][j];
       }
   }

   char initial;
   //Enter initial state
   cout << "ENTER INITIAL STATE" << endl;
   cin >> initial;

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

   int i2=0;
   char curr_state = initial,next_state,curr_input;

   //logic
   while( i2 < input_string.length() )
   {
      curr_input = input_string[i2];

      for( int i=1; i< state_n+1;i++)
      {
        if( state_table[i][0] == curr_state )
        {
          for( int j=1; j< input_n+1; j++)        //checking new state by comparing
          {
            if ( state_table[0][j] == curr_input )
            next_state = state_table[i][j];
          }

        }
      }


      cout << "Current state : " << curr_state ;
      cout << " Input symbol : " << curr_input ;
      cout << " New state : " << next_state << endl;

      bool accept = false;

      if ( i2 == input_string.length()-1)
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
      i2++;
   }

   return 0;
}
