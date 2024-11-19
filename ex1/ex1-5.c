/*
 * Exemplo compilação 
 * 
 * Compilar: gcc SE1_func.c -c
 * 			 gcc ex1-5.c -c
 * 			 gcc SE1_func.o ex1-5.o
 * Executar: a.out demo_file2.txt  cebola
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "SE1_func.h"

#define LINE_LEN 512 //511 caracteres úteis e 1 para o terminador



int lineFilterPrint(const char * line, void * context){
	//guardar o conteúdo de line sem alterações
	char line_copy[LINE_LEN];
	for(int i = 0; line[i] != '\0'; i++)line_copy[i] = line[i];
	
	//obter o primeiro campo de line
	splitField(line_copy);
	
	//uniformizar o campo
	separatorUnify(line_copy);
	
	//comparar strings e retornar
	if(strcmp_ic(line_copy, context) == 0){
		printf("%s", line);
		return 1;
	}
	
	return 0;
}

int processFile(const char * filename, int (*action)(const char * line, void * context), void * context){
	char line_buffer[LINE_LEN];
	int accumulator = 0;
	FILE* file = fopen(filename, "r");									//abertura o ficheiro
	
	if(file == NULL){													//verificação de abertura do ficheiro
		printf("Não foi possível abrir o ficheiro.\n");
		return -1; //valor de return escolhido para indicar erro
	}
	
	while(fgets(line_buffer, sizeof(line_buffer), file) != NULL){		//leitura linha a linha
		accumulator += action(line_buffer, context);					//acumulador dos valores do return da funcao "action"
	}
	
	fclose(file);														//fechar o ficheiro
	return accumulator;
}

int main(int argc, char * argv[]){
	int n_lines = processFile(argv[1], lineFilterPrint, argv[2]);
	if(n_lines == -1)
		printf("Não foram apresentadas linhas do ficheiro!\n");
	else
		printf("Número de linhas apresentadas: %d\n", n_lines);
}
