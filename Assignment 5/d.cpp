#include<bits/stdc++.h>
using namespace std;

int main()
{
    int e=37, d=1, z= 60;
    for(int i= 1;;i++)
    {
        d = ((i*z)+1)/e;
        if((e*d)%z == 1)
        {
            cout<<d<<endl<<i;
            return 0;
        }
    }
}
