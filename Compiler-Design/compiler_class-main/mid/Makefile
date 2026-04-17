# OS에 관계없이 최대한 공통으로 동작하게 구성
# 필요 도구: bison, flex, gcc/clang
# macOS(Homebrew), Linux, MSYS2(MINGW64) 등에서 확인용

TARGET := calc
LEX    := flex
YACC   := bison
CC     := cc

LEX_SRC := scanner.l
YACC_SRC := parser.y

# Bison 생성물
YACC_C  := parser.tab.c
YACC_H  := parser.tab.h

# Flex 생성물
LEX_C   := lex.yy.c

CFLAGS  := -O2 -Wall -Wextra
YFLAGS  := -Wall -Wcounterexamples -d
LDFLAGS :=

# 대부분의 플랫폼에서 -lfl 사용 (macOS Homebrew flex 포함)
LIBS := -ll

# 일부 환경(아주 오래된 macOS)에서 -ll 이 필요한 경우를 대비한 대체 규칙
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
# Homebrew flex면 -lfl이 기본. 실패 시 수동 링크 안내 메시지 제공.
endif

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(YACC_C) $(LEX_C)
	$(CC) $(CFLAGS) $(YACC_C) $(LEX_C) -o $@ $(LDFLAGS) $(LIBS) || \
	( echo "링크 실패 시: LIBS=-ll 로 재시도 해보세요 (예: make clean && make LIBS=-ll)"; exit 1 )

$(YACC_C) $(YACC_H): $(YACC_SRC)
	$(YACC) $(YFLAGS) $(YACC_SRC)

$(LEX_C): $(LEX_SRC) $(YACC_H)
	$(LEX) $(LEX_SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET) $(YACC_C) $(YACC_H) $(LEX_C)
