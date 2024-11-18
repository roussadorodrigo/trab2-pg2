#include <stdio.h>

int processFile(const char * filename, int (*action)(const char * line, void * context), void * context){
	FILE * file;
	char line_buffer[512];
	int accumulator = 0;
	
	//abrir o ficheiro
	file = fopen(filename, "r");
	
	//verificação de abertura do ficheiro
	if(file == NULL){
		printf("Não foi possível abrir o ficheiro.");
		return -1; //valor de return escolhido para indicar erro
	}
	
	//ler a linha
	while(fgets(line_buffer, sizeof (line_buffer), file) != NULL){
		//aplicar a função action à linha lida
		accumulator += action(line_buffer, context);
	}
	//fechar o ficheiro
	fclose(file);
	
	return accumulator;
}

int linePrintRaw(const char * line, void * context){
	printf("%s", line);
	return 1;
}

int main(int argc, char * argv[]){
	processFile(argv[1], linePrintRaw, NULL);
}
