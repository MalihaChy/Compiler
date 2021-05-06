#include<bits/stdc++.h>
using namespace std;

FILE *p1, *p2;
char c;
string file;
vector< pair<int,string> >v;
char space = ' ';
string token;
vector<string>lexeme_list, type_list;
vector< pair<string,string> >identifier_list;

void CommentRemove()
{
    c=fgetc(p1);
    if(c=='/')
    {
        while(c=fgetc(p1))
        {
            if(c=='\n')break;
        }
    }
    else if(c=='*')
    {
        while(c=fgetc(p1))
        {
            if(c=='/')break;
        }
    }
}

void Comment_And_Extra_Space_Remove(int flag)
{
    if(flag == 1)
    {
        p1 = fopen("input.c", "r");
        p2 = fopen("output1.txt", "w");
    }
    else if(flag == 0)
    {
        p1 = fopen("output.txt","r");
        p2 = fopen("output1.txt","w");
    }
    while((c=fgetc(p1))!=EOF)
    {
        if(c=='/')CommentRemove();
        else if(c==' '||c=='\t')
        {

            while(c=fgetc(p1))
            {
                if(c!=' '&&c!='\t')
                {
                    if(c=='/')CommentRemove();
                    else
                    {
                        fputc(' ',p2);
                        fputc(c,p2);
                    }
                    break;
                }
            }
        }
        else fputc(c,p2);
    }
    fclose(p1);
    fclose(p2);

}

void Lexeme_Division()
{
    p1 = fopen("output1.txt", "r");
    p2 = fopen("output.txt","w");

    while((c=fgetc(p1))!=EOF)
    {
        if(c==39)
        {
            fputc(space,p2);
        }
        else if(c==';'||c=='='||c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='<'||c=='>'||c==','||c=='{'||c=='}')
        {
            fputc(space,p2);
            fputc(c,p2);
            if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c==',')
                fputc(space,p2);
            else if(c=='='||c=='<'||c=='>')
            {
                c=fgetc(p1);
                if(c=='='||c=='<'||c=='>')
                {
                    fputc(c,p2);
                    fputc(space,p2);
                }
                else
                {
                    fputc(space,p2);
                    fputc(c,p2);
                }
            }
        }
        else fputc(c,p2);
    }
    fclose(p1);
    fclose(p2);
    Comment_And_Extra_Space_Remove(0);
}

void Inserting_Line_Number()
{
    p1 = fopen("output1.txt", "r");
    p2 = fopen("output2.txt", "w");

    int i = 1;
    char num[5];
    itoa(i, num, 10);

    int j;
    for(j = 0; num[j] != '\0'; j++)fputc(num[j], p2);
    fputc(':', p2);

    while((c = fgetc(p1)) != EOF)
    {
        fputc(c, p2);
        if(c == '\n')
        {
            itoa(++i, num, 10);
            for(j = 0; num[j] != '\0'; j++)fputc(num[j], p2);
            fputc(':', p2);
            fputc(' ', p2);
        }
    }
    fclose(p1);
    fclose(p2);
}

void Getting_The_Whole_File_In_A_String()
{
    p1 = fopen("output2.txt", "r");
    while((c=fgetc(p1))!= EOF)file+=c;
}

void Handling_Curly_Braces()
{
    stack<int>s;
    string line_no;
    int x;
    int sz = file.size();
    for(int i=0; i<sz;)
    {
        line_no = "";
        while(file[i]!=':')
        {
            line_no+=file[i];
            i++;
        }
        stringstream ss(line_no);
        ss >> x;
        while(file[i]!='\n' && i<sz)
        {
            if(file[i]=='{')s.push(x);
            else if(file[i]=='}')
            {
                if(!s.empty())s.pop();
                else v.push_back(make_pair(x, " --> error: Extra/Unmatched } found\n"));
            }
            i++;
        }
    }
    while(!s.empty())
    {
        v.push_back(make_pair(s.top(), " --> error: Single/Unmatched { found\n"));
        s.pop();
    }
}

