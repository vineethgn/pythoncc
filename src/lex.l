%option stack
%{


/* Include this file to indentify tokens. 
Use bison -d filename.y to generate parser
*/
#include <string>
#include <stack>
#include <fstream>
#define SAVE_TOKEN yylval.str = new std::string(yytext, yyleng)
#define TOKEN(t) (yylval.token = t)
#include "parse.hpp"
#include <cstdio>
extern "C" int yywrap() { }

%}




escapeseq      		\\(.|\n)(?# "\" <any ASCII character>)
longstringchar 		[^\\](?# <any source character except "\">)
shortstringchar         [^\\|\'|\"|\n](?# <any source character except "\" or newline or the quote>)
longstringitem 		{longstringchar}|{escapeseq}
shortstringitem         {shortstringchar}|{escapeseq}
longstring    		(\'\'\'{longstringitem}*\'\'\')|(\"\"\"{longstringitem}*\"\"\")
shortstring    		(\'{shortstringitem}*\')|(\"{shortstringitem}*\")
stringprefix		'r'|'u'|'(ur)'|'R'|'U'|'(UR)'|'(Ur)'|'(uR)'
stringliteral		{stringprefix}?({shortstring}|{longstring})

DIGIT [0-9]
ID [a-zA-Z][a-zA-Z0-9]*

%x FORDEDENT
%%

%{


	int current_indentation = 0;
	int i;
	int len=0;
	int flag=0;

	std::stack<int> indentation_stack;

%}


print   {return TOKEN(PRINT);};
"="	{SAVE_TOKEN; return EQ;};
"+"	{SAVE_TOKEN; return PLUS;};
"-"	{SAVE_TOKEN; return MINUS;};
"*"	{SAVE_TOKEN; return MUL;};
"/"	{SAVE_TOKEN; return DIV;};


<FORDEDENT>.* 	{
			indentation_stack.pop();
			return DEDENT;
			yyless(len-2);
			if(indentation_stack.top() <= current_indentation)
				BEGIN(0);
			
		}

\\\n	/* explicit line joining */

\n	return NEWLINE;

[ \t]*'#'.*	/* comment line */

^[ \t]*. {
		current_indentation = 0;
		if(indentation_stack.empty())
			indentation_stack.push(0);
		for (i = 0; yytext[i] != '\0'; i++)	
			if(yytext[i] == ' ')
				current_indentation += 1;
			else if(yytext[i] == '\t')
				current_indentation += 8;
		len= strlen(yytext); 
		if (indentation_stack.top() == current_indentation)
			yyless(len-1);
		else if (indentation_stack.top() < current_indentation) 
		{
			indentation_stack.push(current_indentation);
			return INDENT;
			yyless(len-1);
		}
		else if (indentation_stack.top() > current_indentation)
		{
			BEGIN(FORDEDENT);
			yyless(len-1);
		}
	}

{DIGIT}+ {	
		SAVE_TOKEN;
		return(NUMBER);
	 }

{ID} 	{
		SAVE_TOKEN;
		return(IDENTIFIER);
	}

{stringliteral}	{
			SAVE_TOKEN;
			return STRING;
		}



%%

int input(char* file)
{
	yyin = std::fopen(file,"r");
	return 0;
}

void close()
{
	fclose(yyin);
}
