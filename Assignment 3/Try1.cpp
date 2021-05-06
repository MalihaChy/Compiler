#include<bits/stdc++.h>
using namespace std;

FILE *p1;
char c;
string s = "";
vector<string>v, lexeme_list, symbol_table[100];
string Name;
string Id_Type;
int Sl_No, index;
string Data_Type;
string Scope = "global";
string Value;
int search_result;

int Search(string Name)
{

    for(int i=0; i<=index; i++)
    {
        if(symbol_table[i][0] == Name)return i;
    }
    return -10;
}

void Update(int i)
{
    symbol_table[i][4] = Value;
}


void Display()
{
    cout<<"Displaying the Symbol Table\n\n";
    cout<<"Sl No\tName\t\tId Type\t\tData Type\tScope\t\tValue\n";
    for(int i = 0; i<15; i++)
    {
        cout<<i+1<<"\t";
        for(int j = 0; j<symbol_table[i].size(); j++)
            cout<<symbol_table[i][j]<<"\t\t";
        cout<<endl;
    }
}

int go_search(string x)
{
    for(int i=0; i<index; i++)
    {
        for(int j=0; j<symbol_table[i].size(); j++)
        {
            if(j==0 && symbol_table[i][j] == Name)
                return i;
        }
    }
    return -1;
}

void Insertion()
{
    Sl_No = 0;
    index = 0;
    for(int i = 0; i<lexeme_list.size(); i++)
    {
        if(lexeme_list[i] == "id")
        {
            Data_Type = lexeme_list[i-1];
            Sl_No++;
            i++;
            Name = lexeme_list[i];
            i++;
            if(lexeme_list[i] == "(")
            {
                Id_Type = "func";
                Scope = Name;
                Value = " ";
            }
            else
            {
                Id_Type = "var";
                if(lexeme_list[i] == "=")
                {
                    i++;
                    Value = lexeme_list[i];
                }
            }

            //cout<<endl<<Search("z")<<endl;

            //if(index>0)cout<<Search(Name)<<endl;
            //symbol_table[index].push_back(to_string(Sl_No));
            cout<<go_search(Name)<<endl;
            search_result = go_search(Name);
            if(search_result == -1)
            {
                symbol_table[index].push_back(Name);
                symbol_table[index].push_back(Id_Type);
                symbol_table[index].push_back(Data_Type);
                if(Scope == Name)symbol_table[index].push_back("global");
                else symbol_table[index].push_back(Scope);
                symbol_table[index].push_back(Value);
                index++;
            }
            else
            {
                Update(search_result);
            }

        }
    }

}


void step_2()
{
    Insertion();
    Display();
}

void step_1()
{
    p1 = fopen("input_for_step1.txt", "r");
    while((c = fgetc(p1)) != EOF)
    {
        if(c == ' ')
        {
            v.push_back(s);
            s = "";
        }
        else
        {
            s += c;
        }
    }
    cout<<"Output for Step 1\n\n";
    for(int i = 0; i<v.size(); i++)
    {
        if(v[i] == "[id")
        {
            cout<<v[i];
            cout<<" ";
            lexeme_list.push_back("id");
        }
        else
        {
            cout<<"[";
        }
        i++;
        cout<<v[i];
        v[i].resize(v[i].size() - 1);
        lexeme_list.push_back(v[i]);
    }
    cout<<endl<<endl<<endl;
    fclose(p1);
}

int main()
{
    step_1();
    step_2();
    //Insertion();
    //Display();
    //Search("z");
}
