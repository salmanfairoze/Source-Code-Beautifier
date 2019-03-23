/*
	This is a code to beautify
	any given syntactically correct
	C source code.

	Written by Salman_Fairoze
	on 22/03/2019
	Student @ PES University

	Make any untidy code readable
	and enjoy reading the beautified
	code :-)

	Code on!! 
*/


#include<stdio.h>
#include<string.h>

void trim(char * str,int flag);
void add_indent(char*s, int count);
void beautify(char* src);

void trim(char * str,int flag)
{
    int index, i;
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }
    i = 0;
    while(str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0';
    i = 0;
    index = -1;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }

        i++;
    }
    if(flag)
    {
    	str[index + 1] = ';';
    	str[index + 2] = '\0';
    }
    else
    	str[index + 1] = '\0';	
}

void add_indent(char*s, int count)
{
	char res[1000];
	int i,j=0;
	for (i = 0; i < count; ++i)
	{
		res[i]=putchar('\t');
	}
	while(s[j]!='\0')
		res[i++]=s[j++];
	res[i]='\0';
	strcpy(s,res);
}

void beautify(char* src)
{
	FILE* fp1=fopen(src,"r");
	FILE* fp2=fopen("final.c","w");
	char buffer[1000];
	char token[1000];
	int i=0;int j=0;
	int indent=0;
	while(fgets(buffer,1000,fp1)!=NULL)
	{
		i=0;
		while(buffer[i]!='\0')
		{
			if(buffer[i]!='{' && buffer[i]!='}' && buffer[i]!=';')
				token[j++]=buffer[i];
			else
			{
				token[j]='\0';
				if(buffer[i]==';')
				{
					trim(token,1);
					add_indent(token,indent);
					fprintf(fp2, "%s\n", token);
				}
				else if (buffer[i]=='{')
				{
					trim(token,0);
					add_indent(token,indent);
					fprintf(fp2, "%s\n", token);
					strcpy(token,"{");
					fprintf(fp2, "%s\n", token);
					++indent;
				}
				else if (buffer[i]=='}')
				{
					indent--;
					strcpy(token,"}");
					add_indent(token,indent);
					fprintf(fp2, "%s\n",token );
				}
				j=0;
			}
			++i;
		}
	}
	fclose(fp1);
	fclose(fp2);
}

int main()
{
	char file[100];
	scanf("%s",file);
	beautify(file);
}