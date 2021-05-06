#include<stdio.h>

char c;
char space = ' ';
FILE *p1,*p2;

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

int main()
{
    p1 = fopen("input.c","r");
    p2 = fopen("output.txt","w");
    if(!p1)printf("File cannot be opened!\n");
    else
    {
        while((c=fgetc(p1))!=EOF)
        {
            if(c=='/')CommentRemove();
            else if(c==' '||c=='\n'||c=='\t')
            {
                while(c=fgetc(p1))
                {
                    if(c!=' '&&c!='\n'&&c!='\t')
                    {
                        if(c=='/')CommentRemove();
                        else
                        {
                            fputc(space,p2);
                            fputc(c,p2);
                        }
                        break;
                    }
                }
            }
            else fputc(c,p2);
        }
    }
    fclose(p1);
    fclose(p2);
    p1 = fopen("input.c","r");
    p2 = fopen("output.txt","r");

    printf("\n\n------ Input File ------\n\n");
    while((c=fgetc(p1))!=EOF)printf("%c",c);
    printf("\n\n------ Output File ------\n\n");
    while((c=fgetc(p2))!=EOF)printf("%c",c);
    printf("\n");

}
