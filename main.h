#ifndef MAIN_H
#define MAIN_H

#define SUCCESS 1
#define FAILURE 0

#define KEYWORD_SIZE 32
#define OPERATOR_SIZE 13
#define SYMBOL_SIZE 4
#define SPECIAL_SIZE 5
#define DELIM_SIZE 3

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//tokens
extern char* keyword[];
extern char operator[];
extern char symbol[];
extern char special[];
extern char delim[];



/*Function Declarations*/
void lexical_analyze(FILE* fptr);
void check_type(char* token);
int is_keyword(char* token);
int is_digit(char* token);
int is_special(char ch);
int is_operator(char token);
int is_assignment(char ch);
int is_symbol(char ch);
int is_octal(char* number);
int is_bin(char* number);
int is_hexa(char* number);

void process_identifier(char** ptr);
int process_complex_operator(char** ptr); 
int process_single_char(char** ptr);
void process_char(char** ptr);
void process_string(char** ptr) ;
void skip_delimiters(char** ptr);


#endif