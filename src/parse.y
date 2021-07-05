%error-verbose
%{
#include<iostream>
#include "generator.hpp"

int yyerror(char *);
extern int yylex();

Node* root= NULL;

%}


%union {
       	 class Node* nodes;
	 std::string *str;
	 int token;
	 
}

%token <token> NEWLINE INDENT DEDENT 

%token <str> STRING NUMBER IDENTIFIER EQ PLUS MINUS MUL DIV
%token <token> PRINT

%type <nodes> root file_input stmt expr atom op
%type <nodes> print_stmt assign_stmt

%start root
%%

root: file_input { root= $1;};

file_input:       stmt { $$ = new Node;
			 $$-> add_leftchild($1);
			 }
		| stmt file_input { $$= new Node;
				   $$-> add_leftchild($1);
				   $$-> add_rightchild($2);
				};

stmt: print_stmt {$$=$1;} | assign_stmt {$$=$1}  /*| if_stmt*/;

print_stmt: PRINT expr NEWLINE { $$= new Nprint;
				 $$->leftchild= $2;
				 $$->rightchild=$2->rightchild;
			       };

expr:     atom { $$=$1->leftchild; } 
	| atom op atom {
 			        Noperator *opr= new Noperator();
				opr->add_leftchild($1->leftchild);
				opr->add_rightchild($3->leftchild);
				opr->value= $2->leftchild->get_value();
				$2->leftchild=NULL;
				$$=opr;
    		      };

/*if_stmt:   IF test COLON suite
	 | IF test COLON suite ELSE;*/

op:       PLUS  { Nstring *str = new Nstring($1); $$->add_leftchild(str);}
	| MINUS { Nstring *str = new Nstring($1); $$->leftchild=str;}
	| MUL   { Nstring *str = new Nstring($1); $$->leftchild=str;} 
	| DIV   { Nstring *str = new Nstring($1); $$->leftchild=str;};

atom:      STRING {
			Nstring *str=new Nstring($1);				
			$$->add_leftchild(str);

		  }
	 | NUMBER {
			Nnumber *str=new Nnumber($1);				
			$$->add_leftchild(str);

		  }
	 | IDENTIFIER {	Nidentifier *id = new Nidentifier($1);
			$$->add_leftchild(id);
		      };

assign_stmt: IDENTIFIER EQ expr NEWLINE {
						Nidentifier *id= new Nidentifier($1);
						Noperator *op = new Noperator;
						$$= op;
						$$->add_leftchild(id);
						$$->add_rightchild($3);
					};

%%

int yyerror(char *s)
{
	std::cerr<<s;
}
