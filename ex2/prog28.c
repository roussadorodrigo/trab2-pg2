/*Este programa consegue encontrar os livros por isbn no ficheiro "dados_3livros.csv" mas não no ficheiro "dados.csv"*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "books.h"

int main(int argc, char * argv[]){
	
	Collection col;
	col.count = 0;
	
	BookData * search_isbn;
	
	BookData * matching_isbn;
	
	char input[LINE_LEN];
	char* isbn;
	int check_isbn = 0;
	
	if(processFile(argv[1], collAddBook, &col) == -1){				//Processamento de ficheiro
		return 1;
	}
	
	collSortTitle(&col);												//ordem alfabetica dos titulos
	collSortRefIsbn(&col);												//ordem crescente dos ISBN dos livros
								
	
	printf("The valid commands are:\n l - show all books \n q - exit\n i isbn - searches for the book by isbn\n");
	
	while(1){
		
		fgets(input, sizeof(input), stdin);								// fazendo com fgets já não dá loop infinito 
		separatorUnify(input);											//uniformização de espaços
		
		switch(input[0]){												
			case 'l':
				for(int i = 0; i <= col.count-1; i++){
				printf("TITLE: %s | ", col.books[i].title);
				printf("ISBN: %s | ", col.books[i].isbn);
				printf("AUTHORS: %s | ", col.books[i].authors);
				printf("PUBLISHER: %s\n\n", col.books[i].publisher);
				}
				break;
				
				
				
				
				
			case 'i':
				isbn = strtok(input, " ");
				isbn = strtok(NULL, " ");
				
				strcpy(search_isbn->isbn,isbn);
				
				matching_isbn = (BookData *) bsearch(search_isbn, &col.refs, col.count, sizeof(BookData *), (int (*) (const void *, const void *))isbn_cmp);
				printf("->> %p\n", matching_isbn);
				if(matching_isbn != NULL){
					
					printf("TITLE: %s | ", matching_isbn->title);
					printf("ISBN: %s | ", matching_isbn->isbn);
					printf("AUTHORS: %s | ", matching_isbn->authors);
					printf("PUBLISHER: %s\n", matching_isbn->publisher);
					continue;
					}
				
				printf("Book not found\n");
						
				break;
				
				
				
				
				
			case 'q':
				printf("Exiting the program\n");
				return 0;
				
			default:
				printf("Invalid command\n");
				continue;
			
		}
		
	}
	
	
}
