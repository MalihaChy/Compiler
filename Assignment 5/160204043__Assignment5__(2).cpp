#include<bits/stdc++.h>
using namespace std;

string s;
int i = 0;
bool F();

bool ID()
{
    if(s[i]=='a' || s[i]=='b' || s[i]=='c' || s[i]=='d' || s[i]=='e')return true;
    else return false;
}

bool NUM()
{
    if(s[i]>='0' && s[i]<='9')return true;
    else return false;
}

bool T()
{
    if(F())
    {
        i++;
        if(s[i]=='*' || s[i]=='/' )
        {
            i++;
            if(F())return true;
            else
            {
                i--;
                return false;
            }
        }
        else
        {
            i--;
            return true;
        }
    }
    else return false;
}

bool E()
{
    if(T())
    {
        i++;
        if(s[i]=='+' || s[i]=='-')
        {
            i++;
            if(T())return true;
            else
            {
                i--;
                return false;
            }
        }
        else
        {
            i--;
            return true;
        }
    }
    else return false;
}

bool F()
{
    if(s[i]=='(')
    {
        i++;
        if(E())
        {
            i++;
            if(s[i]==')')return true;
            else
            {
                i--;
                return false;
            }
        }
        else
        {
            i--;
            return false;
        }
    }
    else if(ID())return true;
    else if(NUM())return true;
    else return false;
}




int main()
{
    cout<<"<Exp> --> <Term> + <Term> | <Term> - <Term> | <Term>\n";
    cout<<"<Term> --> <Factor> * <Factor> | <Factor> / <Factor> | <Factor>\n";
    cout<<"<Factor> --> ( <Exp> ) | ID | NUM\n";
    cout<<"ID --> a|b|c|d|e\n";
    cout<<"NUM --> 0|1|2|3|4|5|6|7|8|9\n";
    cout<<"\n\nEnter an expression\n";

    cin>>s;
    if(E())cout<<"Valid Expression\n";
    else cout<<"Invalid Expression\n";
}
