#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int HexToInt(char ch);
int sum(int x, int y);
int prod(int x, int y);
int diff(int x, int y);
char * reverse(char *str);
int toDec(char *in, int base);
int getBase(char base);
char tochar(int n);
char toHexChar(int n);
char * fromDec(int n, char s);
char * twos(char *str, char s);

char* fromDec(int num, char s){
    
	char *ans = (char *) calloc(1, sizeof(char));
    	char *digit = (char *) calloc(1, sizeof(char));
	char *negative = "";
	int r;
	int base = 10;
	    
	if (s == 'x'){
		base = 16;
	}
	else if (s == 'o'){
		base = 8;
	}
	else if (s == 'b'){
		base = 2;
	}
	if (num < 0) {
		num = num + 1;
		negative = "-";
	}
	while (num) {
		r = num % base;
		if (base == 16 && r >= 10) {
		    digit[0] = toHexChar(r);
		}
		else {
		    digit[0] = tochar(r);
		}

		strcat(ans, digit);
		num /= base;
	    }
	    printf("%s%c", negative, s);
	    free(digit);
	    return reverse(ans);
}

char toHexChar(int num){
    char hexchars[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    return hexchars[num - 10];
}

int sum(int x, int y){
    return (x+y);
}

int prod(int x, int y){
    return (x*y);
}

int diff(int x, int y){
    return (x-y);
}

char tochar(int n){
    return n - 208;
}

char* reverse(char* str) {
    char *rev = (char*)malloc(strlen(str));
    int i;
    for (i = 0; i < strlen(str); i++) {
        rev[i] = str[strlen(str)-1-i];
    }
    return rev;
}

int toDec(char* c, int base) {
    int ans = 0;
    int power = 0;
    int i;
    for (i = strlen(c) - 1; i >= 0; i--) {
        
	int x;
	if (base == 16 && !isdigit(c[i])) {
            x = HexToInt(c[i]);
        } else {
            x = c[i] - '0';
        }

        ans += x * (pow(base, power++));
    }

    return ans;
}

int HexToInt(char ch) {
    switch (ch) {
        case 'a':  
        case 'A':  
           return 10;  
           break;  
        case 'b':  
        case 'B':  
           return 11;  
           break;  
        case 'c':  
        case 'C':  
           return 12;  
           break;  
        case 'd':  
        case 'D':  
           return 13;  
           break;  
        case 'e':  
        case 'E':  
           return 14;  
           break;  
        case 'f':  
        case 'F':  
           return 15;  
           break; 
	default:
           return -1;
    }
}

int getBase(char base) {
    if (base == 'b')
        return 2;
    else if (base == 'o')
        return 8;
    else if (base == 'd')
        return 10;
    else if (base == 'x')
        return 16;
    else {
        printf("%s%c\n", "Base: ", base);
        fprintf(stderr, "Error: Invalid base\n");
        exit(EXIT_FAILURE); 
    }
}

int main(int argc, char* argv[]) {

    if (argc < 5) {
        fprintf(stderr, "Error: Incorrect number of arguments \n");
        exit(EXIT_FAILURE);        
    }
    if (argc > 6) {
        fprintf(stderr, "Error: Too many arguments\n");
        exit(EXIT_FAILURE);        
    }

    char* op = (char*)malloc(strlen(argv[1]));
    strcpy(op, argv[1]);
    char* first = (char*)malloc(strlen(argv[2]));
    strcpy(first, argv[2]);
    char*second = (char*)malloc(strlen(argv[3]));
    strcpy(second, argv[3]);
    char* output = (char*)malloc(strlen(argv[4]));
    strcpy(output, argv[4]);
    char* ans = (char*)malloc(sizeof(char));

    int num1 = 0;
    int num2 = 0;
    int l = 0;
    int negative1 = 1;
    int negative2 = 1;
    if (first[0] == '-') {
        negative1 = -1;
        char base = first[1];
        int value = getBase(base);
        char* number1 = (char *)malloc(strlen(first)-2);
        number1 = strncpy(number1, first+2, strlen(first));
        num1 = toDec(number1, value);
        num1 *= negative1;
        free(number1);
    }
    else {
        char base = first[0];
        int value = getBase(base);
        char* number1 = (char*)malloc(strlen(first)-1);
        number1 = strncpy(number1, first+1, strlen(first));
        num1 = toDec(number1, value);
        free(number1);
    }

    if (second[0] == '-') {
        negative2 = -1;
        char base = second[1];
        int value = getBase(base);
        char* number2 = (char*)malloc(strlen(second)-2);
        number2 = strncpy(number2, second+2, strlen(second));
        num2 = toDec(number2, value);
        num2 *= negative2;
        free(number2);
    }
    else {
        char base = second[0];
        int value = getBase(base);
        char* number2 = (char*)malloc(strlen(second)-1);
        number2 = strncpy(number2, second+1, strlen(second));
        num2 = toDec(number2, value);
        free(number2);
    }

    if (strcmp(op,"+") == 0) {
        l = sum(num1, num2);
    }
    else if (strcmp(op,"-") == 0) {
        l = diff(num1, num2);
    }
    else if (strcmp(op,"*") == 0) {
        l = prod(num1, num2);
    }


    ans = fromDec(l, (*output));
    printf("%s\n", ans);
    
    
    free(op);
    free(first);
    free(second);
    free(output);
    free(ans);

    return 0;
}
