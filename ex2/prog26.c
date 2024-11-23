#include <stdio.h>

#include "books.h"

Collection col;
Collection * col_ptr = &col;

int main(int argc, char * argv[]){
	char input[LINE_LEN];
	
	if(processFile(argv[1], collAddBook, col_ptr) == -1){				//Processamento de ficheiro
		return 1;
	}
	
	collSortTitle(col_ptr);												//colocar os livros por ordem alfabetica dos titulos
	
	printf("The valid commands are:\n l - show all books \n q - exit\n");
	
	while(1){
		
		fgets(input, sizeof(input), stdin); 
		separatorUnify(input);											//uniformização de espaços
		
		switch(input[0]){
			case 'l':													//comando l
				for(int i = 0; i <= col_ptr->count-1; i++){
				printf("TITLE: %s | ", col_ptr->books[i].title);
				printf("ISBN: %s | ", col_ptr->books[i].isbn);
				printf("AUTHORS: %s | ", col_ptr->books[i].authors);
				printf("PUBLISHER: %s\n\n", col_ptr->books[i].publisher);
				}
				break;
				
			case 'q':													//comando q
				printf("Exiting the program\n");
				return 0;
				
			default:													//comandos invalidos
				printf("Invalid command\n");
				continue;
			
		}
		
	}
	
	
}
