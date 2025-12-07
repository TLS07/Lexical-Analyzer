#include "main.h"
extern int error_flag;
char* keyword[]= {"char","int","float","double","void","short","long","signed","unsigned","const","volatile","auto","register","static","extern","typedef","if","else","switch","case","default","for","while","do","goto","return","break","continue","struct","union","enum","sizeof","NULL"};
char operator[] = {'+','-','/','%','^','!','~','*','<','>','&','|'};
char symbol[] = {'{','}','[',']'};
char special[] = {'(',')',';',','};
char delim[] = "\n\t ";

void lexical_analyze(FILE* fptr)
{
    char line[200];
    while(fgets(line,sizeof(line),fptr))
    {
        //if line is preprocessing line skip line
        if(line[0]=='#' )
        {
            printf("Header file\n");
            continue;
        }
        check_type(line);
    }

}

// main check_type function
void check_type(char* line)
{
    char *ptr =line;
    while(*ptr!='\0')
    {
        skip_delimiters(&ptr);

        if(*ptr=='"')
        {
            process_string(&ptr);
        }
        else if(*ptr=='\'')
        process_char(&ptr);

        else if(process_single_char(&ptr))
        continue;

        else if(process_complex_operator(&ptr))
        continue;

        else 
        process_identifier(&ptr);
    }
}


// Helper to skip delimiters
void skip_delimiters(char** ptr) {
    while (**ptr && strchr(delim, **ptr)) 
    {
        (*ptr)++;
    }
}

// Process string literal

void process_string(char** ptr) {
    char str[150];
    int i = 0;
    (*ptr)++; // skip opening "
    while (**ptr && **ptr != '"') {
        if (**ptr == '\\') {
            char next = *(*ptr + 1);
            if (next != 'b' && next != 'f' && next != 'n' && next != 'a' && next != 'v' && next != 't' && next != '0')   //checking for escape sequence
            {
                printf("ERROR: Invalid escape sequence \\%c\n", next);
                error_flag = 1;
                (*ptr)++;
            }
        }
        if (**ptr == ')' || **ptr == ';') {
            printf("ERROR: Closing \" missing\n");
            error_flag = 1;
            break;
        }
        str[i++] = **ptr;
        (*ptr)++;
    }
    str[i] = '\0';
    printf("%-10s :is a string literal\n", str);
    if (**ptr == '"') (*ptr)++; // skip closing "
}


// Process character constant
void process_char(char** ptr) {
    char ch = 0;
    char token[100];
    int i = 0;
    (*ptr)++; // skip opening '
    if (**ptr) {
        token[i++] = **ptr;
        (*ptr)++;
    }
    if (**ptr == '\'') {
        printf("%-20c is a character constant\n", token[0]);
        (*ptr)++;
    } else {
        while (**ptr && **ptr != '\'') {
            token[i++] = **ptr;
            (*ptr)++;
        }
        token[i] = '\0';
        printf("ERROR: Invalid character constant %s\n", token);
        error_flag = 1;
        if (**ptr == '\'') (*ptr)++;
    }
}


// Process operators, special chars, symbols, assignment
int process_single_char(char** ptr) {
    if (is_operator(**ptr)) {
        printf("%-10c :is an operator\n", **ptr);
        (*ptr)++;
        return SUCCESS;
    } 
    else if (is_assignment(**ptr)) {
        printf("%-10c :is an assignment operator\n", **ptr);
        (*ptr)++;
        return SUCCESS;
    }
    else if (is_symbol(**ptr)) {
        printf("%-10c :is a symbol\n", **ptr);
        (*ptr)++;
        return SUCCESS;
    }

    else if (is_special(**ptr)) {
        printf("%-10c :is a special character\n", **ptr);
        (*ptr)++;
        return SUCCESS;
    } 

    return FAILURE;
}


// Process relational, shift, and logical operators
int process_complex_operator(char** ptr) {
    if (**ptr == '<' || **ptr == '>') {
        char op1 = **ptr;
        char op2 = *(*ptr + 1);
        char op3 = *(*ptr + 2);

        if (op2 == '=') {
            printf("%c%-10c :is a relational operator\n", op1, op2);
            *ptr += 2;
            return SUCCESS;

        } else if (op1 == '<' && op2 == '<') {
            if (op3 == '=') {
                printf("%c%c%-10c :is an operator\n", op1, op2, op3);
                *ptr += 3;
                return SUCCESS;

            } else {
                printf("%c%-10c :is a left shift operator\n", op1, op2);
                *ptr += 2;
                return SUCCESS;
            }
        } else if (op1 == '>' && op2 == '>') {
            if (op3 == '=') {
                printf("%c%c%-10c :is an operator\n", op1, op2, op3);
                *ptr += 3;
                return SUCCESS;
            } else {
                printf("%c%-10c :is a right shift operator\n", op1, op2);
                *ptr += 2;
                return SUCCESS;
            }
        } else {
            printf("%-10c :is a relational operator\n", op1);
            (*ptr)++;
            return SUCCESS;
        }
    }
    else if (**ptr == '&' && *(*ptr+1) == '&') {
        printf("&&                   is a logical operator\n");
        *ptr += 2;
        return SUCCESS;
    }
    else if (**ptr == '|' && *(*ptr+1) == '|') {
        printf("||                   is a logical operator\n");
        *ptr += 2;
        return SUCCESS;
    }
    else if (**ptr == '&' || **ptr == '|') {
        printf("%-10c :is a bitwise operator\n", **ptr);
        (*ptr)++;
        return SUCCESS;
    }
    return FAILURE;
}


// Process identifiers, numbers, arrays
void process_identifier(char** ptr) {
    char token[100];
    int i = 0;
    while (**ptr && !strchr(delim, **ptr) && !is_special(**ptr) && !is_assignment(**ptr) && !is_operator(**ptr) && !is_symbol(**ptr)) {
        token[i++] = **ptr;
        (*ptr)++;
    }
    token[i] = '\0';

    if (strlen(token) == 0) return;

    if (!is_keyword(token) && !is_digit(token) && !is_bin(token) && !is_octal(token) && !is_hexa(token)) {
        // Check for arrays
        if (**ptr == '[') {
            char array_token[100];
            strcpy(array_token, token);
            int j = strlen(array_token);
            array_token[j++] = *(*ptr)++; // [
            char temp[20];
            int k = 0;
            while (**ptr && **ptr != ']') temp[k++] = *(*ptr)++;
            temp[k] = '\0';
            if (**ptr == ']') {
                array_token[j++] = *(*ptr)++; // ]
                array_token[j] = '\0';
            }
            printf("%-10s :is an array\n", array_token);
        } else {
            printf("%-10s :is an identifier\n", token);
        }
    }
}


