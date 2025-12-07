// functions to check tokens
#include"main.h"
extern int error_flag;

//function to check token is keyword
int is_keyword(char* token)
{

    for(int i=0;i<KEYWORD_SIZE;i++)
    {
        if(strcmp(token,keyword[i])==0)
        {
           printf("%-10s :is a keyword\n",token);
           return SUCCESS;
        }
    }
    return FAILURE;
}
int is_assignment(char ch)
{
    return (ch == '=');
}
//function to check token is operator or not
int is_operator(char token)
{
    for(int i=0;i<OPERATOR_SIZE;i++)
    {
        if(token==operator[i])
        {
            return SUCCESS;
        }
    }
    return FAILURE;
}

//function to check token  is symbols
int is_symbol(char ch)
{
    for(int i=0;i<SYMBOL_SIZE;i++)
    {
        if(ch==symbol[i])
        {
            return SUCCESS;
        }
    }
    return FAILURE;
} 

//function to check token is special characters
int is_special(char ch)
{
    for(int i=0;i<SPECIAL_SIZE;i++)
    {
        if(ch==special[i])
        {
            return SUCCESS;
        }
    }
    return FAILURE;
}

//function to check token is digit
int is_digit(char* token) {
    int len = strlen(token);
    if(len == 0) return 0;

    int i = 0;
    int dot_count = 0;

    // optional sign at start
    if(token[0] == '+' || token[0] == '-') i++;

    for(; i < len; i++) {
        if(token[i] >= '0' && token[i] <= '9') continue;
        else if(token[i] == '.') {
            dot_count++;
            if(dot_count > 1) return 0;  // multiple dots -> invalid
        }
        else if(token[i] == 'f' && i == len-1) {
            // float literal ending with f, okay
            return SUCCESS;
        }
        else return FAILURE; // invalid character
    }

    return SUCCESS; // valid integer or float
}



// Function to check if token is a hexadecimal number (0x...)
int is_hexa(char* number)
{
    if(strncmp(number, "0x", 2) != 0)
    {
        return FAILURE; 
    }
  

    for(int i = 2; number[i]!='\0'; i++)
    {
        if(!((number[i] >= '0' && number[i] <= '9') ||
             (number[i] >= 'A' && number[i] <= 'F') ||
             (number[i] >= 'a' && number[i] <= 'f')))
        {
            printf("ERROR: Can't initialize hexadecimal number as %s\n", number);
            error_flag = 1;
            return SUCCESS;
        }
    }

    printf("%-10s :is a hexadecimal number\n", number);
    return SUCCESS;
}

// Function to check if token is a binary number (0b...)
int is_bin(char* number)
{
    if(strncmp(number, "0b", 2) != 0)
    return FAILURE;

    for(int i = 2; number[i]!='\0'; i++)
    {
        if(number[i] != '0' && number[i] != '1')
        {
            printf("ERROR: Can't initialize binary number as %s\n", number);
            error_flag = 1;
            return SUCCESS;
        }
    }

    printf("%-10s :is a binary number\n", number);
    return SUCCESS;
}


// Function to check if token is an octal number (starts with 0, not 0x)
int is_octal(char* number)
{
    if(number[0] != '0' || number[1] == 'x') 
    return FAILURE;

    for(int i = 0; number[i]; i++)
    {
        if(number[i] < '0' || number[i] > '7')
        {
            printf("ERROR: Can't initialize octal number as %s\n", number);
            error_flag = 1;
            return SUCCESS;
        }
    }

    printf("%-10s :is an octal number\n", number);
    return SUCCESS;
}
