/*
 * Exemplo compilação 
 * 
 * Compilar: gcc ex1-3.c
 * Executar: a.out demo_file.txt
 */


#include <stdio.h>
#define LINE_LEN 512												//512 caracteres de armazenamento da linha


int processFile(const char * filename, int (*action)(const char * line, void * context), void * context){
	char line_buffer[LINE_LEN];
	int accumulator = 0;
	FILE* file = fopen(filename, "r");									//abertura o ficheiro
	
	if(file == NULL){											//verificação de abertura do ficheiro
		printf("Não foi possível abrir o ficheiro.\n");
		return -1; //valor de return escolhido para indicar erro
	}
	
	while(fgets(line_buffer, sizeof(line_buffer), file) != NULL){						//leitura linha a linha
		accumulator += action(line_buffer, context);							//acumulador dos valores do return da funcao "action"
	}
	
	fclose(file);												//fechar o ficheiro
	return accumulator;
}

int linePrintRaw(const char * line, void * context){
	printf("%s", line);
	return 1;
}

int main(int argc, char * argv[]){
	processFile(argv[1], linePrintRaw, NULL);	
}
