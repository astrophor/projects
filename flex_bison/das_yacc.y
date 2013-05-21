/*
 * das语法分析器
 */

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylex(void);
extern "C"
{
	void yyerror(char * s, ...);
	void emit(char * s, ...);
}

%}

%union 
{
	long long llval;
	double floatval;
	char * strval;
	int subtok;
}

%token <llval> INTEGER
%token <strval> NAME
%token <strval> STRING

%left OR
%left AND
%left '!'
%left <subtok> COMPARISON /* == != > < >= <= */
%left '|'
%left '&'
%left <subtok> SHIFT
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS

%token AS
%token BY
%token DEFAULT
%token FROM
%token GROUP
%token INTO
%token JOIN
%token LENGTH
%token ON
%token OPT_CREATE
%token PRIMARYKEY
%token SELECT
%token WHERE


%type <llval> create_column_list select_expr_list val_list table_references groupby_list into_list opt_val_list

%start stmt_list

%%


stmt_list: stmt ';'
 	| stmt_list stmt ';'
;

stmt: create_stmt { emit("STMT"); }
    	| select_stmt { emit("STMT"); }
;

create_stmt:  OPT_CREATE NAME '(' create_column_list ')' { emit("CREATE DATA %s with %d columns", $2, $4); free($2); }
;

create_column_list : create_column { $$ = 1; }
   	|  create_column_list ',' create_column { $$ = $1 + 1; }
;

create_column: NAME LENGTH '(' INTEGER ')' def_stmt { emit("column name: %s, length: %lld", $1, $4); free($1); }
;

def_stmt:  /* if there is no def_stmt means that this column can be null */
	| DEFAULT STRING { emit("column default value: %s", $2); free($2); }
;

select_stmt:  SELECT select_expr_list primarykey FROM table_references opt_where opt_groupby INTO into_list { emit("select %lld columns from %lld tables into %lld columns", $2, $5, $9); }
;

primarykey: PRIMARYKEY NAME /* 指定主键 */ { emit("primary key is %s", $2); free($2); }
;

select_expr_list: select_expr { $$ = 1; }
	| select_expr_list ',' select_expr { $$ = $1 + 1; }
;

select_expr: expr opt_as_alias
;

opt_as_alias: AS NAME { emit("alias %s", $2); free($2); }
    	| NAME {emit("alias %s", $1); free($1); }
	| /* nil */
;

expr: raw_expr
    	| '(' raw_expr ')'
;

raw_expr: 
    	/* variables */
	  NAME { emit("NAME %s", $1); free($1); }
	| NAME '.' NAME { emit("NAME %s.%s", $1, $3); free($1); free($3); }
	| '(' NAME ')' NAME { emit("column type: %s, NAME %s", $2, $4); free($2); free($4); }
	| '(' NAME ')' NAME '.' NAME { emit("column type: %s, NAME %s.%s", $2, $4, $6); free($2); free($4); free($6); }
	| STRING { emit("STRING %s", $1); free($1); }
	| INTEGER { emit("INTEGER %lld", $1); }

	/* expressions */
	| expr '+' expr { emit("ADD"); }
	| expr '-' expr { emit("SUB"); }
	| expr '/' expr { emit("DIV"); }
	| expr '*' expr { emit("MUL"); }
	| expr '%' expr { emit("MOD"); }
	| '-' expr %prec UMINUS  /* eg: -1 */ { emit("NEG"); }
	| expr OR expr { emit("OR"); }
	| expr AND expr { emit("AND"); }
	| expr '|' expr { emit("BIT OR"); }
	| expr '&' expr { emit("BIT AND"); }
	| expr SHIFT expr { emit("SHIFT %s", $2==1?"LEFT":"RIGHT"); }
	| '!' expr { emit("NOT"); }
	| expr COMPARISON expr { emit("COMPARISON %lld", $2); }

	/* functions */
	| NAME '(' opt_val_list ')' { emit("CALL %s with %lld args", $1, $3); free($1); }
;

opt_val_list: /* nill */ { $$ = 0; }
	| val_list
;

val_list: expr { $$ = 1; }
	| expr ',' val_list { $$ = 1 + $3; }
;

table_references: table_reference { $$ = 1; }
       	| table_references ',' table_reference { $$ = $1 + 1; }
;

table_reference: table_factor
       	| join_table
;

table_factor: NAME opt_as_alias { emit("TABLE %s", $1); free($1); }
    	| NAME '.' NAME opt_as_alias { emit("TABLE %s.%s", $1, $3); free($1); free($3); }
;

join_table: table_reference JOIN table_factor join_condition { emit("JOIN"); }
;

join_condition:  ON expr  /* eg: on a.id=b.id */ { emit("JOIN_ON_CONDITION"); }
;

opt_where: /* nil */
 	| WHERE expr { emit("WHERE"); }
;

opt_groupby: /* nil */
   	| GROUP BY groupby_list { emit("GROUP BY %lld columns", $3); }
;

groupby_list: expr { $$ = 1; }
    	| groupby_list ',' expr { $$ = $1 + 1; }
;

into_list: NAME '.' NAME { emit("into column: %s.%s", $1, $3); free($1); free($3); $$ = 1; }
 	| into_list ',' NAME '.' NAME { emit("into column: %s.%s", $3, $5); free($3); free($5); $$ = $1 + 1; }
;


%%

void emit(char * s, ...)
{
	va_list ap;
	va_start(ap, s);

	printf(" ");
	vfprintf(stdout, s, ap);
	printf("\n");
}

void yyerror(char * s, ...)
{
	extern int yylineno;
	va_list ap;
	va_start(ap, s);

	fprintf(stderr, "%d: error: ", yylineno);
	vfprintf(stderr, s, ap);
	fprintf(stderr, "\n");
}

int main(int argc, char ** argv)
{
	if ( argc != 2)
	{
		printf("usage: %s filename\n", argv[0]);
		return 1;
	}

	extern FILE * yyin;
	if (NULL == (yyin = fopen(argv[1], "r")))
	{
		printf("open file: %s failed\n", argv[1]);
		return 1;
	}

	if (!yyparse())
		printf("SQL parse worked\n");
	else
		printf("SQL parse failed\n");

	return 0;
}


