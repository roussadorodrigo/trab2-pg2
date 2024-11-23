#include <stdio.h>

#include "books.h"

Collection col;
Collection * col_ptr = &col;

int main(int argc, char * argv[]){
	
	char input[LINE_LEN];
	
	if(processFile(argv[1], collAddBook, col_ptr) == -1){
		return 1;
	}
	
	printf("The valid commands are:\n l - show all books \n q - exit\n");
	
	while(1){
		
		scanf("%[^\n]%*c", input);  // [^\n] - serve para ler a string até encontrar um \n (não lendo o \n)
		
		switch(input[0]){
			
			case 'l':
				for(int i = 0; i <= col_ptr->count-1; i++){
				printf("TITLE: %s | ", col_ptr->books[i].title);
				printf("ISBN: %s | ", col_ptr->books[i].isbn);
				printf("AUTHORS: %s | ", col_ptr->books[i].authors);
				printf("PUBLISHER: %s\n\n", col_ptr->books[i].publisher);
				}
				break;
				
			case 'a':
				for(int i = 0; i <= col_ptr->count-1; i++){
				printf("TITLE: %s | ", col_ptr->books[i].title);
				printf("AUTHORS: %s | ", col_ptr->books[i].authors);
				printf("PUBLISHER: %s | ", col_ptr->books[i].publisher);
				printf("ISBN: %s \n\n", col_ptr->books[i].isbn);
				}				
				
				break;
				
			case 'i':
				printf("IIIIIIIIIIIIII\n");
				//FALTA COMPLETAR
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
