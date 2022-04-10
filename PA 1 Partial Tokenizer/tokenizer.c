/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
    char* inputString; 
    char* curr; 
    int error; 
    size_t length;
    int index; 
};

typedef struct TokenizerT_ TokenizerT;

/*
 * TKCreate creates stream[i]new TokenizerT object for stream[i]given token stream
 * (given as stream[i]string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change to increase efficiency.)
 * If the function succeeds, it returns stream[i]non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts )
{
    TokenizerT* tokenizer = (TokenizerT*) malloc(sizeof(TokenizerT));
    tokenizer->length = strlen(ts);
    if(tokenizer->length == 0)
    {
        return NULL;
    }
    tokenizer->error = 0;
    tokenizer->index = 0;
    tokenizer->inputString = (char*)malloc(sizeof(char)*(1+tokenizer->length));
    strcpy(tokenizer->inputString, ts);
    tokenizer->curr = (char*)malloc(sizeof(char)*(1+tokenizer->length));
    return tokenizer;
}

/*
 * TKDestroy destroys stream[i]TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    free(tk->curr);
    free(tk);
	free(tk->inputString);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns stream[i]C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    int i,j;
    char* finalString; 
    finalString = (char*)malloc(sizeof(char));
     char* stream = (char*)malloc(sizeof(char)*(1+tk->length)); //original string
    strcpy(stream, tk->inputString);
	i = tk->index;
    j = 0;
    
    
    while(stream[i] == ' ' || stream[i] == '\t' || stream[i] == '\v' || stream[i] == '\t' || stream[i] == '\f' || stream[i] == '\r' || stream[i] == '\n' ) {
        i++;
    }
    
    if (isalpha(stream[i]))
    {
        while(isalnum(stream[i]))
        {
            finalString[j] = stream[i];
            i++;
            j++;
        }
        tk->index = i;
        printf("WORD: ");
        return finalString;
    }
    
    if (isdigit(stream[i]))
    {
        if(stream[i] == '0')
        {
            if (stream[i+1] <= '7' && stream[i+1] >= '0')
            {
                while(stream[i] <= '7' && stream[i] >= '0')
                {
                    finalString[j] = stream[i];
                    i++;
                    j++;
                }
                tk->index = i;
                printf("OCTAL: ");
                return finalString;
            }
            
            if (stream[i+1] == 'x' || stream[i+1] == 'X')
            {
                if(isxdigit(stream[i+2]))
                {
                    while(j<2)
                    {
                        finalString[j] = stream[i];
                        j++;
                        i++;
                    }
                    while(isxdigit(stream[i]))
                    {
                    finalString[j] = stream[i];
                    i++;
                    j++;
                    }
                    tk->index = i;
                    printf("HEXADECIMAL: ");
                    return finalString;
                }
                
                else
                {
                    while(j<3)
                    {
                        finalString[j] = stream[i];
                        j++;
                        i++;
                    }
						tk->index = i;
                        printf("MAL INPUT: ");
                        return finalString;
                    }
                }
            }
        
            if (stream[i+1]== '.')
            {
                if(isdigit(stream[i+2]))
                {
                    while(j<2)
                    {
                        finalString[j] = stream[i];
                        j++;
                        i++;
                    }
                    while(isdigit(stream[i]))
                    {
                        finalString[j] = stream[i];
                        i++;
                        j++;
                    }
                    
                    if(stream[i] == 'E' || stream[i] == 'e')
                    {
                        if(stream[i+1] == '+' || stream[i+1] == '-')
                        {
                            
                            if(isdigit(stream[i+2]))
                            {
								int k;
                                for(k = 0; k<2; k++)
                                {
                                    finalString[j] = stream[i];
                                    j++;
                                    i++;
                                }
                                
								while(isdigit(stream[i]))
                                {
                                    finalString[j] = stream[i];
                                    i++;
                                    j++;
                                }
                                tk->index = i;
                                printf("FLOAT: ");
                                return finalString;
                                   
                            }
                            else
                            {
								int k;
                                for(k = 0; k<3; k++)
                                {
                                    finalString[j] = stream[i];
                                    j++;
                                    i++;
                                }
                                tk->index = i;
                                printf("MAL INPUT: ");
                                return finalString;
                            }
                        }
                               
                        else
                        {
                            if(isdigit(stream[i+1]))
                               {
								   int k;
                                   for(k = 0; k<2; k++)
                                   {
                                       finalString[j] = stream[i];
                                       j++;
                                       i++;
                                   }
                                   while(isdigit(stream[i]))
                                   {
                                       finalString[j] = stream[i];
                                       i++;
                                       j++;
                                   }
                                   
                                   tk->index = i;
                                   
                                   printf("FLOAT: ");
                                   return finalString;
                                   
                               }
                               
                               else
                               {
								   int k;
                                   for(k = 0; k<2; k++)
                                   {
                                       finalString[j] = stream[i];
                                       j++;
                                       i++;
                                   }
                                   tk->index = i;
                                   printf("MAL INPUT: ");
                                   return finalString;
                               }

                        }
                               
                    }
                    
                    tk->index = i;
                    
                    printf("FLOAT: ");
                    return finalString;
                }
            }
        
		else
        {
            while(isdigit(stream[i]))
            {
                finalString[j] = stream[i];
                i++;
                j++;
            }
            
            if (stream[i]== '.' || stream[i]== 'E' || stream[i] == 'e')
            {
                if(stream[i] == 'E' || stream[i] == 'e')
                {
                    if(stream[i+1] == '+' || stream[i+1] == '-')
                    {
                        
                        if(isdigit(stream[i+2]))
                        {
							int l;
                            for( l = 0; l<2; l++)
                            {
                                finalString[j] = stream[i];
                                j++;
                                i++;
                            }
                            while(isdigit(stream[i]))
                            {
                                finalString[j] = stream[i];
                                i++;
                                j++;
                            }
                            tk->index = i;
							printf("float ");
                            return finalString;
                        }
                        else
                        {
							int l;
                            for(l = 0; l<3; l++)
                            {
                                finalString[j] = stream[i];
                                j++;
                                i++;
                            }
                            tk->index = i;
                            printf("MAL INPUT: ");
                            return finalString;
                        }
                    }
                    
                    else
                    {
                        if(isdigit(stream[i+1]))
                        {
							int l;
                            for(l = 0;l<2; l++)
                            {
                                finalString[j] = stream[i];
                                j++;
                                i++;
                            }
                            while(isdigit(stream[i]))
                            {
                                finalString[j] = stream[i];
                                i++;
                                j++;
                            }
                            tk->index = i;
                            printf("FLOAT: ");
                            return finalString;
                        }
                        else
                        {
							int l;
                            for(l = 0; l<2; l++)
                            {
                                finalString[j] = stream[i];
                                j++;
                                i++;
                            }
                            tk->index = i;
							printf("MAL INPUT: ");
                            return finalString;
                        }
                        
                    }
                    
                }

                
                if (stream[i]== '.')
                {
                    if(isdigit(stream[i+1]))
                    {
						int k;
                        for(k = 0; k<2; k++)
                        {
                            finalString[j] = stream[i];
                            j++;
                            i++;
                        }
                        while(isdigit(stream[i]))
                        {
                            finalString[j] = stream[i];
                            i++;
                            j++;
                        }
                        
                        if(stream[i] == 'E' || stream[i] == 'e')
                        {
                            if(stream[i+1] == '+' || stream[i+1] == '-')
                            {
                                
                                if(isdigit(stream[i+2]))
                                {
									int l;
                                    for(l = 0; l<2; l++)
                                    {
                                        finalString[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    
                                    
                                    while(isdigit(stream[i]))
                                    {
                                        finalString[j] = stream[i];
                                        i++;
                                        j++;
                                    }
                                    tk->index = i;
                                    printf("FLOAT: ");
                                    return finalString;
                                    
                                }
                                else
                                {
									int l;
                                    for(l = 0; l<3; l++)
                                    {
                                        finalString[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    
                                    tk->index = i;
                                    printf("MAL INPUT: ");
                                    return finalString;
                                }
                            }
                            
                            else
                            {
                                if(isdigit(stream[i+1]))
                                {
									int l;
                                    for(l = 0;l<2; l++)
                                    {
                                        finalString[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    while(isdigit(stream[i]))
                                    {
                                        finalString[j] = stream[i];
                                        i++;
                                        j++;
                                    }
                                    tk->index = i;
                                    printf("FLOAT: ");
                                    return finalString;
                                    
                                }
                                
                                else
                                {
									int l;
                                    for(l = 0; l<2; l++)
                                    {
                                        finalString[j] = stream[i];
                                        j++;
                                        i++;
                                    }
                                    tk->index = i;
                                    printf("MAL INPUT: ");
                                    return finalString;
                                } 
                            } 
                        }
                        tk->index = i;
                        printf("FLOAT: ");
                        return finalString;
                    }
                }
            }
            tk->index = i;
            printf("DECIMAL: ");
            return finalString;
        }
    }
    if(stream[i] == '.')
    {
        printf("PERIOD ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
    }
    
    if(stream[i] == '(')
    {
        printf("LEFTPARANTHESIS ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
    }
    
    if(stream[i] == ')')
    {
        printf("RIGHTPAFINALSTRINGHESIS ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
    }
    
    if(stream[i] == '{')
    {
        printf("LEFTCURLYBRACKET ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
    }
    
    if(stream[i] == '}')
    {
        printf("RIGHTCURLYBRACKET ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '[')
    {
        printf("LEFTBRACE ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == ']')
    {
        printf("RIGHTBRACE ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i]== '+')
    {
        if(stream[i+1] == '=')
        {
            printf("PLUSEQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
        }
        if(stream[i+1] == '+')
        {
            printf("INCREMENT ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
        }
        printf("PLUS ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i]== '-')
    {
        if(stream[i+1] == '=')
        {
            printf("MINUSEQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        if(stream[i+1] == '-')
        {
            printf("DECREMENT ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        if(stream[i+1] == '>')
        {
            printf("STRUCTPOINTER ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("MINUS ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '*')
    {
        if(stream[i+1] == '=')
        {
            printf("MULTIPLYEQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
        }
        printf("MULTIPLY ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '*')
    {
        if(stream[i+1] == '=')
        {
            printf("DIVIDEEQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("DIVIDE ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '%')
    {
        if(stream[i+1] == '=')
        {
            printf("MODULUSEQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("MODULUS ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '&')
    {
        if(stream[i+1] == '&')
        {
            printf("LOGICAL-AND ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        if(stream[i+1] == '=')
        {
            printf("AND/OR ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("AND ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '!')
    {
        if(stream[i+1] == '=')
        {
            printf("NOT-EQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("NEGATE ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '~')
    {
        printf("1'SCOMP ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i]== '<')
    {
        if(stream[i+1] == '=')
        {
            printf("LESSOREQUAL ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        if(stream[i+1] == '<')
        {
            printf("SHIFTLEFT ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("LESSTHAN ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '>')
    {
        if(stream[i+1] == '=')
        {
            printf("GREATEROREQUAL ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        if(stream[i+1] == '>')
        {
            printf("SHIFTRIGHT ");
            
        }
        printf("GREATERTHAN ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '^')
    {
        if(stream[i+1] == '=')
        {
            printf("EXCLUSIVEOREQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("EXCLUSIVEOR ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == '|')
    {
        if(stream[i+1] == '|')
        {
            printf("LOGICAL-OR ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        if(stream[i+1] == '=')
        {
            printf("OREQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("BITWISE-OR ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i]== ':')
    {
        printf("COLON ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
    if(stream[i] == ';')
    {
        printf("SEMICOLON ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
	
	 if(stream[i] == '"')
    {
        printf("QUOTES ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
     
	if(stream[i] == '#')
    {
        printf("POUND ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
	
	 if(stream[i] == '@')
    {
        printf("AMPERSAND ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
	
	 if(stream[i] == '?')
    {
        printf("CONDITIONAL ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
	
    if(stream[i]== '=')
    {
        if(stream[i+1] == '=')
        {
            printf("EQUALS ");
            while(j<2)
            {
                finalString[j] = stream[i];
                j++;
                i++;
            }
            tk->index = i;
            return finalString;
            
        }
        printf("ASSIGNMENT ");
        finalString[j] = stream[i];
        j++;
        i++;
        tk->index = i;
        return finalString;
        
    }
    
   
    if((stream[i-1] == ' ' || stream[i-1] == '\t' || stream[i-1] == '\v' || stream[i-1] == '\t' || stream[i-1] == '\f' || stream[i-1] == '\r' || stream[i-1] == '\n') && i == tk->length )
    {
        tk->error = 1;
        finalString[j] = '\0';
		tk->index = i;
        return finalString;
        
    }
    
    else
    {
        tk->error = 1;
        printf("ERROR: [Ox%02x]\n", stream[i]);
        finalString[j] = '\0';
        i++;
        tk->index = i;
        return finalString;
        
    }
	i++;
    return "ERRORS";
}

/*
 * main will have stream[i]string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on stream[i]separate line.
 */

int main(int argc, char **argv) {
    
    if (argc == 1)
    {
        printf("error: did not enter a string\n");
        return 0;
    }
    
    if (argc != 2)
    {
        printf("error: too many arguments\n");
        return 0;
    }
    
    char* str = argv[1];
    TokenizerT* tokenizer = TKCreate(str);
    
    while (tokenizer->index<(tokenizer->length))
    {
    tokenizer->curr = TKGetNextToken(tokenizer);
        if(tokenizer->error == 1)
        {
            tokenizer->error = 0;
            continue;
        }
        
        printf("\"%s\"\n", tokenizer->curr);
    }
    
    TKDestroy(tokenizer);
    
    return 0;
}