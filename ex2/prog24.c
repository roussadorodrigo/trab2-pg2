#include <stdio.h>

#include "books.h"

int main(int argc, char * argv[]){
	
	Collection col;
	col.count = 0;
	
	if(processFile(argv[1], collAddBook, &col) == -1){
		return 1;
	}
	
	for(int i = 0; i <= col.count-1; i++){
		printf("%s;", col.books[i].title);
		printf("%s;", col.books[i].isbn);
		printf("%s;", col.books[i].authors);
		printf("%s\n", col.books[i].publisher);
	}
}
