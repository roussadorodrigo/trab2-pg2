#include <stdio.h>

#include "books.h"

int main(int argc, char * argv[]){
	
	Collection col;
	Collection * col_ptr = &col;
	col_ptr->count = 0;
	
	if(processFile(argv[1], collAddBook, col_ptr) == -1){
		return 1;
	}
	
	for(int i = 0; i <= col_ptr->count-1; i++){
		printf("%s;", col_ptr->books[i].title);
		printf("%s;", col_ptr->books[i].isbn);
		printf("%s;", col_ptr->books[i].authors);
		printf("%s\n", col_ptr->books[i].publisher);
	}
}
