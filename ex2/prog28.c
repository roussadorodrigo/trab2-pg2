#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "books.h"

Collection col;
Collection * col_ptr = &col;

int main(int argc, char * argv[]){
	char input[LINE_LEN];
	char* isbn;
	int check_isbn = 0;
	
	if(processFile(argv[1], collAddBook, col_ptr) == -1){				//Processamento de ficheiro
		return 1;
	}
	
	collSortTitle(col_ptr);												//ordem alfabetica dos titulos
	collSortRefIsbn(col_ptr);											//ordem crescente dos ISBN dos livros
	
	printf("The valid commands are:\n l - show all books \n q - exit\n i isbn - searches for the book by isbn\n");
	
	while(1){
		
		fgets(input, sizeof(input), stdin);								// fazendo com fgets já não dá loop infinito 
		separatorUnify(input);											//uniformização de espaços
		
		switch(input[0]){												
			case 'l':
				for(int i = 0; i <= col_ptr->count-1; i++){
				printf("TITLE: %s | ", col_ptr->books[i].title);
				printf("ISBN: %s | ", col_ptr->books[i].isbn);
				printf("AUTHORS: %s | ", col_ptr->books[i].authors);
				printf("PUBLISHER: %s\n\n", col_ptr->books[i].publisher);
				}
				break;
				
				
			case 'i':
				isbn = strtok(input, " ");
				isbn = strtok(NULL, " ");

				for(int i = 0; i < (col_ptr->count); i++){
					if(strcmp_ic(col_ptr->refs[i]->isbn, isbn) == 0){
					
						printf("TITLE: %s | ", col_ptr->books[i].title);
						printf("ISBN: %s | ", col_ptr->books[i].isbn);
						printf("AUTHORS: %s | ", col_ptr->books[i].authors);
						printf("PUBLISHER: %s\n", col_ptr->books[i].publisher);
						check_isbn = 1;
						break;
					}
				}
				if(check_isbn == 0)printf("Book not found\n");
						
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
