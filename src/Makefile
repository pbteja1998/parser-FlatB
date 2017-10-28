# bcc:	parser.tab.c lex.yy.c
# 	gcc parser.tab.c lex.yy.c -lfl -o bcc
# parser.tab.c: parser.y 
# 	bison -d parser.y 
# parser.tab.h: parser.y
# 	bison -d parser.y 
# lex.yy.c: scanner.l parser.tab.h
# 	flex scanner.l

# .PHONY: clean 
# clean:
# 	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true


CC = g++

bcc: parser.tab.c lex.yy.c Classes.cpp ClassDefs.h
	$(CC) -g -std=c++14 lex.yy.c parser.tab.c Classes.cpp -lfl -o bcc

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

parser.tab.c: parser.y 
	bison -vd parser.y 

clean:
	rm -f *.c parser.tab.h *.output

veryclean:
	rm -rf *.c parser.tab.h *.output bcc