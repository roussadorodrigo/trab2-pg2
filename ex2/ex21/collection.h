#ifndef COLLECTION_H
#define COLLECTION_H

#define MAX_BOOKS 310 //MAX_BOOKS coincide com o número máximo
					  //de linhas!

#define MAX_LINE_WIDTH 450

#define MAX_TITLE 220
#define SIZE_ISBN 20
#define MAX_AUTHORS 100
#define MAX_PUB_NAME 70

typedef struct book { 
 char title[MAX_TITLE]; 
 char isbn[SIZE_ISBN]; 
 char authors[MAX_AUTHORS]; 
 char publisher[MAX_PUB_NAME]; 
} BookData; 
 
typedef struct{ 
 BookData books[MAX_BOOKS]; 
 BookData *refs[MAX_BOOKS]; 
 int count; 			//quantidade de elementos preenchidos em books 
} Collection; 

#endif
