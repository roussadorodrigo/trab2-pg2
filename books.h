#ifndef BOOKS_H
#define BOOKS_H

#define LINE_LEN 512

#define MAX_BOOKS 296 //MAX_BOOKS coincide com o número máximo de linhas!
#define MAX_LINE_WIDTH 435+1
#define MAX_TITLE 200+1
#define SIZE_ISBN 10+1
#define MAX_AUTHORS 92+1
#define MAX_PUB_NAME 51+1

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

/***FUNCOES SE1***/
static char *splitField(char *str);
int lenght(const char *str);
int strcmp_ic(const char *str1, const char *str2);
void separatorUnify(char str[]);
/******/

static int title_cmp(const BookData * b1, const BookData * b2);
int isbn_cmp(const BookData * b1, const BookData * b2);
BookData *find_book_by_isbn(const char *search_isbn, Collection *col);	// Função nova, a tal do bsearch


int processFile(const char * filename, int (*action)(const char * line, void * context), void * context);
int linePrintRaw(const char * line, void * context);
int lineFilterPrint(const char * line, void * context);
int fillBookData(BookData * b, const char * line);
int collAddBook(const char * line, void * context);
void collSortTitle(Collection * col);
void collSortRefIsbn(Collection * col);
int bookContainsAuthor(BookData * b, const char * word);
#endif
