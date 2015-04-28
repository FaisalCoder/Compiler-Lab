#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<stack>
using namespace std;

string terminals = "e", nonterminals, startsymbol;             // e is epsilon

struct parseEntry
{
    //terminal,production
    string production;
    string input;
};

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
          //          cout << "terminal " << terminals[j] << endl;
                    if ( a[0] == terminals[j] )
                    {
                        first_ans += a[0];
                    //   cout << first_ans << endl;
                       break;
                    }
               }
            }
    }


   //
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
                //p += (it->second)[pos+1];         //change this to accomaodate whole till end
                p = (it->second).substr(pos+1,length-pos-1);
                tmp = firstMain(p,map);

                while( tmp.find(e) != string::npos)
                tmp.erase((tmp.find(e)),1);               //removing epsilon from first

                follow_ans += tmp;
            }

            string tmp2;
            tmp2 = (it->second).substr(pos+1,length-pos-1);     //need to modify this rule

        //    cout << "POS  " << pos+2 << " length " << length << " FOLLOW OF " << a[0] << " rhs " << it->second << endl;
            //applying 3 rule
            if ( (pos+1) == length  )
            {
                 string tmp1;
                 tmp1 += it->first;

                 if ( tmp1[0] == a[0])
                 {
                    continue;
                 }

             //    cout << "FOLLOW  "  << follow(tmp1,map) << " to be added in " << a[0] << endl;
                 follow_ans += follow(tmp1,map);
              //   cout << "Which is " << follow_ans << endl;
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

//PREDICTIVE PARSING TABLE PART
void PrediciveParsingTable(multimap<char,parseEntry>& ptable ,multimap<char,string> cfg)
{
    //creating empty parsing table
    for( int i=0; i < nonterminals.length(); i++)
    {
        char lhs = nonterminals[i];

        for( int j=0; j< terminals.length();j++)
        {
            parseEntry temp;
            if( terminals[j] != 'e')
            {
                temp.input = terminals[j];
                ptable.insert(pair<char,parseEntry>(lhs,temp));
            }

        }
        //adding the dollar entry
        parseEntry dollar;
        dollar.input = "$";
        ptable.insert(pair<char,parseEntry>(lhs,dollar));
    }


    //computations
    for ( multimap<char, string>::iterator it = cfg.begin(); it != cfg.end(); ++it)
    {
        string t;
        string lhs1,rhs1 ;
        lhs1 += it->first;      //lhs
        rhs1 += it->second;     //rhs
        t += it->second;           //rhs
        string first1 = firstMain(t,cfg);
     //   cout << "\n ..............LHS............ " << it->first << endl;
      //  cout << "First of " << t << " is " << first1  << endl;   //checked right

        for( int k=0; k< first1.length(); k++)
        {
            if ( first1[k] == 'e')
            {
             //   cout << "taking e" << endl;
                string p1,follow1;
                p1 += it->first;
                follow1 = dupliRemove(follow(p1,cfg));
              //  cout << "Follow of " << p1 << " " << follow1  << endl;

                //for each terminal in follow
                for ( int l=0 ; l< follow1.length(); l++)
                {
                    for (multimap<char,parseEntry>::iterator pit = ptable.begin(); pit != ptable.end(); ++pit)
                    {
                        parseEntry temp = pit->second;
                   //     cout << "LHS: " << it->first << " INPUT: " << temp.input << " PRODUCTION: "  << temp.production << endl;

                        if ( (pit->first == it->first) && ((temp.input)[0] == follow1[l]))
                        {
                            string pro;
                            pro += lhs1 + " - " + rhs1;
                     //      cout << "CFG: " << it->first << " - " << it->second << endl;
                        //   cout << "CFG ACTUAL: " << pro << endl;
                            (pit->second).production += pro;
                        }
                    }
                }
            }

            else
            {
               //gives the range with same lhs in the map
                pair <multimap<char,parseEntry>::iterator, multimap<char,parseEntry>::iterator> range;
                range = ptable.equal_range(it->first);

                for (multimap<char,parseEntry>::iterator pit = ptable.begin(); pit != ptable.end(); ++pit)
                {
                    parseEntry temp = pit->second;
            //        cout << "LHS: " << it->first << " INPUT: " << temp.input << " PRODUCTION: "  << temp.production << endl;

                    if ( (pit->first == it->first) && ((temp.input)[0] == first1[k]))
                    {
                        string pro;
                        pro += lhs1 + " - " + rhs1;

                        (pit->second).production += pro;
                    }

                }

                //
            }
        }
    }
}
//LL PARSER PROGRAM
bool LLParser( string b, multimap<char,parseEntry>& ptable)
{
    string stackinput;      //to display stack content
    string input2,isymbol,top;
    input2 = b + "$";       //input symbol
    cout << "Input: " << input2 << endl;

    stack<char> pstack;               //stack of parser
    int i=0;                          // i is iterator of input string
    isymbol = input2[i];              //isymbol is current input symbol
    top =  startsymbol;
                            //put start symbol on top of stack
    pstack.push('$');
    stackinput += '$';
    pstack.push(startsymbol[0]);
    stackinput += startsymbol[0];

    //working
    cout << "STACK\t\tInput\t\tOutput\n";
    cout << "$" << top << "\t\t" << input2 << "\t" <<   endl ;

    while( top[0] != '$' )
    {
        bool p1 = false;
        string production,dummy ;        //from parse table.searching the parse table
        for (multimap<char,parseEntry>::iterator pit = ptable.begin(); pit != ptable.end(); ++pit)
        {
             parseEntry temp2 = pit->second;

             if ( (pit->first == top[0]) && ((temp2.input) == isymbol))
             {
                production = temp2.production;        //extracting production to be used in rule 3,4
             }
        }

        if ( top == isymbol)
        {
            //cout << "1\n";
        //    cout << "\t\tMatch " << top << endl;
            dummy = top;
            pstack.pop();
            int l = stackinput.length()-1;
            stackinput.resize(l);
            p1 = true;
            i++;
            isymbol = input2[i];
        }

        else if ( (terminals.find(top[0])) != string::npos)  //top is terminal
        {
          // cout << "2\n";
            return false;
        }

        else if (production == "")
        {
          //  cout << "3\n";
            return false;
        }

        else if ( production != "")
        {
            pstack.pop();
            int l = stackinput.length()-1;
            stackinput.resize(l);

            //pushing the production rhs on stack
            string p = rhs_cfg(production);
        //    cout << "RHS OF PRODUCTION: " << p << endl;
            for( int i= (p.length()-1); i >=0 ;i--)
            {
       //         cout << "PUSH: " << p[i] << endl;
                if ( p[i] != 'e')
                {
                    pstack.push(p[i]);
                    stackinput += p[i];
                }

            }
        }

        top = "";
        top = pstack.top();

        //display
        string inp = input2.substr(i);

        if ( p1 )
        cout << stackinput << "\t\t" << inp << "\t\t" << "Match " << dummy << endl ;

        else
        cout << stackinput << "\t\t" << inp << "\t\t" << production << endl ;

    }
    return true;
}


int main()
{
    multimap<char,string> cfg;
    map<string,string> firstSet;
    map<string,string> followSet;
    multimap<char,parseEntry> parsetable;
    fstream in("q8.txt");                       //Input File

    int i,dummy= 0;
    string input,temp;

    while(true)
    {
       getline(in,input);
       if ( dummy == 0)
       {
           startsymbol = input[0];     //assigning start symbol
           dummy++;
       }

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
  //  cout << "....................FIRST sets........................." << endl;

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

       //    cout << "FIRSTMAIN " << dupliRemove(firstMain(lhs,cfg)) << endl;
       }
    }

   // cout << "....................FOLLOW sets........................." << endl;
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
    //CREATING PREDICTIVE PARSING TABLE
    PrediciveParsingTable(parsetable,cfg);

    //LL Parsing
    string tobeparsed;
    while (true)
    {
        cout << ".................... LL(1) Parser ........................." << endl;
        cout << "\nEnter the string to be parsed.Press 1 to exit " ;
        cin >> tobeparsed;

        if (tobeparsed == "1")
        break;

        cout << endl;
        bool parsed = LLParser( tobeparsed, parsetable);
        if ( parsed == true)
        {
            cout << "Input string " << tobeparsed << " is parsed\n\n";
        }

        else
        cout << "Error.   Input string " << tobeparsed << " is not parsed\n\n";

    }


    in.close();
    return 0;
}
