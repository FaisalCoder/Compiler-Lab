#include<iostream>
#include<string>
using namespace std;

int main()
{
     string input_string;
     cout << "Enter input as 0,1 or 2" << endl;
     getline(cin,input_string);


     int i=0,input;
     char state = 'A',base = '0';


     while( i < input_string.length() )
     {
         input = (input_string[i])-'0';

         cout << "Current state : " << state ;
         switch( state )
         {

            case 'A' :
                     if ( input == 0 ) state = 'B';
                     else if( input == 1 ) state = 'A';
                     else if( input == 2 ) state = 'B';

                     break;

            case 'B' :
                     if ( input == 0 ) state = 'E';
                     else if( input == 1 ) state = 'A';
                     else if( input == 2 ) state = 'C';

                     break;

            case 'C' :
                     if ( input == 0 ) state = 'A';
                     else if( input == 1 ) state = 'E';
                     else if( input == 2 ) state = 'D';

                     break;

            case 'D' :
                     if ( input == 0 ) state = 'C';
                     else if( input == 1 ) state = 'D';
                     else if( input == 2 ) state = 'E';

                     break;

            case 'E' :
                     if ( input == 0 ) state = 'E';
                     else if( input == 1 ) state = 'D';
                     else if( input == 2 ) state = 'A';

                     break;


         }

         cout << " New state : " << state ;
         cout << " Input symbol : " << input_string[i] ;
         if ( state == 'E' ) cout << " which is accepting state" << endl;
         else cout << " which is non-accepting state" << endl;
         i++;

     }

     return 0;
}

