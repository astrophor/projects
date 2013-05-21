
CC=g++ -g
LEX=flex
YACC=bison

das_demo: das_yacc.tab.c das_lex.c
	${CC} -o $@ das_yacc.tab.c das_lex.c -lfl

das_yacc.tab.c das_yacc.tab.h: das_yacc.y
	${YACC} -d $<

das_lex.c: das_lex.l
	${LEX} $<
	mv lex.yy.c das_lex.c


clean:
	rm *.c *.h