void Handling_Parentheses()
{
    stack<int>s;
    string line_no;
    int sz = file.size();
    int x;
    for(int i=0; i<sz;)
    {
        line_no = "";
        while(file[i]!=':')
        {
            line_no+=file[i];
            i++;
        }
        stringstream ss(line_no);
        ss >> x;
        while(file[i]!='\n' && i<sz)
        {
            if(file[i]=='(')s.push(x);
            else if(file[i]==')')
            {
                if(!s.empty())s.pop();
                else v.push_back(make_pair(x, " --> error: Extra/Unmatched ) found\n"));
            }
            i++;
        }
    }
    while(!s.empty())
    {
        v.push_back(make_pair(s.top(), " --> error: Single/Unmatched ( found\n"));
        s.pop();
    }
}

void Handling_If_else()
{
    stack<int>s;
    string line_no;
    int sz = file.size();
    int x;
    for(int i=0; i<sz;)
    {
        line_no = "";
        while(file[i]!=':')
        {
            line_no+=file[i];
            i++;
        }
        stringstream ss(line_no);
        ss >> x;
        while(file[i]!='\n' && i<sz)
        {
            if(file[i]=='i')
            {
                i++;
                if(file[i]=='f')s.push(x);
            }
            else if(file[i]=='e')
            {
                i++;
                if(file[i]=='l')
                {
                    i++;
                    if(file[i]=='s')
                    {
                        i++;
                        if(file[i]=='e')if(!s.empty())s.pop();
                            else v.push_back(make_pair(x, " --> error: else without a previous if\n"));
                    }
                }
            }
            i++;
        }
    }
}

void Check_Semicolons()
{
    string line_no;
    int sz = file.size();
    int x;
    for(int i=0; i<sz;)
    {
        line_no = "";
        while(file[i]!=':')
        {
            line_no+=file[i];
            i++;
        }
        stringstream ss(line_no);
        ss >> x;
        int cnt = 0;
        while(file[i]!='\n' && i<sz)
        {
            if(file[i]=='f')
            {
                i++;
                if(file[i]=='o')
                {
                    i++;
                    if(file[i]=='r')
                    {
                        while(file[i]!=')')
                        {
                            i++;
                            if(file[i]==';')cnt++;
                        }
                        if(cnt<2)v.push_back(make_pair(x," --> error: Inside for loop, a semicolon is expected\n"));
                        else if(cnt>2)v.push_back(make_pair(x," --> error: Inside for loop, an extra semicolon is found\n"));
                    }
                }
            }
            if(file[i]==';')
            {
                i++;
                while(1)
                {
                    if(file[i]==' ')
                    {
                        i++;
                        continue;
                    }
                    else if(file[i]==';')v.push_back(make_pair(x, " --> error: Extra semicolon found\n"));
                    else break;
                    i++;
                }
            }
            i++;
        }
    }
}

void Print_Error_Report()
{
    cout<<"Error Report\n\n";
    sort(v.begin(), v.end());
    int sz = v.size();
    ofstream out("output.txt");
    for(int i=0; i<sz; i++){
        cout<<"Line "<<v[i].first<<v[i].second<<"\n";
        stringstream ss;
        ss << v[i].first;
        string input = "Line " + ss.str() + v[i].second + "\n";
        out << input;
    }
    out.close();
}

int Variable_Check(string token)
{
    int i=0;
    int sz = token.size();
    if(token[i]=='_'||(token[i]>='A'&&token[i]<='Z')||(token[i]>='a'&&token[i]<='z'))i++;
    else return 0;
    for(; i<sz; i++)
    {
        if(token[i]=='_'||(token[i]>='A'&&token[i]<='Z')||(token[i]>='a'&&token[i]<='z')||(token[i]>='0'&&token[i]<='9'));
        else return 0;
    }
    return 1;
}

void Tokenization()
{
    p1 = fopen("output3.txt","w");
    p2 = fopen("output2.txt","r");
    while((c=fgetc(p2))!=EOF)
    {
        while(c!=' '&&c!=EOF)
        {
            token+=c;
            c=fgetc(p2);
        }
        if(token == "int"||token == "double"||token == "float"||token == "void"||token == "return"||token == "for"||token == "if"||token == "else");
        else if(Variable_Check(token)==1)token = "id " + token;
        int sz = token.size();
        for(int i=0; i<sz; i++)fputc(token[i], p1);
        fputc(' ', p1);
        token = "";
    }
    fclose(p1);
    fclose(p2);
}

