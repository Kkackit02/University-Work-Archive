LEX=flex
CC=gcc
CFLAGS=-Wall -O2

all: lexer

lexer: lexer.l
	$(LEX) lexer.l
	$(CC) $(CFLAGS) -o $@ lex.yy.c

clean:
	rm -f lex.yy.c lexer
