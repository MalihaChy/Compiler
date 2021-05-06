#include<bits/stdc++.h>
using namespace std;

char c;
FILE *p1, *p2;
vector<string>v, v1;
string s = "";
int sz;

void step_2()
{
    int cnt = 1;
    sz = v1.size();
    for(int i = 0; i<sz ; i++)
    {
        if(v1[i] == "[id"){
            cout<<cnt<<"\t";
            int data_type = i-1;
            i++;
            cout<<v1[i]<<"\t";
            i++;
            if(v1[i] == "(]")cout<<"func\t";
            else cout<<"var\t";
            cout<<v1[data_type]<<"\t";
            if(v1[i] == "=]")cout<<v1[i+1]<<"\t";
            cnt++;
        }
        cout<<"\n";
    }


}

void step_1()
{
    p1 = fopen("input_for_step1.txt", "r");
    p2 = fopen("output_of_step1.txt", "w");
    while((c = fgetc(p1)) != EOF){
        if(c == ' '){
            v.push_back(s);
            s = "";
        }
        else s += c;
    }
    sz = v.size();
    for(int i = 0; i<sz ;i++)
    {
        if(v[i] == "[id"){
            cout<<v[i]<<" ";
            v1.push_back(v[i]);
            for(int j=0;j<v[i].size();j++){
                c = v[i][j];
                fputc(c, p2);
            }
            fputc(' ', p2);
        }
        else{
            cout<<"[";
            fputc('[', p2);
        }
        i++;
        cout<<v[i];
        v1.push_back(v[i]);
        for(int j=0;j<v[i].size();j++){
            c = v[i][j];
            fputc(c, p2);
        }
    }
    fclose(p1);
    fclose(p2);
    cout<<endl<<endl<<endl;
    step_2();
}

int main()
{
    step_1();
}
