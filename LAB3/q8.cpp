#include<iostream>
#include<string>
#include<map>
#include<fstream>
using namespace std;

string terminals = "e", nonterminals;             // e is epsilon

string dupliRemove( string  a )
{
    string w;
    for( int i=0; i<a.length();i++)
    {
        if ( w.find(a[i]) == string::npos)
        {
            w += a[i];
        }
    }

    return w;
}

//FIRST SET
string first( string a,multimap<char,string>& map)
{
    string first_ans;

    for (multimap<char, string>::iterator it = map.begin();it != map.end();++it)
    {
        if ( it->first == a[0])
        {
            //rhs is non-terminal
            for( int k = 0 ; k < (it->second).length(); k++)   //searching rhs of production
            {
               // multimap<char,string> cfg;
                bool repeat = false;
                string rhs;
                rhs += (it->second)[k];

                string tmp ;
                tmp  = first(rhs, map);

               const int length = tmp.length();
                //searching tmp for epsilon
                for( int i=0;i<length;i++)
                {
                    if ( tmp[i] == 'e')
                    {
                        if ( k != (it->second).length())                     //last symbol on rhs dont remove
                        tmp.erase(i,1);

                        first_ans += tmp;
                        repeat = true;        //epsilon found go to next symbol
                        break;
                    }
                }

                //epsilon not found  leave the loop
                if ( repeat == false)
                {

                    first_ans += tmp;
                    break;
                }
            }
        }

        else              //terminal        is part of loop not necessary but keep this way
            {
                for( int j=0 ; j< terminals.length();j++)
                {
                    if ( a[0] == terminals[j] )
                    {
                        first_ans += a[0];
                        break;
                    }
               }
            }
    }

    return first_ans;
}

string rhs_cfg(string a)
{
    int i=0;
    while ( a[i] != '-')i++;
    i+= 2;

     if ( i >= a.length()) return "-1";

    return a.substr(i,a.length()-i); // rhs of production
}

string firstMain( string a , multimap<char,string>& map )
{
    string first_ans,temp,e = "e";
    for( int i=0 ; i < a.length(); i++)
    {
        string in;
        in = a[i];
        temp = first(in , map);

        if ( temp.find(e) != string::npos)
        {
            temp.erase(temp.find(e),1);
            first_ans += temp;

            if ( i == a.length()-1)
            {
                first_ans += e;
            }
        }

        else
        {
            first_ans += temp;
            break;
        }
    }
    string ans =  dupliRemove(first_ans);
    return ans;
}

//FOLLOW SET
string follow( string a , multimap<char,string>& map)    //enter cfg
{
    string follow_ans;

    for (multimap<char,string>::iterator it = map.begin();it != map.end();++it)
    {
                     //means it is the start symbol
        if ( it == map.begin() && a[0] == it->first)
        {
            follow_ans += "$";
        }

        //scanning rhs to apply 2 rule to find follow
        if ( (it->second).find(a[0]) != string::npos)   // we found a[0]
        {
            int length = (it->second).length();
            int pos = (it->second).find(a[0]);
            string e = "e";

            if ( (pos+1) < length )              //not the last symbol
            {
                string p,tmp;
                p = (it->second).substr(pos+1,length-pos-1);
                tmp = firstMain(p,map);

                while( tmp.find(e) != string::npos)
                tmp.erase((tmp.find(e)),1);               //removing epsilon from first

                follow_ans += tmp;
            }

            string tmp2;
            tmp2 = (it->second).substr(pos+1,length-pos-1);     //need to modify this rule

           //applying 3 rule
            if ( (pos+1) == length  )
            {
                 string tmp1;
                 tmp1 += it->first;

                 if ( tmp1[0] == a[0])
                 {
                    continue;
                 }

                 follow_ans += follow(tmp1,map);
            }

            else if ( firstMain(tmp2,map).find(e) != string::npos )   //first has epsilon
            {
                string a1;
                a1 += it->first;

                if ( a1[0] == a[0]) continue;
                follow_ans += follow(a1,map);
            }
        }
    }

    return follow_ans;
}

int main()
{
    multimap<char,string> cfg;
    map<string,string> firstSet;
    map<string,string> followSet;
    fstream in("q8.txt");                       //Input File

    int i;
    string input,temp;

    while(true)
    {
       getline(in,input);

       //add to multimap
       if ( rhs_cfg(input) != "-1")
       cfg.insert(pair<char,string>(input[0],rhs_cfg(input)));

       if ( in.eof()) break;

    }

    cout << ".................CONTEXT FREE GRAMMAR.......................\n" << endl;

    for (multimap<char, string>::iterator it = cfg.begin();it != cfg.end();++it)
    {
        //store first set in a array
       cout << (*it).first << " - " << (*it).second << endl;
    }

    //asking for terminals and nonterminals
    cout << "Enter TERMINALS in the CFG .Press q to exit" << endl;
    while(true)
    {
        cin >> temp;

        if ( temp == "q" ) break;
        terminals += temp;

    }

    cout << endl;
    cout << "Enter NON-TERMINALS in the CFG" << endl;
    while(true)
    {
        cin >> temp;

        if ( temp == "q" ) break;
        nonterminals += temp;

    }

    cout << "\n Terminals " << terminals << "  \n Nonterminals " << nonterminals << endl;
    cout << "....................FIRST sets........................." << endl;

    char duplicateChecker = NULL ;
    for (multimap<char, string>::iterator it = cfg.begin(); it != cfg.end(); ++it)
    {
       if ( duplicateChecker != it->first)
       {
           string  lhs;
           lhs += it->first;
           string ans = dupliRemove(first(lhs,cfg));
           duplicateChecker = it->first;
           firstSet.insert(pair<string,string>(lhs,ans));    //adding to first hashtable
       }
    }

     for (multimap<string, string>::iterator it = firstSet.begin(); it != firstSet.end(); ++it)
     {
         cout << "FIRST( " << it->first << " ) = " << it->second << endl;
     }

    cout << "....................FOLLOW sets........................." << endl;
    duplicateChecker = NULL ;
    for (multimap<char, string>::iterator it = cfg.begin(); it != cfg.end(); ++it)
    {
       if ( duplicateChecker != it->first)
       {
          string  lhs;
          lhs += it->first;
          string ans = dupliRemove(follow(lhs,cfg));
          duplicateChecker = it->first;
          followSet.insert(pair<string,string>(lhs,ans));      //adding to follow hashtable
       }
    }

    for (multimap<string, string>::iterator it = followSet.begin(); it != followSet.end(); ++it)
     {
         cout << "FOLLOW( " << it->first << " ) = " << it->second << endl;
     }

    in.close();
    return 0;
}
