#include<stdio.h>

FILE *p1, *p2;
char c, space = ' ';
char token[50];

void Lexeme_Division()
{
    p2 = fopen("output.txt","w");

    while((c=fgetc(p1))!=EOF)
    {
        /*if(c=='}')
        {
            fclose(p2);
            break;
        }*/
        if(c==39){
            fputc(space,p2);
            fputc(c,p2);
            fputc(space,p2);
            //printf("1%c%c2%c3\n",space,c,space);
        }
        else if(c==';'||c=='='||c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='<'||c=='>'||c==',')//||c=='\'')
        {
            fputc(space,p2);
            fputc(c,p2);
            if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c==',')//||c=='\'')
                fputc(space,p2);
            //if(c!=';'&&c!='='&&c!='<'&&c!='>'&&c!=',')fputc(space,p2);
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
}


int Number_Check(char *token)
{
    int i, l, s;
    i=0;
    if(isdigit(token[i]))
    {
        s=1;
        i++;
    }
    else if(token[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;
    l=strlen(token);
    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(token[i]))
                s=1;
            else if(token[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==2){
        if(isdigit(token[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    }
    if(s==3){
        for(; i<l; i++)
        {
            if(isdigit(token[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==3) s=1;
    return s;
}

int Variable_Check(char *token)
{
    int i=0;
    if(token[i]=='_'||(token[i]>='A'&&token[i]<='Z')||(token[i]>='a'&&token[i]<='z'))i++;
    else return 0;
    for(;token[i];i++){
        if(token[i]=='_'||(token[i]>='A'&&token[i]<='Z')||(token[i]>='a'&&token[i]<='z')||(token[i]>='0'&&token[i]<='9'));
        else return 0;
    }
    return 1;
}

int Token_Name(char *token)
{
    if(strlen(token)==1&&token[0]==' ')return -100;
    if(strcmp(token,"char")==0||strcmp(token,"int")==0||strcmp(token,"float")==0||strcmp(token,"if")==0||strcmp(token,"else")==0)return 0;
    else if(strcmp(token,";")==0||strcmp(token,",")==0||strcmp(token,"'")==0)return 1;
    else if(strcmp(token,"=")==0||strcmp(token,"<")==0||strcmp(token,">")==0||strcmp(token,"<=")==0||strcmp(token,">=")==0||strcmp(token,"==")==0||strcmp(token,"+")==0||strcmp(token,"-")==0||strcmp(token,"/")==0||strcmp(token,"*")==0)return 2;
    else if(Number_Check(token)==1)return 3;
    else if(Variable_Check(token)==1)return 4;
    else if(strcmp(token,"(")==0||strcmp(token,")")==0)return 5;
    else return 6;
}

void Tokenization()
{
    p2 = fopen("output.txt","r");
    while((c=fgetc(p2))!=EOF)
    {
        int i=0;
        while(c!=' '&&c!=EOF)
        {
            token[i]=c;
            i++;
            c=fgetc(p2);
        }
        int x = Token_Name(token);
        if(x==-100)continue;
        else if(x==0)printf("[kw ");
        else if(x==1) printf("[sep ");
        else if(x==2) printf("[op ");
        else if(x==3) printf(("[num "));
        else if(x==4) printf(("[id "));
        else if(x==5) printf(("[par "));
        else printf("[unkn ");
        int j;
        for(j=0; j<strlen(token); j++)printf("%c",token[j]);
        printf("]");
        for(j=0; j<50; j++)token[j]='\0';

    }
    fclose(p2);
}

int main()
{
    p1 = fopen("input2.c","r");
    if(!p1)printf("File Cannot Be Opened!\n");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='m')
            {
                c=fgetc(p1);
                if(c=='a')
                {
                    c=fgetc(p1);
                    if(c=='i')
                    {
                        c=fgetc(p1);
                        if(c=='n')
                        {
                            while(1)
                            {
                                c=fgetc(p1);
                                if(c=='{')
                                {
                                    Lexeme_Division();
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        Tokenization();
    }
}

