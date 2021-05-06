#include<bits/stdc++.h>
using namespace std;

int main()
{
    ifstream p1("input.c");
    string line;
    int j, k = 0;
    while(getline(p1, line))
    {
        k++;
        string y;
        vector< char > s;
        int sz = line.size();
        for(int i=0; i<sz; i++)
        {
            if(line[i]=='(')
            {
                j = i-1;
                while(line[j]!=' ')
                {
                    s.push_back(line[j]);
                    j--;
                }
                reverse(s.begin(), s.end());
                for(int x=0; x<s.size();x++)
                    y+=s[x];
                cout<<y<<" : Line No "<<k<<endl;
            }
        }
    }
}
