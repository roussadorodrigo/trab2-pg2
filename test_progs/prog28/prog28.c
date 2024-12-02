#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "books.h"



int main(int argc, char * argv[]){
	
	Collection col;
	col.count = 0;
	char input[LINE_LEN];												// Array onde vai ficar o input do programa
	char* isbn;															// String que tem o isbn apenas proveniente do "Array de input"
	
	
	if(processFile(argv[1], collAddBook, &col) == -1) return 1;			// Processamento de ficheiro
	
	collSortTitle(&col);												// Ordem alfabetica dos titulos
	collSortRefIsbn(&col);												// Ordem crescente dos ISBN dos livros
								
	
	printf(" The valid commands are:\n l - show all books \n q - exit\n i isbn - searches for the book by isbn\n\n ");
	while(1){
		
		
		
		fgets(input, sizeof(input), stdin);								// Leitura do input do programa 
		separatorUnify(input);											// Uniformização de espaços do input, para ter formatação certa 
		
		
		
		
		if((lenght(input) > 2) && (input[1] != ' ') && ( ((input[1] != 'i')) || ((input[1] != 'a')))){					/// If de verificar espaço entre "comando" e "palavra" no INPUT, senão segmentation fault;   maior que 2 porque o lenght conta com o \0;   
			printf("\n Invalid input, please input a space between the command and the word/number\n\n ");				/// A ser melhorado, pode haver questões com comando de uma unica letra
			continue;
		}
		
	
	
		switch(input[0]){	
			default:													///Comandos inválidos
				printf("\n Invalid command\n\n ");
				continue;
				
															
			case 'l':													/// Comando l
				for(int i = 0; i <= col.count-1; i++){
				printf("\n TITLE: %s | ", col.books[i].title);
				printf("ISBN: %s | ", col.books[i].isbn);
				printf("AUTHORS: %s | ", col.books[i].authors);
				printf("PUBLISHER: %s\n\n ", col.books[i].publisher);
				}
				break;
				
				
			case 'i':													/// Comando i
				isbn = strtok(input, " ");
				isbn = strtok(NULL, " ");
				
				BookData* matching_isbn = find_book_by_isbn(isbn, &col);// Função nova já está no books.h e books.c
				
				if(matching_isbn != NULL){
					printf("\n TITLE: %s | ", matching_isbn->title);
					printf("ISBN: %s | ", matching_isbn->isbn);
					printf("AUTHORS: %s | ", matching_isbn->authors);
					printf("PUBLISHER: %s\n\n ", matching_isbn->publisher);
					continue;
				}
				
				printf("\n Book not found\n\n ");
				break;
				
				
			case 'q':													/// Comando q
				printf("\n Exiting the program\n\n");
				return 0;
		}
	}
}
