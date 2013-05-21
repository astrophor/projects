/*
 * das´Ê·¨·ÖÎöÆ÷
 */

%option noyywrap nodefault yylineno case-insensitive

%{

#include "das_yacc.tab.h"
#include <stdarg.h>
#include <string.h>

extern "C"
{
	void yyerror(char *s, ...);
}

%}

%%

and { return AND; }
as { return AS; }
by { return BY; }
create[ \t\n]+data { return OPT_CREATE; }
default { return DEFAULT; }
from { return FROM; }
group { return GROUP; }
into { return INTO; }
join { return JOIN; }
length { return LENGTH; }
on { return ON; }
or { return OR; }
primarykey { return PRIMARYKEY; }
select { return SELECT; }
where { return WHERE; }


-?[0-9]+ { yylval.llval = atoll(yytext); return INTEGER; }
'(\\.|''|[^'\n])*' |
\"(\\.|\"\"|[^"\n])*\" { yylval.strval = strdup(yytext); return STRING; }

'(\\.|[^'\n])*$ { yyerror("Unterminated string %s", yytext); }
\"(\\.|[^"\n])*$ { yyerror("Unterminated string %s", yytext); }

[A-Za-z][A-Za-z0-9_]* { yylval.strval = strdup(yytext); return NAME; }

[-+*&|/%,;()!.] { return yytext[0]; }

"&&" { return AND; }
"||" { return OR; }

"<<" { yylval.subtok = 1; return SHIFT; }
">>" { yylval.subtok = 2; return SHIFT; }

"==" { yylval.subtok = 1; return COMPARISON; }
">"  { yylval.subtok = 2; return COMPARISON; }
">=" { yylval.subtok = 3; return COMPARISON; }
"<"  { yylval.subtok = 4; return COMPARISON; }
"<=" { yylval.subtok = 5; return COMPARISON; }
"!=" { yylval.subtok = 6; return COMPARISON; }

[ \t\n] /* whitespace */
. { yyerror("mystery character '%c'", *yytext); }

%%

/*
int main()
{
	yylex();
	return 0;
}
*/


