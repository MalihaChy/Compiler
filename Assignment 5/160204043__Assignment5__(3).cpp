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


bool relop()
{
    if(s[i]=='='||s[i]=='>'||s[i]=='<'||s[i]=='!')
    {
        if(s[i]=='=')return true;
        else return true;
    }
    else return false;
}

bool extn()
{
    i++;
    if(relop())
    {
        if(E())return true;
        else return false;
    }
    return true;
}

bool expn()
{
    if(E())
    {
        i++;
        if(extn())return true;
        else return false;
    }
    else return false;
}

bool asgn_stat()
{
    if(s[i]=='a'||s[i]=='b'||s[i]=='c'||s[i]=='d'||s[i]=='e')
    {
        i++;
        if(s[i]=='=')
        {
            i++;
            if(expn())return true;
            else return false;
        }
        else return false;
    }
    else return false;
}

bool stat()
{
    if(asgn_stat())return true;
    else return false;
}

int main()
{
    cout<<"Enter an assignment expression :\n";
    cin>>s;
    if(stat())cout<<"Valid\n";
    else cout<<"Invalid\n";
}
