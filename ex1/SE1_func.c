#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "SE1_func.h"


char *splitField(char *str) {
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        if (str[i] == ';') {
            str[i] = '\0';
            return &str[i + 1];
        }
    }
    return NULL;
}



void separatorUnify(char str[]) {
    int i = 0, space_before = 0, j = 0;

    while (isspace(str[i])) {
        i++;
    }

    while (str[i] != '\0') {
        if (isspace(str[i])) {
            if (!space_before) {
                str[j++] = ' ';
                space_before = 1;
            }
        } else {
            str[j++] = str[i];
            space_before = 0;
        }
        i++;
    }

    if (j > 0 && str[j - 1] == ' ') {
        j--;
    }
    str[j] = '\0';
}



int strcmp_ic( const char *str1, const char *str2 ){
	
	char str1_low[lenght(str1)];
	char str2_low[lenght(str2)];
	
	int i = 0; //variável para percorrer str1
	int j = 0; //variável para percorrer str2
	
	
	//Converter todos os characters em minusculas e adicionar o terminador 
	while(str1[i] != '\0'){
		str1_low[i] = tolower(str1[i]);
		i++;
	}
	str1_low[i] = '\0';
	
	while(str2[j] != '\0'){
		str2_low[j] = tolower(str2[j]);
		j++;
	}
	str2_low[j] = '\0';
	
	//str1_low é menor que str2_low
	if(i < j){ 
		
		for(int k = 0; k <= i; k++){
			
			if(str1_low[k] != str2_low[k])return (str1_low[k] - str2_low[k]);
			
		}
		
	}
	
	//str1_low é maior que str2_low
	if(i > j){ 
		
		for(int k = 0; k <= j; k++){
			
			if(str1_low[k] != str2_low[k])return (str1_low[k] - str2_low[k]);
			
		}
		
	}

	//str1_low tem igual comprimento que str2_low
	for(int k = 0; str1_low[k] != '\0'; k++){
		
		if(str1_low[k] != str2_low[k])return (str1_low[k] - str2_low[k]);
		
	}
	
	//Quando ambas as string são iguais em palavra e comprimento
	return 0;
	
}
