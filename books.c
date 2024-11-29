#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "books.h"

/***FUNCOES SE1***/
static char *splitField(char *str){
	for(int i = 0; str[i] != '\n'; i++){		//ciclo "for" para percorrer um array
		if (str[i] == ';'){						//se o elemento atual for um ";" 
			str[i] = '\0';						//este vai ser substituido por "\0"(caracter terminador)
			return &str[i + 1];					//a função vai devolver o endereço do elemento atual caso este sejá um "\0"
		}
	}
	
	return NULL;
}


static int lenght(const char *str){
	int counter = 0; //Variavel para contar quantos elementos tem no array
	for(int i = 0; str[i] != '\0'; i++)
		counter ++;
	return (counter+1);			/////////////////////////////////////////////// +1 - contar '\0' no final do campo 
}


int strcmp_ic(const char *str1, const char *str2){
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
	
	return 0; //Quando ambas as string são iguais
}


void separatorUnify(char str[]){
	int i = 0; 				//Variável que percorre a string
	int space_before = 0;	//Variável que diz se há espaço anteiror (=1) ou não (=0)
	int j = 0;
	
	//Remover ("ignorar") espaços iniciais existentes
	while(isspace(str[i]))i++;
		
	//Percorrer toda a string removendo todos os espaços a mais
	while (str[i] != '\0'){
		//Adicionar apenas um espaço caso haja mais que um
		if(isspace(str[i])){
			//se não houver espaço anterior, adicionar apenas 1
			if(!space_before){
				str[j++] = ' ';
				space_before = 1;
			}
		}
		else{
			str[j++] = str[i];
			space_before = 0;
		}
		i++;
	}
	
	//Remover os espaços finais
    if (j > 0 && str[j - 1] == ' ')j--;
    
	//Adicionar o terminador
    str[j] = '\0';	
}

/******/

static int title_cmp(const BookData * b1, const BookData * b2){
	return strcmp_ic(b1->title, b2->title);
}


int isbn_cmp(const BookData * pb1, const BookData * pb2){
	BookData *b1 = *(BookData**)pb1;
	BookData *b2 = *(BookData**)pb2;
	
	return strcmp_ic(b1->isbn, b2->isbn);
}


int processFile(const char * filename, int (*action)(const char * line, void * context), void * context){
	char line_buffer[LINE_LEN];
	int accumulator = 0;
	
	//abrir o ficheiro
	FILE * file = fopen(filename, "r");
	
	//verificação de abertura do ficheiro
	if(file == NULL){
		printf("Não foi possível abrir o ficheiro.\n");
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


int lineFilterPrint(const char * line, void * context){
	//copiar line para uma string auxiliar (para não perder quando splitField e separatorUnify!)
	char line_copy[LINE_LEN];
	strcpy(line_copy, line);
	
	//obter o primeiro campo de line
	splitField(line_copy);
	
	//uniformizar o campo
	separatorUnify(line_copy);
	
	//comparar strings e retornar
	if(strcmp_ic(line_copy, context ) == 0){
		printf("%s", line);
		return 1;
	}
	return 0;
}


int fillBookData(BookData * b, const char * line){
	char * unsplit_line;
	
	//fazer uma cópia de line
	char line_copy[LINE_LEN];
	char string_aux[LINE_LEN];
	strcpy(line_copy, line);
	
	unsplit_line = splitField(line_copy); //obtenção do título
	if(!unsplit_line)return 0;			  //verificação do pointer
	separatorUnify(line_copy);
	
	strcpy(b->title, line_copy);		  //preenchimento do título
	
	int i;	  							  //preenchimento de line_copy com o resto da linha
	for(i = 0; unsplit_line[i] != '\0'; i++)line_copy[i] = unsplit_line[i];

	
	unsplit_line = splitField(line_copy); //preenchimento do isbn
	if(!unsplit_line)return 0;
	separatorUnify(line_copy);
	strcpy(b->isbn,line_copy);

	for(i = 0; unsplit_line[i] != '\0'; i++)line_copy[i] = unsplit_line[i];
	
	unsplit_line = splitField(line_copy); //avançar sem copiar o 3º campo da linha
	if(!unsplit_line)return 0;
	for(i = 0; unsplit_line[i] != '\0'; i++)line_copy[i] = unsplit_line[i];
	
	unsplit_line = splitField(line_copy); //preenchimento do authors
	if(!unsplit_line)return 0;
	separatorUnify(line_copy);
	strcpy(b->authors,line_copy);

	for(i = 0; unsplit_line[i] != '\0'; i++)line_copy[i] = unsplit_line[i];
	
	
	unsplit_line = splitField(line_copy); //preenchimento do publisher
	if(!unsplit_line)return 0;
	separatorUnify(line_copy);
	strcpy(b->publisher,line_copy);
	
	for(i = 0; unsplit_line[i] != '\0'; i++)line_copy[i] = unsplit_line[i];
	
	return 1;
}


int collAddBook(const char * line, void * context){
	
	Collection * p = (Collection *)context; //ponteiro auxiliar (para a collection)
	
	//verificar se há espaço para o novo elemento
	if(p->count == MAX_BOOKS)return 0;
	
	//verificar se a informação é válida
	if(fillBookData(&(p->books[p->count]), line) == 0)return 0;
	//preencher a estrutura com o novo elemento
	p->refs[p->count] = NULL;
	p->count++;
	return 1;
}


void collSortTitle(Collection * col){
	if(col == NULL || col->count == 0)printf("ERRO - a collection não existe ou está vazia!");
	else{qsort(col->books, col->count, sizeof(BookData), (int (*) (const void *, const void *))title_cmp);}	
}


void collSortRefIsbn(Collection * col){
	//iniciar o array refs (com a ordem do array books)
	for(int i = 0; i < col->count; i++){
		col->refs[i] = &(col->books[i]);
	}
	
	//ordenar o array refs
	qsort(col->refs, col->count, sizeof(BookData *), (int (*) (const void *, const void *))isbn_cmp);
}


int bookContainsAuthor(BookData * b, const char * word){
	char * token;
	const char * break_character = " ";
	
	//criar uma cópia de b->authors
	char authors_copy[MAX_AUTHORS];
	for(int i = 0; b->authors[i]!='\0'; i++)authors_copy[i] = b->authors[i];
	
	//passar as vírgulas a espaços
	for(int i = 0; authors_copy[i] != '\0'; i++)
		if(authors_copy[i] = ',')
			authors_copy[i] = ' ';
	
	//uniformizar a string
	separatorUnify(authors_copy);
	
	token = strtok(authors_copy, break_character);
	while(token != NULL){
		if(strcmp_ic == 0)return 1;
		token = strtok(NULL, break_character);
	}
	
	return 0;
}

