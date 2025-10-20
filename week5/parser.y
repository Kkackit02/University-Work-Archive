%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Prototype for the lexer function
int yylex(void);
// Prototype for the error reporting function
void yyerror(const char *s);

// Symbol table structure
struct symbol {
    char *name;
    double value;
};

// Simple symbol table
#define NHASH 9997
struct symbol symtab[NHASH];

// Hash function for symbol table
static unsigned symhash(char *sym) {
    unsigned int hash = 0;
    unsigned c;
    while((c = *sym++)) hash = hash*9 ^ c;
    return hash;
}

// Look up a symbol
struct symbol *lookup(char* sym) {
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;
    while(--scount >= 0) {
        if(sp->name && !strcmp(sp->name, sym)) { return sp; }
        if(!sp->name) { // New entry
            sp->name = strdup(sym);
            sp->value = 0;
            return sp;
        }
        if(++sp >= symtab+NHASH) sp = symtab; // Wrap around
    }
    yyerror("symbol table overflow");
    abort();
}

// Set a variable's value
void setval(char *name, double val) {
    struct symbol *sp = lookup(name);
    sp->value = val;
}

// Get a variable's value
double getval(char *name) {
    struct symbol *sp = lookup(name);
    return sp->value;
}

}

/* Bison declarations */
%union {
    double dval;  // For returning double values
    char *sval;   // For returning symbol names (identifiers)
}

%token <dval> T_NUMBER
%token <sval> T_ID
%token T_PRINT

%type <dval> expr

%left '+' '-'
%left '*' '/'
%left '%'
%nonassoc UMINUS

%%

/* Grammar rules */
input: /* empty */
     | input line
     ;

line: stmt '\n'     { printf("= %g\n", $1); }
    | '\n'         { /* ignore empty lines */ }
    | error '\n'   { yyerrok; } /* error recovery */
    ;

stmt: expr                { $$ = $1; }
    | T_ID '=' expr       { setval($1, $3); $$ = $3; free($1); }
    | T_PRINT expr        { $$ = $2; } /* print value of expr */
    ;

expr: expr '+' expr       { $$ = $1 + $3; }
    | expr '-' expr       { $$ = $1 - $3; }
    | expr '*' expr       { $$ = $1 * $3; }
    | expr '/' expr       { if ($3 == 0.0) { yyerror("division by zero"); $$ = 0; } else { $$ = $1 / $3; } }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')'        { $$ = $2; }
    | T_NUMBER            { $$ = $1; }
    | T_ID                { $$ = getval($1); free($1); }
    ;

%%

/* C code section */
#include <stdio.h>

// Main function
int main() {
    printf("> ");
    return yyparse();
}

// Error reporting function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
