CC=gcc
CFLAGS=-Wall -g

# The name of the final executable
TARGET=calc

# Object files
OBJS=parser.tab.c lex.yy.c

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lfl

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

clean:
	rm -f $(TARGET) lex.yy.c parser.tab.c parser.tab.h
