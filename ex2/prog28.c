#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "books.h"

Collection col;
Collection * col_ptr = &col;

int main(int argc, char * argv[]){
	char input[LINE_LEN];
	char * isbn;
	BookData * elem;
	
	if(processFile(argv[1], collAddBook, col_ptr) == -1){
		return 1;
	}
	
	collSortTitle(col_ptr);
	collSortRefIsbn(col_ptr);
	
	printf("The valid commands are:\n l - show all books \n q - exit\n i isbn - searches for the book by isbn\n");
	
	while(1){
		
		scanf("%s", input);
		
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
				
				
				separatorUnify(input);
				
				strtok(input, " ");
				isbn = strtok(input, " ");
				
				printf("%s\n", isbn);
				elem = bsearch(isbn, col_ptr->refs, col_ptr->count, SIZE_ISBN, (int (*) (const void *, const void *))isbn_cmp);
				if(!elem)
					printf("ISBN not found\n");
				else{
					printf("TITLE: %s | ", elem->title);
					printf("ISBN: %s | ", elem->isbn);
					printf("AUTHORS: %s | ", elem->authors);
					printf("PUBLISHER: %s\n\n", elem->publisher);
				}
				
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