bool Is_Number(string token)
{
    int sz = token.size();
    int i = 0;
    for(; i<sz; i++)
    {
        if(token[i]>='0'&&token[i]<='9');
        else if(token[i]=='.')break;
        else return false;
    }
    for(i++; i<sz; i++)
    {
        if(token[i]>='0'&&token[i]<='9');
        else return false;
    }
    return true;
}

void Handling_Token_Duplication()
{
    ifstream p3("output2.txt");
    string line;
    while(getline(p3, line))
    {
        string flag = "";
        int sz = line.size();
        int i;
        int x;
        string line_no;
        for(i=0; i<sz; i++)
        {
            if(line[i]==':')break;
            else line_no+=line[i];
        }
        stringstream ss(line_no);
        ss >> x;
        for(i++; i<sz; i++)
        {
            while(line[i]!=' ' && i<sz)
            {
                token+=line[i];
                i++;
            }

            if(token == "int"||token == "double"||token == "float" ||token == "void"||token == "return")
            {
                if(flag=="kw")
                {
                    v.push_back(make_pair(x, " --> error: Duplicate Keyword Token Found\n"));
                    flag = "";
                }
                else flag = "kw";
            }
            else if(token == "+"||token == "-"||token == "*" ||token == "/"||token == ">"||token == "<"||token == "=="||token == ">=" ||token == "<="||token == "++"||token == "--")
            {
                if(flag=="op")
                {
                    v.push_back(make_pair(x, " --> error: Duplicate Operator Token Found\n"));
                    flag = "";
                }
                else flag = "op";
            }
            /*else if(Is_Number(token))
            {
                if(flag=="num")
                {
                    v.push_back(make_pair(x, " --> error: Duplicate Number Token Found\n"));
                    flag = "";
                }
                else flag = "num";
            }*/
            else flag = "";
            token = "";
        }
    }
}

bool If_Already_Exists(string id_name, string scope, string id_type)
{
    int sz = identifier_list.size();
    for(int i=0; i<sz; i++)
    {
        if(id_name == identifier_list[i].first)
        {
            if(scope == identifier_list[i].second)// || identifier_list[i].second == "global")
            {
                if(id_type == type_list[i]||id_type == "double"||id_type == "int"||id_type == "float"||id_type == "char")return true;
                else return false;
            }
        }
    }
    if(id_type == "int"||id_type == "double"||id_type == "char"||id_type == "float")
    {
        identifier_list.push_back(make_pair(id_name, scope));
        type_list.push_back(id_type);
    }
    return false;
}

void Handling_Duplicate_Identifiers()
{
    p1 = fopen("output3.txt", "r");
    string s = "";
    while((c = fgetc(p1)) != EOF)
    {
        if(c == ' ' || c == '\n')
        {
            lexeme_list.push_back(s);
            s = "";
        }
        else s += c;
    }
    int sz = lexeme_list.size();
    string name, scope = "global";
    for(int i = 0; i<sz; i++)
    {
        if(lexeme_list[i]=="id")
        {
            name = lexeme_list[i+1];
            if(lexeme_list[i+2]=="(")scope = name;
            bool answer;
            if(scope == name)answer = If_Already_Exists(name, "global", lexeme_list[i-1]);
            else answer = If_Already_Exists(name, scope, lexeme_list[i-1]);
            if(answer == true)
            {
                int j = i;
                while(j--)
                {
                    string x = lexeme_list[j];
                    if(x[lexeme_list[j].size()-1] == ':')
                    {
                        x.resize(x.size()-1);
                        stringstream ss(x);
                        int y;
                        ss >> y;
                        v.push_back(make_pair(y, " --> error: Duplicate Identifier Found\n"));
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    Comment_And_Extra_Space_Remove(1);
    Lexeme_Division();
    Inserting_Line_Number();
    Tokenization();
    Getting_The_Whole_File_In_A_String();
    Handling_Curly_Braces();
    Handling_Parentheses();
    Handling_If_else();
    Check_Semicolons();
    Handling_Token_Duplication();
    Handling_Duplicate_Identifiers();
    Print_Error_Report();

}

