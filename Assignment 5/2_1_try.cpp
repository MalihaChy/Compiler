#include<bits/stdc++.h>
using namespace std;

string s;
vector<char>v;
stack<int>st;

bool ID(char c)
{
    if(c=='a' || c=='b' || c=='c' || c=='d' || c=='e')return true;
    else return false;
}

bool NUM(char c)
{
    if(c>='0' && c<='9')return true;
    else return false;
}

bool OP(char c)
{
    if(c=='+' || c=='-' || c=='*' || c== '/')return true;
    else return false;
}

bool test()
{
    int sz = s.size();
    for(int i=0; i<sz; i++)
    {
        if(s[i]=='(')
        {
            st.push(i);
        }
        else if(s[i]==')')
        {
            if(!st.empty() && (i-1)!=st.top())st.pop();
            else return false;
        }
        else v.push_back(s[i]);
    }

    if(!st.empty())return false;
    sz = v.size()-1;

    for(int i =0; i<sz; i+=2)
    {
        if(ID(v[i]) || NUM(v[i]));
        else return false;
        if(OP(v[i+1]));
        else return false;
    }
    cout<<"he";
    if(ID(v[sz]) || NUM(v[sz]))return true;
    else return false;
}



int main()
{
    while(1){
    cin>>s;
    if(test())cout<<"valid\n";
    else cout<<"invalid\n";
    }
}
