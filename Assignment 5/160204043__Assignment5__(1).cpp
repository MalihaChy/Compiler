#include<bits/stdc++.h>
using namespace std;

string s;
int sz;
int i = 0;

bool X()
{
    if(s[i]=='b')
    {
        i++;
        if(s[i]=='b' || s[i]=='c')
        {
            i++;
            X();
        }
        else
        {
            i--;
            return false;
        }
    }
    else return false;
}

bool A()
{
    if(s[i]=='a')
    {
        i++;
        if(X())return true;
        else if(s[i]=='d'&& (i+1)==sz)return true;
        else return false;
    }
}

int main()
{
    cout<<"A --> aXd\n";
    cout<<"X --> bbX\n";
    cout<<"X --> bcX\n";
    cout<<"X --> epsilon\n";
    cout<<"\n\nEnter a string\n";

    cin>>s;
    sz = s.size();
    if(sz>=2){
        if(A())cout<<"valid\n";
        else cout<<"invalid\n";
    }
    else cout<<"invalid\n";
}
