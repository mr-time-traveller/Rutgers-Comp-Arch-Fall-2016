#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* substring(const char*, int, int);
int getsign(const char*);
int getexp(const char*);
int getsignif(const char*);
int chartoint(char);
int toDec(const char*);
char* fromDec(int n, int neg);
float toFloat(int, int, int);
char* strrepeat(const char* toR, int num);
char* reverse(char* str) ;

char* substring(const char* string, int l, int len) {
    if (!string || !strlen(string) || len < 0 || len > (strlen(string) - l)){
        return 0;
    }
    char* output = (char*) malloc(len);
    strncpy(output, string + l, len);
    output[len] = '\0';
    return output;
}

int getsign(const char* num) {
    char* sym = substring(num, 0, 1);
    return chartoint(*sym);
}
 
int getexp(const char* num) {
    char* exponent = substring(num, 1, 8);
    if (!strcmp(exponent, strrepeat("0", 8)))
            return 100;
    else if (!strcmp(exponent, strrepeat("1", 8)))
            return 10;

    return toDec(exponent);
}
 
int getsignif(const char* num) {
    char* significand = substring(num, 9, 23);
    if (!strcmp(significand, strrepeat("0", 23)))
            return 100;
    else if (!strcmp(significand, strrepeat("1", 23)))
            return 10;

    return toDec(significand);
}

char* reverse(char* str) {
    char* rev = (char*)calloc(1, strlen(str));
    int i;
    for (i = 0; i < strlen(str); i++) {
        rev[i] = str[strlen(str)-1-i];
    }
    return rev;
}

char tochar(int n) {
    return n - 208;
}

int chartoint(char c) {
    return c - '0';
}

char* fromDec(int n, int neg) {
    if (neg == -1) {
        n = n + 1;
    }

    int base = 10;

    char* final = (char *) calloc(1, sizeof(char));
    char* digit = (char *) calloc(1, sizeof(char));
    int remainder;


    while (n) {
        remainder = abs(n % base);

        digit[0] = tochar(remainder);

        strcat(final, digit);
        n /= base;
    }
    if (neg == -1)
        printf("%s","-");
    return reverse(final);
}


int toDec(const char *num) {
    int base = 2;
    int final = 0;
    int power = 0;
    int i;
    for (i = strlen(num) - 1; i >= 0; i--) {
        int x;
        x = num[i] - '0';

        final += x * (pow(base, power++));
    }

    return final;
}

char* strrepeat(const char* c, int num) {
    char* res = (char*)malloc(sizeof(char)*num);
    int i = 0;
    for (; i < num; i++)
        strcat(res,c);

    return res;
}

float toFloat(int sign, int mag, int exp) {
    int finalexp = exp - 127;
 
    float final = (pow(-1, sign) * (1 + (mag * pow(2, -23))) * pow(2, finalexp));
    return final;
}

void tostring(float f) {
    float temp = f;
    char* output = (char*)malloc(sizeof(char)*100);
    char* add = (char*)malloc(sizeof(char));
    char* exp = (char*)malloc(sizeof(char));
    strcat(exp,"e");
    int n = 0;

    if (f < 1) {
        n++;
        strcat(exp,"-");
    }

    int exponent = abs((int)log10(f))+n;
    *add = (exponent-208);
    if (n == 1) {
        double power = 1;
        while (power < exponent) {
            f *= 10;
            power++;
        }
        f *= 10;
        temp = f;
    }

    strcat(exp,add);


    while (temp > 1) {
        int newadd = (int)temp%10;
        *add = (newadd-208);
        temp = temp/10;
        strcat(output,add);
    }

    output = reverse(output);
    strcat(output,".");
    temp = f*10;
    
    int i;
    for (i = 0; i < 7; i++) {
        int fadd = (int)temp%10;
        *add = (fadd-208);
	strcat(output,add);
	temp = temp*10;
    }
    printf("%s%s\n", output, exp);
}

int main(int argv, char* argc[]) {
    
    if (argv < 2) {
        fprintf(stderr, "Error: Incorrect number of arguments \n");
        exit(EXIT_FAILURE);        
    }
    if (argv > 2) {
        fprintf(stderr, "Error: Too many arguments\n");
        exit(EXIT_FAILURE);        
    }

    char* set = (char*)malloc(strlen(argc[1]));
    strcpy(set,argc[1]);
    char* type = (char*)malloc(strlen(argc[2]));
    strcpy(type, argc[2]);
    char* ans = (char*)malloc(sizeof(char)*4);
    int temp = 0;

    if (strcmp(type,"int") == 0) {
        int neg = 1;
        if (set[0] == '1')
            neg = -1;
        temp = toDec(set);
        ans = fromDec(temp, neg);
        printf("%s\n", ans);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(type,"float") == 0) {
        int signNum = getsign(set);
        int exponent = getexp(set);
        int significand = getsignif(set);

        if (significand == 100) {
            if (exponent == 100) {
                if (signNum == 1) {
                    printf("0.0e0\n");
                    exit(EXIT_SUCCESS);
                }
                else {
                    printf("0.0e0\n");
                    exit(EXIT_SUCCESS);
                }
            } else if (exponent == 10) {
                if (signNum == 1) {
                    printf("ninf");
                    exit(EXIT_SUCCESS);
                } else {
                    printf("pinf");
                    exit(EXIT_SUCCESS);
                }
            }
        } else {
            if (exponent == 10) {
                printf("NaN");
                exit(EXIT_SUCCESS);
            }
        }
    }
    int signNum = getsign(set);
    int exponent = getexp(set);
    int significand = getsignif(set);  
    float answer = toFloat(signNum, significand, exponent);
    tostring(answer);
    free(set);
    free(type);
    free(ans);
    return 0;
}
